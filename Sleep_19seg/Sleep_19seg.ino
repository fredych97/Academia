/*
 *                                                              UNIVERSIDAD TÉCNICA DEL NORTE
 *                                                                      FICA-CIERCOM
 *                                                                 SISTEMAS MICROPROCESADOS
 *      Nombre: Fredy Chicaiza
 *      Fecha: 5-2-2019
 *      Actividad: Realizar un programa que permita poner al sistema 19 segundos en modo sleep, se despierte, 
 *      realice un lectura del conversor análogo digital, lo imprima por comunicación serial y vuelva a dormir 
 *      19 segundos.
 */
//Librerias a Utilizar
#include <LowPower.h>
#include <MsTimer2.h>

 float slp;
void setup() {
  Serial.begin(9600);                  // Se debe inicializar la comunicacion serial
  MsTimer2::set(1000, rutina);         // ingreso parametros el timer y su metodo
  MsTimer2::start();                   //inicio del timer
  Serial.print("Iniciando Sistema");   // mensaje de inicio
  Serial.println(analogRead(0));       // Se ejecuta la lectura del CAD

}



void loop() {
 
}
void () {

  //19 segundos /8 segundos =2.375 por lo tanto como solo reconoce un valor de 8 segundos si se aumenta 8 segundos-> 2.375 veces daria un valor de 19 segundos 
for(slp=2.375;slp>0;slp--){
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //Funcion de la libreria LowPower
 
  }
}
