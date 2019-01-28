/*UNIVERSISDAD TECNICA DEL NORTE 
 * FICA-CIERCOM
 * 
 * NOMBRE:WILMER BENAVIDES
 *        MACAS CRISTOFER
 *        
 * 
 */
#define ARM_MATH_CM3
#include <arm_math.h>// librerias 
#define tam_inputSignal 640// señal del pulso de prueba
#define tam_impulse 29// señal pulso 

extern float32_t points_ecg[tam_inputSignal];// llamamos a la señal de la otra pestaña
extern float32_t Impulse_response[tam_impulse];// se llama a la señal portadora 
float32_t signal_out[tam_inputSignal + tam_impulse];// variable para la señal de salida 
float32_t promedio;// variables para los respectivos calculos
float32_t desvE;
float32_t var;


void setup() {
  Serial.begin(9600);
  //promedio
  arm_mean_f32(&points_ecg[0], tam_inputSignal, &promedio);
  Serial.println(promedio);
  //varianza
  arm_var_f32(&points_ecg[0], tam_inputSignal, &var);
  Serial.println(var);
  //desviacion estandar
  //sacar raiz de la varianza
  desE=sqrt(var);
  Serial.println(desE);

}

void loop() {
  //  convolucion(InputSignal_1kHz_15kHz,
  //              Impulse_response,
  //              tam_inputSignal,
  //              tam_impulse
  //              );
  arm_conv_f32(&points_ecg[0], tam_inputSignal, &Impulse_response[0], tam_impulse, &signal_out[0]);// se llama a la libreria y se asigna los valores que se va a realizar una convulucion
  plot_sig(signal_out, tam_inputSignal + tam_impulse);// se llama al metodo para asignar los parametros para mostrar la señal de la señal
}

void plot_sig(float32_t *sig_entrada, uint32_t tam_sig) {// metodo para graficar la señal 
  uint32_t i;
  for (i = 0; i < tam_sig; i++) {// se genera un ciclo repetitivo del tamaño de la señal
    Serial.println(sig_entrada[i] * 100);
    delay(10);
  }
}

void convolucion(float32_t *sig_entrada, float32_t *sig_impulso, uint32_t tam_sig_entrada, uint32_t tam_impulso) {// se realiza un metodo con la convolucion  
  uint32_t i, j; //i recorre sig entrada y j recorre sig impulso
// ciclos repetitivos para las dos señales y asi lograr multiplicar componente por componentes
  for (i = 0; i < tam_sig_entrada; i++) {
    for (j = 0; j < tam_impulso; j++) {
      signal_out[i + j] = signal_out[i + j] + sig_entrada[i] * sig_impulso[j];
    }
  }


}
