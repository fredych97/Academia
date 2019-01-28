/*
   float32_t
   uint32_t
*/
#define ARM_MATH_CM3
#include <arm_math.h>
#define tam_inputSignal 500
#define tam_impulse 29

extern float32_t Señal_1[tam_inputSignal];
extern float32_t Impulse_response[tam_impulse];
float32_t signal_out[tam_inputSignal + tam_impulse];
float32_t promedio;
float32_t desvE;
float32_t var;
float32_t desv;

void setup() {
  Serial.begin(9600);
  //promedio
  arm_mean_f32(&Señal_1[0], tam_inputSignal, &promedio);
  Serial.println(promedio);
  //varianza
  arm_var_f32(&Señal_1[0], tam_inputSignal, &var);
  Serial.println(var);
  //desviacion estandar
  //sacar raiz de la varianza
  desv=sqrt(var);
  Serial.println(desv);

}

void loop() {
  //  convolucion(InputSignal_1kHz_15kHz,
  //              Impulse_response,
  //              tam_inputSignal,
  //              tam_impulse
  //              );
  arm_conv_f32(&Señal_1[0], tam_inputSignal, &Impulse_response[0], tam_impulse, &signal_out[0]);
  plot_sig(signal_out, tam_inputSignal + tam_impulse);
}

void plot_sig(float32_t *sig_entrada, uint32_t tam_sig) {
  uint32_t i;
  for (i = 0; i < tam_sig; i++) {
    Serial.println(sig_entrada[i] * 100);
    delay(10);
  }
}

void convolucion(float32_t *sig_entrada,
                 float32_t *sig_impulso,
                 uint32_t tam_sig_entrada,
                 uint32_t tam_impulso) {
  uint32_t i, j; //i recorre sig entrada y j recorre sig impulso

  for (i = 0; i < tam_sig_entrada; i++) {
    for (j = 0; j < tam_impulso; j++) {
      signal_out[i + j] = signal_out[i + j] + sig_entrada[i] * sig_impulso[j];
    }
  }


}
