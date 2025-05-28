/**
 *******************************************************************************
 * @file	stm32g4_adc.h
 * @author	vchav
 * @date	May 23, 2024
 * @brief	
 *******************************************************************************
 */
#ifndef BSP_STM32G4_ADC_H_
#define BSP_STM32G4_ADC_H_

#include "main.h"

typedef void (*callback_fun_t)(void);

/**
 * @brief Enumération des convertisseurs analogique numérique sélectionnable
 */
typedef enum{
	ADC_1 = 0,		//Entrée PA0
	ADC_2,			//Entrée PA1
	ADC_3,			//Entrée PA6
	ADC_4,			//Entrée PA7
	ADC_10,			//Entrée PF1
	ADC_13,			//Entrée PA5
	ADC_17,			//Entrée PA4
	ADC_CHANNEL_NB
}adc_id_e;


uint32_t BSP_ADC_getValue(adc_id_e channel);
void DEMO_adc_process_1ms(void);

#endif /* BSP_STM32G4_ADC_H_ */
