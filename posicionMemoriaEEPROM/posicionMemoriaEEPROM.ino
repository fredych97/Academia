/*
                                                                UNIVERSIDAD TÉCNICA DEL NORTE
                                                                        FICA-CIERCOM
                                                                   SISTEMAS MICROPROCESADOS
        Nombre: Fredy Chicaiza
        Fecha: 15-1-2019
        Actividad: Realice un sistema que guarde en una posición de la memoria EEPROM solo cuando su valor exceda a la anterior lectura.
*/
#include <EEPROM.h>

int inicial = 0, aux, prt = 0, pos = 0;// Posicion de la EEPROM
String valor;                          //Variables del Serial Read
void setup()
{
  Serial.begin(9600);
  
    EEPROM.write(inicial,aux);          // Escribe  la posicion y el valor numerico     
    Serial.print("EEPROM = ");          //Imprime la frase EEPROM=
    Serial.println(EEPROM.read(pos));   //Imprime el numero en esa posicion
}


void loop(){
  valor = Serial.readString();          //Lee el valor numerico
  aux = valor.toInt();                  //Transforma el valor a entero
if(aux != 0){                           //La variable aux debe ser diferente de cero
  if(aux > EEPROM.read(pos)){           //Si aux es mayor al dato que se lee en la posiscion
    Serial.println("NUMERO MAYOR");     //imprime la frase NUMERO MAYOR  
    EEPROM.write(pos,aux);              //Escribe y guarda el numero mayor
    Serial.print("EEPROM = ");          //imprime la frase EEPROM=
    Serial.println(EEPROM.read(pos));   //Imprime el numero Mayor
  }else{
    Serial.println("NUMERO MENOR");     //Imprime la frase NUMERO MENOR    
    Serial.print("EEPROM = ");          //Imprime la frase EEPROM=
    Serial.println(EEPROM.read(pos));   //Imprime el numero Menor
  }
}
  
}
