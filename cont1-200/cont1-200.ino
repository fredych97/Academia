/*
 *                                              UNIVERSIDAD TECNICA DEL NOERTE 
 *                                                      FICA-CIERCOM
 * NOMBRE:FREDY CHICAIZA                       
 * ASIGNATURA:SISTEMAS MICROPROCESADOS
 * ORDEN:Estimados estudiantes realizar un sistema que permita contar de forma automática (sin pulsador, 
 *       el sistema inicia y empieza a contar sin necesidad de una actividad del usuario). Del 1 al 200 mediante la multiplexación de displays.
 */

//Display 7 Segmentos Catodo Común
//Para mostrar los números en un display de 7 segmentos,
//debemos proporcionar con el ARDUINO la secuencia de la tabla de verdad de los displays de Cátodo común:
int display7c[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
//Delcaración de Los Pines del Display
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;
// Declaración de los Pines de los Transistores

byte t2=10;
byte t3=11;
byte t4=12;
//Contadores para hacer el Temporizador
long tempor=0,contret=0;
//Función que coloca en el puerto de salida los bits comenzando
// desde el pin ini hasta el pin fin
void puerto(int bits,int ini,int fin){
for(int i=ini;i<=fin;i++)
{
digitalWrite(i,bitRead(bits,i-ini));
}
}
//Función encargada de la multiplexación
void mostrar( ) //Rutina mostrar
{
int dig[3];   //Declarar las variables
//como un entero, es decir de 8bits
//Dígito Millar
dig[0]=tempor/100;
//Dígito Centena
dig[1]=(tempor-dig[0]*100)/10;
//Dígito Decena
dig[2]=(tempor-dig[0]*100-dig[1]*10);

//Rutina de Multiplexación
for(int i=t2;i<=t4;i++){ 
//Muestra unidades
puerto(display7c[dig[i-t2]],a,g); 
digitalWrite(i,HIGH);  //Enciende el display de unidades
delay(10);               //Retardo de 1 milisegundos
digitalWrite(i,LOW);   //Apaga el display de unidades
}                      
}
//Función que cuenta el tiempo que le toma al temporizador incrementar su cuenta
void temporizacion() 
{
contret=10;       //Cargue con 10 la variable CONTRET
while (contret>0) //Mientras que la variable CONTRET sea mayor que cero
{
mostrar();        //Llamar la rutina MOSTRAR
contret--;        // Decremente la variable CONTRET
}
}
//Configura todos los pines como Salidas
void setup() {
//Configura los 8 Pines digitales como SALIDAS
for(int i=a;i<=t4;i++){
pinMode(i,OUTPUT);
}
}
//Programa Principal
void loop() {
tempor=1;  //Inicializa el temporizador en Uno
while(tempor<=200) //mientras la variable TEMPOR es menor que 9999
{
temporizacion(); //Llama la Función Temporizador
tempor++;        //Incrementa el tempor 
}
}
