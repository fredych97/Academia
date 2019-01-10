
/*
                                                                UNIVERSIDAD TÉCNICA DEL NORTE
                                                                        FICA-CIERCOM
                                                                   SISTEMAS MICROPROCESADOS
        Nombre: Fredy Chicaiza
        Fecha: 10-1-2019
        Actividad:  Subir su programa de un reloj con alarma que sea ingresada por comunicacion serial.
*/
#include <LiquidCrystal.h>
#include <TimerOne.h>
#include<EEPROM.h>
#include <MsTimer2.h>
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
int i = 0;
int d = 0;
int j = 0;
int m = 0;
int h = 0;
int M = 0;
int H = 0;
int k = 0;
String dato;
void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(12, INPUT);
  lcd.begin(16, 2);
  Timer1.initialize(1000000); // Contador a 1 seg
  Timer1.attachInterrupt(contador); // Se configurara el metodo
  MsTimer2::set(1000, talarma); //  Trabajara a 1 seg
  //MsTimer2::start();
  attachInterrupt(0, ho, RISING);
  attachInterrupt(1, mi, RISING);
  m = EEPROM.read(0);
  h = EEPROM.read(1);
}
void loop() {
  minutos();  //funcion minutos
  horas();    //funcion horas
  confalarma();
  //Serial.println(j);
  delay(500);
  segundos();  //funcion segundos
  detener();
  alarma();
  if (h > 23) {   //Si el ho llega a 23  reiniciara empezando desde 0
    h = 0;
  }
  // estructura LCD
  lcd.setCursor(2, 0);
  lcd.print(':');
  lcd.setCursor(5, 0);
  lcd.print(':');
  lcd.setCursor(0, 1);
  lcd.print("ALARMA CIERCOM");
  lcd.setCursor(8, 0);
  lcd.print(' ');
}
void contador() {   // Funcion contador
  i++;                //Incrementara en 1
  if (i == 10) {      //Si i es igual a 10
    EEPROM.write(0, m); //Escribe en la posicion de memoria 0
    EEPROM.write(1, h); //Escribe en la posicion de memoria 1
  }
  if (i > 59) {       //Si el seg llega a 59 el  reinicia empezando desde 0
    i = 0;
    m++;                //Incrementara en 1 el minu
  }
  if (m > 59) {       //Si el minutero llega a 59 el  reinicia empezando desde 0
    m = 0;
    h++;
  }
}
void segundos() {    // Funcion  segundos
  if (i < 10) {        //Si el segundero es menor a 10
    lcd.setCursor(6, 0); // Se imprimira en la columna 6 fila 0 --> el 0
    lcd.print(0);
    lcd.setCursor(7, 0); // Se imprimira en la columna 7 fila 0 --> el seg
    lcd.print(i);
  }
  else {
    lcd.setCursor(6, 0); // Se imprimira en la columna 6 fila 0 --> el seg
    lcd.print(i);
  }
}
void minutos() {      // Funcion  minutos
  if (m < 10) {         //Si  minutos es menor a 10
    lcd.setCursor(3, 0);  // Se imprimira en la columna 3 fila 0 --> el 0
    lcd.print(0);
    lcd.setCursor(4, 0);  // Se imprimira en la columna 4 fila 0 --> el minu
    lcd.print(m);
  }
  else {
    lcd.setCursor(3, 0);   // Se imprimira en la columna 3 fila 0 --> el minu
    lcd.print(m);
  }
}
void horas() {           // Funcion  horas
  if (h < 10) {            //Si el horero es menor a 10
    lcd.setCursor(0, 0);     // Se imprimira en la columna 0 fila 0 --> el 0
    lcd.print(0);
    lcd.setCursor(1, 0);     // Se imprimira en la columna 1 fila 0 --> el ho
    lcd.print(h);
  }
  else {
    lcd.setCursor(0, 0);      // Se imprimira en la columna 0 fila 0 --> el ho
    lcd.print(h);
  }
}
void talarma() {         //Funcion talarma
  j++;                     // incremento en 1
}
void ho() {              //Funcion ho
  h++;                     // incremento en 1
}
void mi() {              //Funcion mi
  m++;                     // incremento en 1
}
void confalarma() {       //Funcion confalarma
  if (k == 0) {              //Si k es igual a 0
    Serial.println("ingrese hora de alarma");  // Se imprimira la frase "ingrese hora de alarma"
    delay(1000);
    if (Serial.available() > 0) {     //Se valida el dato
      dato = Serial.readString();       // Se lee el dato
      H = dato.toInt();                 // Se transforma el dato a entero
      EEPROM.write(3, H);               //Se escribe en la posicion de memoria 3 el dato
      delay(1000);
      k = 1;
    }
  }
  if (k == 1) {                       //Si k es igual a 1
    Serial.println(' ');
    Serial.println("ingrese minutos de la alarma");    // Se imprimira la frase "ingrese minutos de la alarma"
    delay(1000);
    if (Serial.available() > 0) {         //Se valida el dato
      dato = Serial.readString();            // Se lee el dato
      M = dato.toInt();                     // Se transforma el dato a entero
      EEPROM.write(4, M);                   //Se escribe en la posicion de memoria 4 el dato
      delay(1000);
      k = 2;
    }
  }
  if (k == 2) {                           //Si k es igual a 1
    Serial.println(' ');
    Serial.println("La alarma ingresada es: ");       // Se imprimira la frase "La alarma ingresada es"
    Serial.print(EEPROM.read(3));                     //Se escribe en la posicion de memoria 3 el dato
    Serial.print(':');
    Serial.print(EEPROM.read(4));                       //Se escribe en la posicion de memoria 4 el dato
    k = 3;
  }
}
void alarma() {                               //Funcion alarma
  if (d == 0) {
    if (m == M && h == H && i == 0 ) {              // Se iguala las anteriores variables y compara
      digitalWrite(10, HIGH);  
      delay(1000);// pin 10 encendido
      MsTimer2::start();
      Serial.print("alamra activa");
      j = 0;
    }
    if (j == 1) {                                    //Si j es igual a 21
      digitalWrite(10, LOW);                            //Se establece en bajo el pin 10
      j = 0;
      M++;
      //Estructura de la Modificacion de Alarma
      Serial.print("La nueva alarma: ");
      Serial.print(H);
      Serial.print(':');
      Serial.print(M);
      MsTimer2::stop();
    }
  }
  else {
    //Serial.print("Alarma Apagada");
    digitalWrite(10, LOW);                            //Se establece en bajo el pin 10
    d = 1;
    MsTimer2::stop();
    j = 0;
  }
}
void detener() {                                 //Funcion detener
  if ( digitalRead(12) == LOW)                     // si el estado del pulsador  en esa posicion esta en bajo ->  d=0
    d = 0;
  if ( digitalRead(12) == HIGH)                     // si el estado del pulsador  en esa posicion esta en alto ->  d=1
    d = 1;
}
