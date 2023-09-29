#include "conversores.h"
#include "MKL25Z4.h"

#include <stdint.h>

void initDac(){
    SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
    DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}
void initAdc(){
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;//habilitar clock del PIN
    ADC0->CFG1 = ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(1) | ADC_CFG1_ADIV(0);//configurar
    ADC0->SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);//iniciar calibracion
    while (ADC0->SC3 & ADC_SC3_CAL_MASK);// espera a q termine la calibracion
}
void DacConversion(int valor){
    DAC0->DAT[0].DATH = DAC_DATH_DATA0(valor >> 8);
    DAC0->DAT[0].DATL = DAC_DATL_DATA0(valor & 0xFF);
}
int AcdLectura(int channel){
    ADC0->SC1[0] = ADC_SC3_ADCH(channel);
    while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
    int valorMedido = ADC0->R[0];
    int valorVolt = ((3.6 * valorMedido)/65535);
    return valorVolt;
}
