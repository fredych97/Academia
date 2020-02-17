/*
 *                                                     UNIVERSIDAD TECNICA DEL NORTE 
 *                                                              FICA-CIERCOM
 *                                                           SISTEMAS EMBEBIDOS
 *Nombre: Fredy Chicaiza
 *Fecha:  17-2-2020
 *Tema:   PERCEPTRÓN
 */
#include "datosEntrenamiento.h"
float varuno= 0.20 ;  //Declaracion de variables 
float vardos= 0.30; 
float vartres= 0.40;
int ciclo=0;          
int posicion=0;
float factor_entre=0.9;
int cont_err;
#define filas 60
#define columnas 4
float sumatoria[filas];
float predecir[filas];
float err[filas];

 
void setup() {
Serial.begin(9600);

}

void loop() {
   while (ciclo < 10) {             //ciclo de veces 
          cont_err=0;               //encero el contador de errores
for(int i=0;i<filas;i++){         //recorro cada casillero de fila multiplico 
                                  //por los valores de los pesos
  
  sumatoria[i]=matriz[i][0]*(varuno) + matriz[i][1]*(vardos) + matriz[i][2]*(vartres);
}
for (int k=0;k<filas;k++){         //recorro cada fila 
     if(sumatoria[k] >= 0) {//asigno 1 o 0 ala prediccion
       predecir[k] = 1;
     } else {
        predecir[k] = 0;
      }
    }

for (int p=0;p<filas/2;p++) {       //predecir   
      err[p]=1-predecir[p];           //
      err[p+30]=0-predecir[p+30];     //
    }  

    
for (int l=0;l<filas;l++) {      //Va a encontrar el error
     if(err[l]==-1||err[l]==1) {// Busca si hay valores diferentes de 0.
       posicion=l;              // Va a cojer su posicion.
       break;
     }
    }
 varuno=varuno+factor_entre*(err[posicion])*1; //Recalcula los pesos
 vardos=vardos+factor_entre*(err[posicion])*(matriz[posicion][1]);
 vartres=vartres+factor_entre*(err[posicion])*(matriz[posicion][2]);
      ciclo++;

  for (int cant_err=0;cant_err<filas;cant_err++){ //cantidad de error
     if (err[cant_err]!= 0)
           cont_err++;

  }

    Serial.print("Peso variableUno: ");
    Serial.print(varuno);
    Serial.print(" Peso variableDos: ");
    Serial.print(vardos);
    Serial.print(" Peso variableTres: ");
    Serial.println(vartres);
    Serial.print("Numero de errores: ");
    Serial.println(cont_err);
   }

}


  
