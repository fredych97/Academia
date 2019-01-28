/*TRANFORMADA SE FOURIER DE PRIMERA SEÑAL
 * 
 */
#define ARM_MATH_CM3    //LIBRERIA MATH DEL DUE
#include <arm_math.h>
#define tam_sig 640
extern float32_t points_ecg[tam_sig];//llamamos a la señal en la otra pestaña
float32_t REX[tam_sig / 2];// variables con el tamaño de muestras por la mitad
float32_t IDX[tam_sig / 2];
float32_t OutputSignal[tam_sig/2];// variable para la señal de salida 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  cal_tdf(&points_ecg[0],&REX[0],&IDX[0],tam_sig);// llamamos al metodo calcular la tranformada 
  get_tdf();
  plot_signal();
}

void cal_tdf(float32_t *input_sig, float32_t *sig_rex, float32_t *sig_idx, uint32_t tam) {// metodo de calcular la tranformada 

  uint32_t i,j,k;
  for(j=0;j<tam/2;j++){// siclo repetitivo para muestriar la señal 
    sig_rex[j]=0;
    sig_idx[j]=0;
  }
// ciclos repetitivos para aplicar las muestras una a una en coseno y seno
  for(k=0;k<tam/2;k++){
    for(i=0;i<tam;i++){
      sig_rex[k]=sig_rex[k]+input_sig[i]*cos(2*PI*k*i/tam);
      sig_idx[k]=sig_idx[k]-input_sig[i]*sin(2*PI*k*i/tam);
    }
  }
}

void get_tdf(void){// metodo para obtener la transformada
  uint32_t i;
  for(i=0;i<tam_sig/2;i++){
    OutputSignal[i]=sqrt(pow(REX[i],2)+pow(IDX[i],2));
  }
}

void plot_signal(){// metodo para graficar la señal
  uint32_t i;
  for(i=0;i<tam_sig/2;i++){
    Serial.println(OutputSignal[i]);
    delay(10);
  }
}
