#define ARM_MATH_CM3    //LIBRERIA MATH DEL DUE
#include <arm_math.h>
#define tam_sig 500
extern float32_t  Senal[tam_sig];
float32_t REX[tam_sig / 2];
float32_t IDX[tam_sig / 2];
float32_t OutputSignal[tam_sig/2];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  cal_tdf(&float32_t Senal[0],&REX[0],&IDX[0],tam_sig);
  get_tdf();
  plot_signal();
}

void cal_tdf(float32_t *input_sig, float32_t *sig_rex, float32_t *sig_idx, uint32_t tam) {

  uint32_t i,j,k;
  for(j=0;j<tam/2;j++){
    sig_rex[j]=0;
    sig_idx[j]=0;
  }

  for(k=0;k<tam/2;k++){
    for(i=0;i<tam;i++){
      sig_rex[k]=sig_rex[k]+input_sig[i]*cos(2*PI*k*i/tam);
      sig_idx[k]=sig_idx[k]-input_sig[i]*sin(2*PI*k*i/tam);
    }
  }
}

void get_tdf(void){
  uint32_t i;
  for(i=0;i<tam_sig/2;i++){
    OutputSignal[i]=sqrt(pow(REX[i],2)+pow(IDX[i],2));
  }
}

void plot_signal(){
  uint32_t i;
  for(i=0;i<tam_sig/2;i++){
    Serial.println(OutputSignal[i]);
    delay(10);
  }
}
