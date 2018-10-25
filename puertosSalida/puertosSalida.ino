/*                                        UTN-FICA-CIERCOM
 *                              ASIGNATURA:SISTEMAS MICROPROCESADOS
 *                              FECHA:24-10-2018
 *                              NOMBRE: Fredy Chicaiza
 *                              TEMA:Puertos Como Salida                            
 * Deber:Nro1
 * 1.- Realizar un juego de lueces que se prendan secuencialmente los leds impartes (1,3,5). 
 * 2.- Realizar un programa que se enciendan uno por uno los leds pares (0,2,4). 
 * 3.- Realizar un juego que se enciendan y apaguen los leds de forma aleatoria. (Consultar random)
 */
 
int led[6]={1,2,3,4,5,6};
int ledi[3]={1,3,5};
int ledp[3]={2,4,6};
int l=0;
int i=0;
int p=0;
long randNumber;
int r=0;
void setup() {
  // put your setup code here, to run once:
  for (;l<6;l++){
  pinMode(led[l],OUTPUT);
  }
  l=0;
  for (;i<3;i++){
  pinMode(ledi[i],OUTPUT);
  }
  i=0;
  for (;p<3;p++){
  pinMode(ledp[p],OUTPUT);
  }
  p=0;

  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:

   for (;i<3;i++){
   digitalWrite(ledi[i],HIGH);//pines impares 1,3,5 en alto
   delay(200);//tiempo de espera de 200ms.
   }
   i=0;
   for (;i<3;i++){
   digitalWrite(ledi[i],LOW);//pines impares 1,3,5 en bajo
   delay(200);//tiempo de espera de 200ms.
   }
   
   for (;p<3;p++){
   digitalWrite(ledp[p],HIGH);//pin pares 2,4,6 en alto
   delay(200);//tiempo de espera de 200ms.
   }
   p=0;
   for (;p<3;p++){
   digitalWrite(ledp[p],LOW);//pines pares 2,4,6 en bajo
   delay(200);//tiempo de espera de 200ms.
   }

   r=random(1,7);
   for(l=0;l<r; l++){
   digitalWrite(led[l],HIGH); //pines 1,2,3,4,5,6 en ramdom  en alto.
   delay(200);//tiempo de espera de 200ms.
   }
   
  i=0;
}
