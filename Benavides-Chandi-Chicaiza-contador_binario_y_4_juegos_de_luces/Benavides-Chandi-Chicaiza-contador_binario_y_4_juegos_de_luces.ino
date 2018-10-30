/*
 * UNIVERSIDAD TECNICA DEL NORTE
 * FICA-CIERCOM
 * SISTEMAS MICROPROCESADOS
 * Puertos entrada-salida
 * INTEGRANTES: WILMER BENAVIDES, FREDY CHICAIZA, ARMANDO CHANDI
 * Ejercicios arduino 
 * 1. Realizar un cotador binario de 1 al 31 
 * 2. Realizar 4 juegos de luces que sean controladas por un dip-switch
 */
int j=1;
int i=0;
int numero=0; //el contador inicia en 0 y se aumentara cuando se presione el pulsador 
int leds[5]={2,3,4,5,6};// pin destiandos como salida para led
int sw0=7; // pin para el pulsador
int sw=8;// pin para el switch
int sw1=9; // pin para el switch
int sw2=10;// pin para el switch
int sw3=11;// pin para el switch
void setup() {
for(;i<6;i++){
     pinMode(leds[i],OUTPUT);// leds declarados como salida
    }
    i=0;
    pinMode(sw1,INPUT);//sw como entrada
    pinMode(sw2,INPUT);//sw como entrada
    pinMode(sw3,INPUT);//sw como entrada
    pinMode(sw,INPUT);//sw como entrada
    pinMode(sw0,INPUT);//pulsador como entrada
}
void loop() {
  //* PIN 7 DE ENTRADA
  //* CONTADOR BINARIO DE 1 A 31 
int k; // Declaro variable k
if (digitalRead(sw0)==HIGH){ // Si presiono el pulsador
numero++; // Aumento el contador
if (numero>32){ // Cuando el contador llega a 32, 5 bits 5 leds
numero=0; // vuelve a 0
}
while (digitalRead(sw0)==HIGH){} // mientras el pulsador este en HIGH no hace nada mas
}
k=numero; // El numero va a variable k
for(int i=2; i<=6; i++){ //Ciclo para ver que leds prendo intervalo de leds descrito de otra manera (orden de los pines 2,3,4,5,6)
digitalWrite(i, k%2); // modulo de la division por 2 para ver si led prendido o apagado
k=k/2; // Se divide el cociente entre 2 por cada ciclo
}
//*PIN 8 DE ENTRADA
if(digitalRead(sw)==HIGH){// pregunta si switch esta en alto o enviando una señal activo
for(;i<6;i++){ // mientras el numero sea menor a 6 habra un incremento
digitalWrite(leds[i],HIGH);  // encendiendo posicion i del vector (incremento)
delay(200);// tiempo de espera de 200 ms
i=i+1;// incremento del contador ya que solo se encienden las pociones 1-3-5
 }
for(;i>0;i--){
digitalWrite(leds[i],LOW);  // encendiendo posicion i del vector
delay(200);
i=i+1; // incremento de 1 para realizar el apagado en el mismo orden que se encendieron los leds 
}}   

//* PIN 9 DE ENTRADA 
 else if (digitalRead(sw1)==HIGH){// pregunta si switch esta en alto
  for(;i<6;i++){
    digitalWrite(leds[i],HIGH);  // encendiendo posicion i del vector
     delay(200);                  //espero
      digitalWrite(leds[i],LOW);   // apago posicion i del vector
       delay(200);                   //espero
    }
    i=0;    // reset de variable de conteo
    
    for(;i<6;i++){
      digitalWrite(leds[i],HIGH);  // encendiendo posicion i del vector
       delay(200);  
      }
     for(;i>=0;i--){
      digitalWrite(leds[i],LOW);  // encendiendo posicion i del vector
       delay(200); 
      }
      }
  //*PIN 10 DE ENTRADA 
       else if (digitalRead(sw2)==HIGH){ // pregunta si switch esta en alto
         i=0;  // j=5 
      for(;i<3;i++){//contador del 0 al 3
        digitalWrite(leds[i],HIGH);// enciende el juego de luces
        digitalWrite(leds[4-i],HIGH);// enciende el juego de luces hasta la mitad y regresa
        delay(200);
        }
        i=2;
        for(;i>=0;i--){
          digitalWrite(leds[i],LOW);// apagamos los leds
           digitalWrite(leds[4-i],LOW);
          delay(200);
          }
     i=0;

       }
    //* PIN 11 DE ENTRADA 
        else if (digitalRead(sw3)==HIGH){
         while(i>6);// mientras sea mayor a 6 sigue trabajando
          int num=random(0,6);//generacion de numeros randomicos 
           for(i=0;i<num;i++){ // ciclo repetevitivo 
             digitalWrite(leds[i],HIGH);  // encendiendo posicion i del vector
              delay(200);  
      }
     for(i=0;i<num;i++){
      digitalWrite(leds[i],LOW);  // encendiendo posicion i del vector
       delay(200);
       }
       }
       
      else
        digitalWrite(leds[i],LOW);// que todos los leds permanescan apagados
}
