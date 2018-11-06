/*                                 UNIVERSIDAD TECNICA DEL NOERTE 
 *                                          FICA-CIERCOM
 *NOMBRE: FREDY CHICAIZA                       
 *ASIGNATURA:SISTEMAS MICROPROCESADOS
 *ORDEN:Realizar un programa que medienta un pulsador se aumente el valor de un contador (1 al 40) 
 *      y mediante otro pulsador se reste ese valor. El visualización del proceso se lo hace en displays. 
 */
 int A=5;  //Pin A del CI 7447
 int B=4;  //Pin B del CI 7447
 int C=3;  //Pin C del CI 7447
 int D=2;  //Pin D del CI 7447
 int btnIncremento=6;  //Boton para incrementar los numeros en el display de 7 segmentos
 int btnDecremento=7;  //Boton para decrementar los numeros en el display de 7 segmentos
 int i=0;              //Variable principal para realizar las respectivas  operaciones y funciones 
 int pinUni=8;         //Pin numero 8 que corresponde al display de las unidades
 int pinDec=9;         //Pin numero 9 que corresponde al display de las unidades
 int unidades;         //Variable  asignar las unidades mediante operaciones matematicas
 int decenas;          //Variable  asignar las decenas mediante operaciones matematicas
      
 
void setup() {
  pinMode(A,OUTPUT); //Definimos los  pines que funcionan como salida
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
pinMode(pinUni,OUTPUT);
pinMode(pinDec,OUTPUT);
  
     

}
void loop() {

  if(digitalRead(btnIncremento)==HIGH){   // Sentencia if que indica si  el boton de incremento  esta en alto(pulsado) debera cumplir los siguientes parametros
    delay(200);                           // Espera o retardo  de 200 milisegundos

   if(i<40){                              //Si cualquier digito del display  es menor a 40 debera cumplir los siguientes parametros
    i++;                                  //Se incrementara, el ++ indica que incrementara en  uno
      decenas= i/10;                      //Operacion que sirve  para que el display de decenas me muestre los valores(numeros) de acuerdo ala operacion establecida
                                          //en este caso esta operacion me vota el valor entero
    unidades= i-(decenas*10);             //operacion que sirve  para que el display de unidades me muestre los valores(numeros) de acuerdo ala operacion establecida
                                          
    
  
    }else{                                // si no cumple el requerimiento que sea menor a 40          
    i=0;                                  //el digito sera igual a cero
    unidades=0;                           //las unidades seran igual a cero
    decenas=0;                            //las decenas seran igual a cero
    }
      
    }
  
  if(digitalRead(btnDecremento)==HIGH){   // Sentencia if que indica si  el boton de decremento  esta en alto(pulsado) debera cumplir los siguientes parametros
    delay(200);                           // Espera o retardo  de 200 milisegundos
    
    if(i<=40){                            //Si cualquier digito del display  es menor o igual a 40 debera cumplir los siguientes parametros
    decenas= i/10;                        //Operacion que sirve  para que el display de decenas me muestre los valores(numeros) de acuerdo ala operacion establecida
                                          //en este caso esta operacion me vota el valor entero
    unidades= i-(decenas*10);             //operacion que sirve  para que el display de unidades me muestre los valores(numeros) de acuerdo ala operacion establecida
                                          
    i--;                                 //Se decrementara, el -- indica que decrementa en  uno
  }
  
  else{                                    // si no cumple el requerimiento que sea menor o igual  a 40 
    i=0;                                   //el digito sera igual a cero    
    unidades=0;                            //las unidades seran igual a cero
    decenas=0;                             //las decenas seran igual a cero
    }
    

  }                                         //Multiplexacion
  digitalWrite( pinUni,HIGH);              //Pin de unidades activado  
    digitalWrite(pinDec,LOW);              //Pin de  decenas desactivado
    display(unidades);                     //Llama a la funcion Display  operacion  unidades
    delay(100);                            // Espera o retardo  de 100 milisegundos
     digitalWrite( pinUni,LOW);            //Pin de unidades desactivado 
    digitalWrite(pinDec,HIGH);             //Pin de  decenas activado
    display(decenas);                      //Llama a la funcion Display la operacion decenas
    delay(100);                            // Espera o retardo  de 100 milisegundos
  
}
  void display(int j){               //Funcion display
    switch(j){                       //Menu de Digitos numericos
      
 //0
 case 0:
 digitalWrite(A,LOW);
 digitalWrite(B,LOW);
 digitalWrite(C,LOW);
 digitalWrite(D,LOW);
   break;
 //1
 case 1:
 digitalWrite(A,HIGH);
 digitalWrite(B,LOW);
 digitalWrite(C,LOW);
 digitalWrite(D,LOW);
 break;
 //2
 case 2:
  digitalWrite(A,LOW);
 digitalWrite(B,HIGH);
 digitalWrite(C,LOW);
 digitalWrite(D,LOW);
 break;
 //3
 case 3:
 digitalWrite(A,HIGH);
 digitalWrite(B,HIGH);
 digitalWrite(C,LOW);
 digitalWrite(D,LOW);
 break;
 //4
 case 4:
 digitalWrite(A,LOW);
 digitalWrite(B,LOW);
 digitalWrite(C,HIGH);
 digitalWrite(D,LOW);
 break;
 //5
 case 5:
 digitalWrite(A,HIGH);
 digitalWrite(B,LOW);
 digitalWrite(C,HIGH);
 digitalWrite(D,LOW);
 break;
 //6
 case 6:
 digitalWrite(A,LOW);
 digitalWrite(B,HIGH);
 digitalWrite(C,HIGH);
 digitalWrite(D,LOW);
 break;
 //7
 case 7:
 digitalWrite(A,HIGH);
 digitalWrite(B,HIGH);
 digitalWrite(C,HIGH);
 digitalWrite(D,LOW);
 break;
 //8
 case 8:
 digitalWrite(A,LOW);
 digitalWrite(B,LOW);
 digitalWrite(C,LOW);
 digitalWrite(D,HIGH);
 break;
 //9
 case 9:
 digitalWrite(A,HIGH);
 digitalWrite(B,LOW);
 digitalWrite(C,LOW);
 digitalWrite(D,HIGH);
 break;
 
  } 
}
