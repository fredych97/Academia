/*                                        UTN-FICA-CIERCOM
 *                              ASIGNATURA:SISTEMAS MICROPROCESADOS
 *                              FECHA:13-11-2018
 *                              NOMBRE: Fredy Chicaiza
 *                              TEMA:Comunicacion Serial                            
 * Deber:
 * Estimados estudiantes realizar un sistema que permite determinar el número de vocales dentro de una palabra. 
 * Este dato es ingresado por comunicación serial y la respuesta del mismo de igual manera. 
 * Subir su link de github. Ejemplo 1: Ingreso: CIERCOM Retorna: 3 Ejemplo 2. Ingreso: DATOS Retorna: 2
 */

char cedula[11];                                //vector cedula 
char validacion[11];                            //vector validacion
void setup() {                                  
  Serial.begin(9600);                           
  Serial.println("Ingrese su Cedula");          //Ingreso de cedula
  for(int i;i<11;i){                            //ciclo for para definir que se puede definir 10 datos
    if(Serial.available()>0){                   //Validacion de la cx.
      cedula[i]=Serial.read();                  //Serial.readString:su funcion es leer los datos ingresadoa
      i++;                                      //incremento
      }
    }
Serial.println("");
}

void loop() {
  Serial.println("Validacion de Cedula");       //Validacion de cedula
  for(int i;i<11;i){                            //ciclo for para definir que se puede definir 10 datos
    if(Serial.available()>0){                   //Validacion de la cx.
      validacion[i]=Serial.read();              //Serial.readString:su funcion es leer los datos ingreado
      i++;                                      //incremento
      }
      }
  Serial.println("");
  if(cedula[0]==validacion[0]&&cedula[1]==validacion[1]&&cedula[2]
  ==validacion[2]&&cedula[3]==validacion[3]&&cedula[4]==validacion[4]
  &&cedula[5]==validacion[5]&&cedula[6]==validacion[6]&&cedula[7]        //La cedula debe cumplir los datos digitados.
  ==validacion[7]&&cedula[8]==validacion[8]&&cedula[9]==validacion[9]
  &&cedula[10]==validacion[10])
  {
    Serial.println("cedula correcta");                                  //Mensaje de verificacion 
    Serial.println("");
    }else{
       Serial.println("cedula incorrecta");                             //Mensaje errones
       Serial.println("");
      }      
        
        
}
