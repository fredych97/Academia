/*                                  UNIVERSIDAD TECNICA DEL NORTE
                                           FICA-CIERCOM
                                       SISTEMAS MICROPROCESADOS
                                            LABORATORIO
    INTEGRANTES:
                BENAVIDES WILMER
                CHANDI BRAYAN
                CHICAIZA FREDY
   Realice un reloj con un pulsador con las
  funciones de modificar la hora y crear la alarma. Otro pulsador para modificar
  el valor del minutero para actualizar la hora y la alarma y otro que permita actualizar el horero.

*/
#include <LiquidCrystal.h> //librerias 
#include <TimerOne.h>
#include<EEPROM.h>
#include <MsTimer2.h>
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);// puertos de lcd
int i = 0;// variables de contadores y banderas
int a = 0;
int j = 0;
int ff = 0;
String dato;// variable para usar y tranformar de string a char y de char a int
int minu = 0;// variable para minutos
int hora = 0;//variable para horas
int MinE = 0;// variables para minutero alarma
int HoraE = 0;// variable hora alarma
int zumbador = 12;// puerto de salida para el buzzer
int frecuencia = 900000000000000;// frecuencia que tendra el buzzer
int sw, sw1 = 0;// variables para las interrupciones
int pulsador = 0;// variable para el pulsador

void setup() {
  Serial.begin(9600);// iniciamos comunicacion serial
  pinMode(10, INPUT);
  pinMode(12, OUTPUT);// entrada de el pulsador
  lcd.begin(16, 2);
  Timer1.initialize(1000000);// inicializar timer1
  Timer1.attachInterrupt(contador);// metodo de control
  MsTimer2::set(1000, talarma);// velocidad el timer con su metodo de contro
  attachInterrupt(0, control, RISING);// interrupcion para crear alarma y modificar hora
  attachInterrupt(1, control1, RISING);// interrupcion para modificar alarma y minutos
  minu = EEPROM.read(0);// direccion de la memoria para minutos
  hora = EEPROM.read(1);//direccion de la memoria para hora
}
void loop() {
  minutos();//mostrar minutos en lcd
  horas();// mostrar hora en lcd
  segundos(); // mostrar segundos en lcd
  Stop();// condicion para parar el sistema
  alarma();// activar alarmar
  if (sw == 1) {// si la interruccion da un pulso se activa modificar hora
    hor();// metodo
    delay(200);
  }
  if (sw == 2) {// si la interruccion da dos pulsos se activa la configuracion de alarma
    configalarm();// metodo
    delay(200);

  } if (sw1 == 1) { //si la interruccion da un pulso se activa modificar minutos
    mi();// metodo
    delay(200);
  }
  if (sw1 == 2) {// si la interruccion da dos pulsoa se activa modificar hora de alarma
    horaE();// metodo
    delay(200);

  }
  if (hora > 23) {// si pasa la hora de 23 se vuelve a cero
    hora = 0;
  }
  horasE();
  minutosE();
  lcd.setCursor(9, 0);// mostrar en lcd
  lcd.print("HORA");
  lcd.setCursor(2, 0);
  lcd.print(':');
  lcd.setCursor(5, 0);
  lcd.print(':');
  lcd.setCursor(8, 0);
  lcd.print(' ');
  lcd.setCursor(0, 1);
  lcd.print("ALARMA");
  //lcd.setCursor(9, 1);
  //lcd.print(HoraE);
  lcd.setCursor(11, 1);
  lcd.print(":");
  //lcd.setCursor(13, 1);
  //lcd.print(MinE);
  
}
void contador() {// metodo de el timer para generar el reloj
  i++;
  if (i == 10) {
    EEPROM.write(0, minu);
    EEPROM.write(1, hora);
  }
  if (i > 59) {
    i = 0;
    minu++;
  }
  if (minu > 59) {
    minu = 0;
    hora++;
  }
}

void horasE() {// condicion para generar la hora en 00 cuando es menor a 10
  if (HoraE < 10) {
    lcd.setCursor(9, 1);// ubicacion en la lcd
    lcd.print('0');
    lcd.setCursor(10, 1);
    lcd.print(HoraE);
  }
  else {
    lcd.setCursor(9, 1);
    lcd.print(HoraE);
  }
  if (HoraE > 24) {
        HoraE = 00;
  }
}
void minutosE() {// condicion para generar la hora en 00 cuando es menor a 10
  if (MinE < 10) {
    lcd.setCursor(12, 1);// ubicacion en la lcd
    lcd.print('0');
    lcd.setCursor(13, 1);
    lcd.print(MinE);
  }
  else {
    lcd.setCursor(12, 1);
    lcd.print(MinE);
  }
  if (MinE > 59) {
        MinE = 00;
  }
}

void segundos() {// condicion para generar la hora en 00 cuando es menor a 10
  if (i < 10) {
    lcd.setCursor(6, 0);// ubicacion en la lcd
    lcd.print(0);
    lcd.setCursor(7, 0);
    lcd.print(i);
  }
  else {
    lcd.setCursor(6, 0);
    lcd.print(i);
  }
}
void control1() {//control para la interrupcion de minutero y alarma
  switch (sw1) {
    case 0:
      Serial.println("");
      Serial.println("configurar minutero");
      sw1++;
      break;
    case 1:
      Serial.println("modificar hora de alarma");
      sw1++;
      break;

  }

}
void minutos() {// configuracion para que los numeros menores a 10 van con 0
  if (minu < 10) {
    lcd.setCursor(3, 0);
    lcd.print(0);
    lcd.setCursor(4, 0);
    lcd.print(minu);
  }
  else {
    lcd.setCursor(3, 0);
    lcd.print(minu);
  }
}
void horas() {// configuracion para que los numeros menores a 10 van con 0
  if (hora < 10) {
    lcd.setCursor(0, 0);
    lcd.print(0);
    lcd.setCursor(1, 0);
    lcd.print(hora);
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print(hora);
  }
}
void alarma() {// configuracion de alarma
  if (a == 0) {
    if (minu == MinE && hora == HoraE && i == 0 ) {// comparacion si la hora del reloj es igual a la de la alarma
      MsTimer2::start();// inicia el
      digitalWrite(12, HIGH);
      delay(5000);
      //tone(zumbador, frecuencia);
      j = 0;
    }
    if (j == 1) {// ingreso de nueva hora para alarma
      j = 0;
      MinE++;
      Serial.print("Alarma nueva: ");// mensaje
      Serial.print(HoraE);// imprime nueva hora de alarma
      Serial.print(':');
      Serial.print(MinE);// imprime nuevo minuto de alarma
      MsTimer2::stop();
      delay(1000);
    }
  } // caso contrario se detiene la alarma
  else {
    //Serial.print("ALARMA APAGADA");
    //delay(5000);
    noTone(zumbador);// se apaga el buzzer
    a = 1;
    MsTimer2::stop();// se suspende el timer2
    j = 0;
  }
}
void configalarm() {// configuracion de alarma
  if (ff == 0) {// si la bandera esta en cero se ingresa  nueva alarma
    Serial.println("Ingrese la Hora");// mensaje
    delay(500);
    if (Serial.available() > 0) {// si se escrtito algo en el serial lee
      dato = Serial.readString();// ingresa el dato string
      HoraE = dato.toInt();// conversion a entero
      if (HoraE >= 23) {
        HoraE = 00;
      } else
      { EEPROM.write(3, HoraE); // guarda en la memoria

        delay(100);
        ff = 1; // se activa l bandera para el proximo proceso
      }
    }
  }
  if (ff == 1) {// ingreso de minutos
    Serial.println(' ');
    Serial.println("Ingrese los minutos");
    delay(500);
    if (Serial.available() > 0) {
      dato = Serial.readString();
      MinE = dato.toInt();
      if (MinE >= 59) {
        MinE = 00;
      } else {
        EEPROM.write(4, MinE);
        delay(100);
        ff = 2;
      }
    }
  }
  if (ff == 2) {// imprime la alarma ingresada
    Serial.println(' ');
    Serial.println("ALARMA ES: ");
    Serial.print(EEPROM.read(3));
    Serial.print(':');
    Serial.print(EEPROM.read(4));
    ff = 3;
  }
}
void talarma() {
  j++;
}
void control() {// metodo para la interrupcion de control de hora y alarma
  switch (sw) {
    case 0:
      Serial.println("configurar hora");
      sw++;
      break;

    case 1:
      Serial.println("crear alarma");
      sw++;
      break;



  }
}
void mi() {// metodo de modificacion de minutero
  pulsador = digitalRead(10);// lee el estado del pusador
  if (pulsador == LOW) {
      minu++;// incremento en minutero
    }
  }

void hor() {// metodo de modificacion de hora
  pulsador = digitalRead(10);
  if (pulsador == LOW) {
    hora++;
  }
}


void horaE() {// metodo de modificacion de horero de alarma
  pulsador = digitalRead(10);

  if (HoraE >= 24) {
    HoraE = 0;
  } else {
    if (pulsador == LOW) {
      HoraE++;
    }
  }
}


void Stop() {
  if ( digitalRead(12) == LOW)
    a = 0;
  if ( digitalRead(12) == HIGH)
    a = 1;
}
