
/*
                                                                UNIVERSIDAD TÉCNICA DEL NORTE
                                                                        FICA-CIERCOM
                                                                   SISTEMAS MICROPROCESADOS
        Nombre: Fredy Chicaiza
        Fecha: 21-1-2019
        Actividad: Realizar un programa que permita que el conversor análogo digital configure al perro guardían a 10,20,30 y 40 segundos.
                   Este proceso se visualiza en una lcd.
*/
#include <LiquidCrystal.h>// Libreria de LCD
#include <avr/wdt.h>
LiquidCrystal lcd (9, 8, 7, 6, 5, 4); // RS,E.D4,D5,D6,D7-> Pines de arduino
float conversor; // variable que recibe el CAD
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REINICIADO");
  delay(3000);
}

void loop() {
  lcd.clear();
  conversor = analogRead(A0); // recibe dato del CAD

 //Como el CAD da valores  hasta 1023 entonces se divide para 5 para, obtener rangos de activacion del perro guardian quedando 5 secciones y dependiendo de la 
 //seccion donde se encuentre el potenciometro, cumplira el tiempo de espera y activara el perro guardian.La activacion se realiza mediante un pulsador conectado
 //a la entrada 10 del arduino, una vez pulsado este comenzara a correr el tiempo.
 
  if (digitalRead(10) == 0) {
    if (conversor > 204.0 && conversor < 408.0) {   //El conversor debe estar en un rango de 204 y 408 para activar el perro guardian en 10 segundos 
      lcd.setCursor(0, 0);
      lcd.print("Reinicio en 10s");
      delay(10000);
      wdt_enable(WDTO_15MS);
    } else {

      if (conversor > 408.0 && conversor < 612.0) {  //El conversor debe estar en un rango de 408 y 612 para activar el perro guardian en 20 segundos 
        lcd.setCursor(0, 0);
        lcd.print("Reinicio en 20s");
        delay(20000);
        wdt_enable(WDTO_15MS);
      } else {

        if (conversor > 612.0 && conversor < 816.0) { //El conversor debe estar en un rango de 612 y 816 para activar el perro guardian en 30 segundos 
          lcd.setCursor(0, 0);
          lcd.print("Reinicio en 30s");
          delay(30000);
          wdt_enable(WDTO_15MS);
        } else {
          if (conversor > 816.0 && conversor < 1023.0) { //El conversor debe estar en un rango de 816 y 1023 para activar el perro guardian en 40 segundos 
            lcd.setCursor(0, 0);
            lcd.print("Reinicio en  40s");
            delay(40000);
            wdt_enable(WDTO_15MS);
          } else {

            lcd.print("Ajuste el tiempo");
            delay(300);
          }
        }
      }
    }
  } else {



    if (conversor > 204.0 && conversor < 408.0) { //El conversor debe estar en un rango de 204 y 408 para activar el perro guardian en 10 segundos 
      lcd.setCursor(0, 0);
      lcd.print("Reinicio en 10s");
    } else {

      if (conversor > 408.0 && conversor < 612.0) { //El conversor debe estar en un rango de 408 y 612 para activar el perro guardian en 20 segundos 
        lcd.setCursor(0, 0);
        lcd.print("Reinicio en 20s");
      } else {

        if (conversor > 612.0 && conversor < 816.0) { //El conversor debe estar en un rango de 612 y 816 para activar el perro guardian en 30 segundos 
          lcd.setCursor(0, 0);
          lcd.print("Reinicio en 30s");
        } else {
          if (conversor > 816.0 && conversor < 1023.0) { //El conversor debe estar en un rango de 816 y 1023 para activar el perro guardian en 40 segundos  
            lcd.setCursor(0, 0);
            lcd.print("Reinicio en  40s");
          } else {

            lcd.print("Ajuste el Tiempo");
            delay(300);
          }
        }
      }
    }
  }
  delay(300);
}
