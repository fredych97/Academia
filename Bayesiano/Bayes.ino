#include "matriz_entrenamiento.h"
#include "ListLib.h"
  // Crear una nueva lista
  List<int> list;
/*
 * CLASIFICADOR BAYESIANO
 * saber cuantas etiquetas tiene el conjunto de datos
 * el # filas y columnas
 * 
 * 
 * etiquetas=1,2,3
 * 
 * p(1)=Sumatorias de todos los elementos con etiqueta 1 y la dividimos para el numero total de filas
 * p(2)=Sumatorias de todos los elementos con etiqueta 2 y la dividimos para el numero total de filas
 * p(3)=Sumatorias de todos los elementos con etiqueta 2 y la dividimos para el numero total de filas
 * 
 * p(x)=Sumatoria de los elemntos dentro de la circunferencia y dividir para el total de filas 
 *      *Como encontrar la circunfernecia?
 *                                      ->necesito sacar la distancia entre la nueva instancia y la base de datos
 *                                      ->encuentro la mayor distancia y divido para el resto de las distancias encontradas 
 *                                      ->Defino el radio de la circunferencia  (0,1) entre cero y uno
 *                                      ->seleccionar las filas que se encuentren dentro de la circunferencia
 *                                      
 * encontrar la probabilidad para que esta x corresponda a la etiqueta 1 P(x/1)= Realizo la sumatoria de todos los elementos que 
 * se encuentran en la circunferencia con etiqueta 1 y divido para todas las instancias de la misma etiqueta (numero de etiquetas)
 * 
 * encontrar la probabilidad para que esta x corresponda a la etiqueta 1 P(x/2)= Realizo la sumatoria de todos los elementos que 
 * se encuentran en la circunferencia con etiqueta 2 y divido para todas las instancias de la misma etiqueta (numero de etiquetas)
 * 
 * encontrar la probabilidad para que esta x corresponda a la etiqueta 1 P(x/3)= Realizo la sumatoria de todos los elementos que 
 * se encuentran en la circunferencia con etiqueta 3 y divido para todas las instancias de la misma etiqueta (numero de etiquetas)
 * 
 * P(1/x)= P(1)*P(x/1)/P(x)  (x)->etiqueta
 * 
 * P(2/x)= P(2)*P(x/2)/P(x)  (x)->etiqueta
 * 
 * P(3/x)= P(2)*P(x/3)/P(x)  (x)->etiqueta
 * 
 */

 float datos_prueba[5]={6,3,4.8,1.8,3};
void setup() {
  Serial.begin(9600);
}

void loop() {
  bayesiano(3,5,120,0.1);
  delay(300);
}

void bayesiano (int etiquetas, int columnas, int filas, float r){
float prob[4][etiquetas];

/*
  |1     |2     |3     |
  |sum1  |sum2  |sum3  | 40,40,40
  |P(x/1)|P(x/2)|P(x/3)| 0.12,0.18,0.75
  |P(1/x)|P(2/x)|P(3/x)| 
 */ 
 int i=0;
 int j=0;
 int k=0;
 int t=0;
 float distancia;
 float sumatoria=0.0;
 float dist_mayor=0.01;
 float normalizador;
 float p_x=0;
 int resultado;
 float aux=0.0;
// encerar matriz y asignar etiqueta a la fila 0
 for(i=0;i<4;i++){            //Recorre un numero de  filas menores a 4
  for(j=0;j<etiquetas;j++){   //Recorre un numero de  columnas menor a 3
      prob[i][j]=0;           //Se crea la matriz la cual esta compuesta por las filas y columnas recorridas y se la encera.
      if(i==0)                //Si i es igual a cero
      prob[i][j]=j+1;         //La matriz se compara con j+1
    }
  }


for(t=0;t<etiquetas;t++){             //Recorre un numero de  filas  menor a 3
    for(i=0;i<filas;i++){             //Recorre un numero de columnas menor a 120
        if(matriz[i][columnas-1]==t+1)   //Comparación  de la matriz  filas [i] y columnas [columnas -1] 
        prob[1][t]++;                     //La matriz se incrementa de uno en uno       
      }
  }

  for(i=0;i<filas;i++){               //Recorre un numero de columnas menor a 120                      
    for(j=0;j<columnas;j++){        //Recorre un numero de columnas menor a 5   
        sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2); // se calcula la distancia 
      }
     distancia=sqrt(sumatoria);         // Se obtiene la distancia
     sumatoria=0;                       //Se encera la sumatoria   
     if(distancia>dist_mayor)             //comparacion de distancias
        dist_mayor=distancia;              
        //Serial.println(dist_mayor); 
    }
    distancia=0;

     for(i=0;i<filas;i++){               //Recorre un numero de columnas menor a 120    
       for(j=0;j<columnas;j++){          //Recorre un numero de columnas menor a 5 
          sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2);  //se calcula la distancia
       }
       distancia=sqrt(sumatoria);         //Se obtiene la distancia
       normalizador=distancia/dist_mayor;    //Normaliza la distancia
       sumatoria=0;                      //se encera la sumatoria
       if(normalizador<r){
         list.Add(i);
        }
     }
     // for(i=0;i<list.Count();i++){
         // Serial.println(list[i]);
    // }
            //Agregacion de etiquetas a los casos probables 
for(i=0;i<list.Count();i++){
  for(j=0;j<etiquetas;j++){
if(matriz [list[i]][columnas-1]==prob[0][j]){
  prob[2][j]++;
  
  }
    
  
    }
  
  }
// 
p_x=list.Count()/float(filas);
for(k=0;k<etiquetas;k++){
  
  prob[3][k]=(prob[1][k]/filas)*(prob[2][k]/prob[1][k])/(p_x);
  
  }
 for(k=0;k<etiquetas;k++){
    
   // Serial.println(prob[3][k]);

if(prob[3][k]>aux){
  resultado= int (prob[0][k]);
  aux=prob[3][k];
  
  }
    
    }
Serial.println(resultado); // se imprime el resultado
}
