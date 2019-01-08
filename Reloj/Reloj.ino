
/*
 *                                                              UNIVERSIDAD TÉCNICA DEL NORTE
 *                                                                      FICA-CIERCOM
 *                                                                 SISTEMAS MICROPROCESADOS
 *      Nombre: Fredy Chicaiza
 *      Fecha: 8-1-2019
 *      Actividad: Suba su programa de un programa que muestre el segundero, minutero y horero visto en una lcd.
 */
#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(13,12,11,10,9,8);
int seg = 0;
int minu = 0;
int ho = 0;
void setup() {
lcd.begin(16, 2);
Timer1.initialize(1000000);   // Contador a 1 seg
Timer1.attachInterrupt(cont);    // Se configurara el metodo
attachInterrupt(0, horero, LOW);
attachInterrupt(1, minutero, LOW);
}
void loop() {
 minutos(); //funcion minutos
 segundos();//funcion segundos
 horas(); //funcion horas
 if (ho > 23) //Si el ho llega a 23  reiniciara empezando desde 0
  ho = 0;      
 estructuraLcd();  //funcion estructura LCD
}
void cont() { // Funcion contador
 seg++;        //Incrementara en 1
 if (seg > 59) {  //Si el seg llega a 59 el  reinicia empezando desde 0
 seg = 0;
 minu++;    //Incrementara en 1 el minu
}
 if (minu > 59) {  //Si el seg llega a 59 el  reinicia empezando desde 0
  minu = 0;
   ho++;
}
}
void segundos() { // Funcion  segundos
if (seg < 10) {     //Si el seg es menor a 10 
 lcd.setCursor(9, 0); // Se imprimira en la columna 9 fila 0 --> el 0
 lcd.print(0);
 lcd.setCursor(10, 0); // Se imprimira en la columna 10 fila 0 --> el seg
 lcd.print(seg);
}
else {
  lcd.setCursor(9, 0); // Se imprimira en la columna 9 fila 0 --> el seg
  lcd.print(seg);
}
}
void minutos() { // Funcion  minutos
if (minu < 10) { //Si el minu es menor a 10 
  lcd.setCursor(6, 0);  // Se imprimira en la columna 6 fila 0 --> el 0
  lcd.print(0);
  lcd.setCursor(7, 0); // Se imprimira en la columna 7 fila 0 --> el minu
  lcd.print(minu);
}
else {
 lcd.setCursor(6, 0);  // Se imprimira en la columna 6 fila 0 --> el minu
 lcd.print(minu);
}
}
void minutero() {
 minu++;               // El minutero se incrementa en 1 
}
void horas() {   // Funcion  horas
if (ho < 10) {   //Si el ho es menor a 10 
lcd.setCursor(3, 0); // Se imprimira en la columna 3 fila 0 --> el 0
lcd.print(0);
lcd.setCursor(4, 0); // Se imprimira en la columna 4 fila 0 --> el ho
lcd.print(ho);
}
else {
lcd.setCursor(3, 0); // Se imprimira en la columna 3 fila 0 --> el ho
lcd.print(ho);
}
}
void horero() {  // Funcion  horero
 ho++;            // El horero se incrementa en 1 
}
void estructuraLcd(){  // Funcion  estructura de la Lcd
 lcd.setCursor(5, 0);  // Se imprimira en la columna 5 fila 0 --> :
 lcd.print(':');
 lcd.setCursor(8, 0);   // Se imprimira en la columna 8 fila 0 --> :
 lcd.print(':');
 lcd.setCursor(11, 0);  // Se imprimira en la columna 11 fila 0 -->
 lcd.print(' ');
 lcd.setCursor(2, 1);  // Se imprimira en la columna 2 fila 1 --> hor/min/seg
 lcd.print("hor/min/seg");
   
  }
