/*                                        UTN-FICA-CIERCOM
 *                              ASIGNATURA:SISTEMAS MICROPROCESADOS
 *                              FECHA:12-11-2018
 *                              NOMBRE: Fredy Chicaiza
 *                              TEMA:Comunicacion Serial                            
 * Deber:
 * Estimados estudiantes realizar un sistema que permite determinar el número de vocales dentro de una palabra. 
 * Este dato es ingresado por comunicación serial y la respuesta del mismo de igual manera. 
 * Subir su link de github. Ejemplo 1: Ingreso: CIERCOM Retorna: 3 Ejemplo 2. Ingreso: DATOS Retorna: 2
 */

int contador=0;                         //Variable contador
String str;                             //Variable String
char palabra;                           //Variable Palabra 
int tam_Palabra;                        //Variable tamaño de Palabra
int i=0;

void setup() {
 Serial.begin(9600); 

}

void loop() {
 if(Serial.available()>0){               //Validacion de la cx.
 str=Serial.readString();                //Serial.readString:su funcion es leer los datos ingreado
 tam_Palabra=str.length();               //Longitud del string y lo guarda en la variable tam_Palabra
 char vec[tam_Palabra];                  //El valor tam_Palabra corresponde al vec(vector)-->que vendria hacer una (cadena char)
 str.toCharArray(vec,tam_Palabra+1);     //Convierte el string a char con el tam_Palabra 
 palabra=vec[0];                         //La variable palabra sera igual a el vector inicializado en la posicion 0 
 delay(600);                             // Tiempo de espera y analisis.
 for (i=0;i<15;i++){                     //Recorre cada dato de la palabra que se ingrese y busca las vocales.
 if (vec[i]=='A'                         //Si el vector en cada posicion encuentra una vocal Mayuscula la almacena.
|| vec[i]=='E' 
|| vec[i]=='I' 
|| vec[i]=='O' 
|| vec[i]=='U'
|| vec[i]=='a'                           //Si el vector en cada posicion encuentra una vocal Minuscula la almacena.
|| vec[i]=='e' 
|| vec[i]=='i' 
|| vec[i]=='o' 
|| vec[i]== 'u')
 {
 contador++;                             // se almacena en la variable contador y comencera a  aumentar. 
 }
  } 
 Serial.println("");    
 Serial.println("El numero de vocales es: ");           //Se imprime el texto "El numero de vocales es: " en la terminal
 Serial.println(contador);                           //Se imprime el numero de vocales que se encuentran en la palabra ingresada 
 contador=0;                                           //Volvera a 0 para que se pueda analizar otra palabra 
   }
 }
