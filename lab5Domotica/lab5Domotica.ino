/*
                                                                UNIVERSIDAD TÉCNICA DEL NORTE
                                                                        FICA-CIERCOM
                                                                   SISTEMAS MICROPROCESADOS
        Integrantes: Benavides Wilmer
                     Chandi    Bryan 
                     Chicaiza  Fredy
                     
        Fecha: 17-1-2019
        Actividad:  
        
        Realizar el sistema demótico que tenga 3 sensores ubicados en puertas y ventana. 
        Debe guardar la hora en la memoria EEPROM cuando suceda algún inconveniente después que la casa sea asegurada. 
        Para ello, debe ingresar una contraseña de 5 dígitos (guardados en la EEPROM) que dará 25 segundos para salir 
        de la casa y que los sensores se activen. Si la alarma se enciende, obligatoriamente debe digitar la contraseña 
        para apagarla.Además, debe tener una función de poder cambiarla en caso de necesitarlo. El ingreso de la misma 
        puede ser por teclado matricial o comunicación serial. Toda la información del estado de la alarma se lo debe 
        visualizar en una Lcd.
*/



#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <MsTimer2.h>
#include<avr/wdt.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //RS-E-D4-D5-D6-D7 //distribucion de pides de la lcd en el arduino
char buffer_EEPROM[6];
int tiempo = 0;
int cont = 0;
int bandera = 0;
int bandera1 = 0;
int bocina = 4, sonido = 0;
int a = 0, b = 0, c = 0, d = 0;
int seg = 0, minut = 0, hor = 0;
int direccion = 0;
String dato, dato1;
int secuencia = 0;
char pass[] = {'1', '1', '1', '1', '1'}; //clave de acceso
int sw , sw1 = 0;
int p1 = 7, p2 = 6, v = 5; //entrada para los sensores de puertas y ventana
int minutero, horero, val; //variables donde se guarda la hora
int x, y, z; // variables de entrada de las puertas y ventana
int rev_puerta1 = 0;
int rev_puerta2 = 0;
int rev_ventana = 0;
int fun = 0;
void setup() {
  minutero = EEPROM.read(10);
  horero = EEPROM.read(11);
  val = EEPROM.read(12);
  MsTimer2::set(500, reloj);
  MsTimer2::start();
  Serial.begin(9600);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(v, INPUT);
  pinMode(bocina, OUTPUT);
  attachInterrupt(1, on, RISING);
  attachInterrupt(0, activar, RISING);
  lcd.begin(16, 2); // lcd de 16x2
  x = digitalRead(p1);
  y = digitalRead(p2);
  z = digitalRead(v);
  lcd.setCursor(2, 0); // ubicacion del cursor dentrol de la lcd-columna,fila
  lcd.print(":"); //impresion que se desea mostrar en la lcd
  lcd.setCursor(5, 0);
  lcd.print(":");
  lcd.setCursor(0, 0);
  lcd.print('0');
  lcd.setCursor(1, 0);
  lcd.print('0');
  lcd.setCursor(3, 0);
  lcd.print('0');
  lcd.setCursor(4, 0);
  lcd.print('0');
  lcd.setCursor(6, 0);
  lcd.print('0');
  lcd.setCursor(7, 0);
  lcd.print('0');
  // borrar();
  Escribir_EEPROM(pass);
}


void loop() {

  intruso();
  resultados();
  if (sw == 2) {
    validar_pass(buffer_EEPROM);
  }
  if (sw == 3) {
    passnew();
  }

  if (sw1 == 2) {
    validar_passnew(buffer_EEPROM);
  }
}
void bloqueo() {
  if (cont == 3) {
    for (int i = 0; i < 6; i++) {
      Serial.println("########################");
      Serial.println("####SISTEMA BLOQUEADO### ");
      Serial.println("########################");
      delay(200);
      cont = 0;
    }
  }
}


//metodo para escribir en la EEPROM
void Escribir_EEPROM(char *fra) {
  for (int i = 0; i < strlen(fra); i++) {
    EEPROM.write(i, fra[i]);

  }
}

//metodo para leer de la EEPROM
void Leer_EEPROM(char *buff) {
  for (int j = 0; j < 6; j++) {
    buff[j] = EEPROM.read(j);
  }
}
void validar_pass(char *buff1) {

  for (int i = 0; i < 6; i++) {
    buff1[i] = EEPROM.read(i);
  }
  //    Serial.println("INGRESE PASSOWORD");
  //    delay(1000);

  if (Serial.available() > 0) { // si se escrtito algo en el serial lee
    dato = Serial.readString(); // el serial lee el dato ingreado
    int tam = dato.length(); //determina la longitud del string y lo guarda en la variable tam
    char vector [tam];//el valor tam corresponde al vector (cadena char)
    dato.toCharArray(vector, tam + 1 ); //conversion de string a char con el tama
    //
    //Serial.println(vector );
    //Serial.println(buff1);
    // si supera el tamaño del anterior se ingresa un nuevo
    if (!(strncmp(vector, buff1, 5))) {
      Serial.println(" PASSWORD CORRECTO ");
      delay(1000);
      bandera1 = 1;
     digitalWrite(bocina, LOW);
    }
    else {// si no supera se imprime la anterior

      Serial.println("");
      Serial.println("PASSWORD INCORRECTA ");
      cont++;
      delay(1000);

    }
    bloqueo();
  }


}
void validar_passnew(char *buff1) {
//Serial.println("INGRESE PASSWORD");
  for (int i = 0; i < 6; i++) {
    buff1[i] = EEPROM.read(i);
  }

  if (Serial.available() > 0) { // si se escrtito algo en el serial lee
    dato = Serial.readString(); // el serial lee el dato ingreado
    int tam = dato.length(); //determina la longitud del string y lo guarda en la variable tam
    char vector [tam];//el valor tam corresponde al vector (cadena char)
    dato.toCharArray(vector, tam + 1 ); //conversion de string a char con el tama
    // si supera el tamaño del anterior se ingresa un nuevo
    if (!(strncmp(vector, buff1, 5))) {
      Serial.println("");
      Serial.println(" PASSWORD CORRECTO ");
      delay(1000);
      bandera=1;

   


    }
    else {// si no supera se imprime la anterior

      Serial.println("");
      Serial.println("PASSWORD INCORRECTA ");
      cont++;
      delay(1000);

    }
    bloqueo();
  }


}

//metodo de borrar EEPROM
void borrar() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("Memoria EEPROM borrada!");

}
void passnew() {
  validar_passnew(buffer_EEPROM);
  if (bandera == 1) {
    Serial.println("");
    Serial.println("INGRESE NUEVO PASSWORD ");
    delay(5000);
    if (Serial.available() > 0) { // si se escrtito algo en el serial lee
      dato1 = Serial.readString(); // el serial lee el dato ingreado
      int tam1 = dato1.length(); //determina la longitud del string y lo guarda en la variable tam
      char vector1 [tam1];//el valor tam corresponde al vector (cadena char)
      dato1.toCharArray(vector1, tam1 + 1 );
      Serial.println(tam1);
      if (tam1 == 6) {
        Escribir_EEPROM(vector1);
        Serial.println("");
        Serial.println("PASSWORD INGRESADA CORRECTAMENTE");
        delay(1000);
        sw = 0;
      } else {
        Serial.println("PASSWORD NO CUMPLE LOS PARAMETROS");
        delay(1000);

      }
    }
  }
}

void activar() {


  switch (sw) {
    case 0:
      Serial.println("SISTEMAS ON");
      delay(40);
      sw++;;
      break;
    case 1:
      Serial.println("INGRESE PASSWORD");
      delay(40);
      sw++;;
      break;
    case 2:
      Serial.println("MODIFICAR PASSWORD");
      delay(40);
      sw++;;
      break;
    case 3:
      Serial.println("SISTEMA OFF");
      delay(40);
      sw = 0;
      break;
  }
}
void reloj() {
  seg++; //incremento de segundos, variable inicial
  if (seg < 10) { //si segundos es menor a 10
    lcd.setCursor(7, 0); //se muestra el conteo en la columna 7 de la fila 0
    lcd.print(seg); //se imprime el valor del conteo
    lcd.setCursor(6, 0); //en la columna 6 y fila 0
    lcd.print('0'); //se imprime cero
  } else { //caso contrario los valores
    lcd.setCursor(6, 0); //se imprimen en la columna 6 fila 0
    lcd.print(seg);
  } //valores que tiene el conteo de segundos
  if (seg == 60) { //si el conteo de la variable seg llega a 60
    seg = 0; //la variable seg vuelve a ser 0 y se reinicia el conteo
    lcd.setCursor(6, 0); //en la columna 6 fila 0
    lcd.print(seg); //se vuelve a imprimir los valores dela variable seg
    seg++; //incrementos de valores en la variable
    minut++; //la variable minut empieza su incremento
    if (minut < 10) { //si minut es menor que 10
      lcd.setCursor(4, 0); //el cursor se ubica en la columna 4 fila 0
      lcd.print(minut); //se imprime el valor dela variable minut
      lcd.setCursor(3, 0); // y en la posicion columna 3 fila 0
      lcd.print('0');
    }// se imprime 0
    else { //caso contrario
      lcd.setCursor(3, 0); //en la posicion columna 3 fila 0
      lcd.print(minut); //se imprime el valor de conteo de la variable minut
    }
    if (minut == 60) { //si minut llega a 60
      minut = 0; //minut toma el valor de 0
      lcd.setCursor(4, 0); //el cursor en la posicion columna 4 fila 0
      lcd.print(minut); //se imprime el valor de la variable minut
      lcd.setCursor(3, 0); //el cursor esta en la posicion columna 3 fila 0
      lcd.print('0');  //se imprime el valor de 0
      hor++; //se incrementa la variable hor
      lcd.setCursor(0, 0); //cursor se ubica en la columna 0 fila 0
      lcd.print('0'); //se imprime el valor 0
      lcd.setCursor(1, 0); //en la columna 1 fila 0
      lcd.print('0'); // se imprime el valor 0
      if (hor < 10) { // si hor es menor a 10
        lcd.setCursor(1, 0); //en la columna 1 fila 0
        lcd.print(hor); // se imprime el valor de hor
        lcd.setCursor(0, 0); //en la columna 0 fila 0
        lcd.print('0'); //se imprime el valor 0
      } else { //caso contrario
        lcd.setCursor(0, 0); //en la columna 0 de la fila 0
        lcd.print(hor); //se imprime el valor de la variable hor
      }
    }
    if (seg == 60 && minut == 60 && hor == 24) { //si hora,minutos y segundos llegan a sus limites
      hor = 0;
      minut = 0; //las variables se reestablecen a 0
      hor = 0;
      lcd.setCursor(1, 0); // y se repite el ciclo
      lcd.print(hor);
      lcd.setCursor(4, 0);
      lcd.print(minut);
      lcd.setCursor(7, 0);
      lcd.print(seg);
      lcd.setCursor(0, 0);
      lcd.print('0');
      lcd.setCursor(3, 0);
      lcd.print('0');
      lcd.setCursor(6, 0);
      lcd.print('0');
    }
  }
  if ((bandera1 == 1) && (seg == 50)) {
    Serial.println("SISTEMA ACTIVADO");
    intruso();
    resultados();
    guardar_HORA();
  }
}
void guardar_HORA() {
  int h = hor;
  int m = minut;
  int s = seg;
  if (a == LOW) {
    if (rev_puerta1 == 0) {
      fun = EEPROM.read(20);
      fun = fun + 1;
      EEPROM.update(20, fun);
      EEPROM.update(22, m);
      EEPROM.update(21, h);
      rev_puerta1 = 1;
      Serial.println("Entrada por la puerta 1");
      Serial.print(h);
      Serial.print(":");
      Serial.print(m);
      Serial.print(":");
      Serial.println(s);
      delay(500);
    }
  }
  if (b == LOW) {
    if (rev_puerta2 == 0) {
      fun = EEPROM.read(20);
      fun = fun + 5;
      EEPROM.update(20, fun);
      EEPROM.update(22, m);
      EEPROM.update(21, h);
      rev_puerta2 = 1;
      Serial.println("Entrada por la puerta 2");
      Serial.print(h);
      Serial.print(":");
      Serial.print(m);
      Serial.print(":");
      Serial.println(s);
      delay(500);
    }
  }
  if (c == LOW) {
    if (rev_ventana == 0) {
      fun = EEPROM.read(20);
      fun = fun + 7;
      EEPROM.update(20, fun);
      EEPROM.update(22, m);
      EEPROM.update(21, h);
      rev_ventana = 1;
      Serial.println("Entrada por la ventana");
      Serial.print(h);
      Serial.print(":");
      Serial.print(m);
      Serial.print(":");
      Serial.println(s);
      delay(500);
    }
  }
}
void resultados() {
  switch (fun) {
    case 1:
      Serial.println("Ingreso por puerta1");
      delay(2000);
      break;
    case 5:
      Serial.println("Ingreso por puerta2");
      delay(2000);
      break;
    case 6:
      Serial.println("Ingreso por puerta1 y puerta2");
      delay(2000);
      break;
    case 7:
      Serial.println("Ingreso por ventana");
      delay(2000);
      break;
    case 8:
      Serial.println("Ingreso por puerta1 y ventana");
      delay(2000);
      break;
    case 12:
      Serial.println("Ingreso por puerta2 y ventana");
      delay(2000);
      break;
    case 13:
      Serial.println("SENSORES ACTIVADOS :(");
      delay(2000);
      break;
  }
}
void on() {
  switch (sw1) {
    case 0:
      Serial.println("INFORMACION DE ALARMA");
      delay(100);
      resultados();
       rev_puerta1 = 0;
      rev_puerta2 = 0;
      rev_ventana = 0;
      Serial.print(EEPROM.read(21));
      Serial.print(":");
      Serial.print(EEPROM.read(22));
      fun = 0;
      EEPROM.update(20, fun);
      Serial.println(EEPROM.read(20));
      sw1++;
      break;
    case 1:
      Serial.println("SISTEMA OFF");
      delay(100);
      sw1 = 0;
      break;
  }
}


void intruso() {
  a = digitalRead(p1);
  b = digitalRead(p2);
  c = digitalRead(v);
  d = digitalRead(bocina);
  if (a == LOW || b == LOW || c == LOW) {
    Serial.println("***INTRUSO**");
    delay(200);
    lcd.setCursor(0, 1);
    lcd.print("*INTRUSO*");
    digitalWrite(4, HIGH);
    delay(1000);
    //digitalWrite(4, LOW);
    lcd.clear();
    lcd.setCursor(2, 0); // ubicacion del cursor dentrol de la lcd-columna,fila
    lcd.print(":"); //impresion que se desea mostrar en la lcd
    lcd.setCursor(5, 0);
    lcd.print(":");
    lcd.setCursor(0, 0);
    lcd.print('0');
    lcd.setCursor(1, 0);
    lcd.print('0');
    lcd.setCursor(3, 0);
    lcd.print('0');
    lcd.setCursor(4, 0);
    lcd.print('0');
    lcd.setCursor(6, 0);
    lcd.print('0');
    lcd.setCursor(7, 0);
    lcd.print('0');
    reloj();
  }
}
