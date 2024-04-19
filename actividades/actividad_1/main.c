// Inclusion de bibliotecas
#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
/*
 * @brief Programa principal
 */ 
int main() {
    // Variable para almacenar el resultado del ADC
    uint16_t NTC = 0;
    // Variable para guardar el valor de temperatura
    float temperatura = 0.0;
    // Constante de proporcionalidad del termistor
    const uint16_t beta = 4000;
    // Habilito USB
    stdio_init_all();
    // Inicializo ADC
    adc_init();
    // Inicializo GPIO26 como entrada analogica
    adc_gpio_init(26);
    // Selecciono canal analogico
    adc_select_input(0);
    while(true) {

        temperatura = 0;
        for (int i=0; i<10; i++){
             // Leer NTC
            NTC = adc_read();
            // Calculo temperatura
            float vx = (NTC * 3.3)/4095;
            float rt =  3300/((3.3/vx)-1);
            temperatura = ((beta*298.15)/( (298*log(rt/2200))+beta))-273;
        }
        
        temperatura = temperatura/10;
        printf("La temperatura es %.2f\n", temperatura);
        // Espero 500 ms
        sleep_ms(500);
    }
    return 0;
}