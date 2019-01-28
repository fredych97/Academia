#define ARM_MATH_CM3    //LIBRERIA MATH DEL DUE
#include <arm_math.h>
#define tam_sig 500
extern float32_t Señal_1[tam_sig];
float32_t OutputSignal [tam_sig];

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  //running_sum(&InputSignal_1kHz_15kHz[0], &OutputSignal[0], tam_sig);
  running_dif(&Señal_1[0], &OutputSignal[0], tam_sig);
  plot_sig();
}

void plot_sig() {
  uint32_t i;
  for (i = 0; i < tam_sig; i++) {
    Serial.println(Señal_1[i] + 5);
    Serial.print(",");
    Serial.println(OutputSignal[i]);
    delay(10);
  }
}

void running_sum(float32_t *input, float32_t *output, uint32_t tam) {
  uint32_t i;
  for (i = 0; i < tam; i++) {
    output[i] = input[i] + output[i - 1];
  }
}

  void running_dif(float32_t *input, float32_t *output, uint32_t tam) {
  uint32_t i;
  for (i = 0; i < tam; i++) {
    output[i] = input[i] - input[i - 1];
  }
}
