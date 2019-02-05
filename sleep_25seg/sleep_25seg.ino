/*
 *                                                              UNIVERSIDAD TÉCNICA DEL NORTE
 *                                                                      FICA-CIERCOM
 *                                                                 SISTEMAS MICROPROCESADOS
 *      Nombre: Fredy Chicaiza
 *      Fecha: 5-2-2019
 *      Actividad: Realizar un sistema que permita configurar por comunicación serial o por pulsadores el modo sleep cada 25 segundos.
 */
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
 int i = 0;
 char dato;
 int f = 0;
 void setup() {
 Serial.begin(9600);
 set_sleep_mode(SLEEP_MODE_PWR_DOWN);
sleep_enable();
  Serial.println("seleccion el tiempo para dormir al sistema");
   }
  void loop() {
  if (f == 0) {                  //Si f es igual a 0
  if (Serial.available() > 0) {   //Se activa la comunicacion serial
  dato = Serial.read();        //El dato es leido
   }
Serial.println(dato);      //Se imprime  el dato
delay(3000);               
 if (dato != 0)             //Si el dato no es igual a cero
    f = 1;                  //f e igual a 1
   }  
  if (f == 1) {                 //Si f es igual a 1
  if (dato == '1') {            //Si el dato es igual a 1
    sleep_mode();               //Manda a dormir  
  wdt_enable(WDTO_1S);          //Durante un segundo
  Serial.println("1 seg");      //Se imprime "1 seg"
  sleep_disable();              //Se desactiva el modo sleep
  }
  if (dato == '2') {            //Si f es igual a 2
       sleep_mode();            //Manda a dormir  
  wdt_enable(WDTO_2S);          //Durante 2 segundos
   Serial.println("2 seg");     //Se imprime "2 seg"
   sleep_disable();             //Se desactiva el modo sleep
  }
  if (dato == '4') {            //Si f es igual a 4
       sleep_mode();            //Manda a dormir 
  wdt_enable(WDTO_4S);          //Durante 4 segundos
  Serial.println("4 seg");      //Se imprime "4 seg"
    sleep_disable();            //Se desactiva el modo sleep
  }
  if (dato == '8') {            //Si f es igual a 8
       sleep_mode();            //Manda a dormir 
  wdt_enable(WDTO_8S);          //Durante 8 segundos
  Serial.println("8 seg");      //Se imprime "8 seg"
    sleep_disable();            //Se desactiva el modo sleep
    }
    f = 2;                      //f es igual a 2      
    }
   if (f == 2) {                //Si f es igual a 2      
        i++;
  Serial.println(i);            //Se imprime el dato "i"
  delay(1000);
   }
  }
