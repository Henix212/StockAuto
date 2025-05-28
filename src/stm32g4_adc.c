/**
 *******************************************************************************
 * @file	stm32g4_adc.c
 * @author	vchav
 * @date	May 23, 2024
 * @brief	
 *******************************************************************************
 */

#include "stm32g4_adc.h"
#include "stm32g4_timer.h"
#include <stdio.h>

#define ADC_NB_OF_CHANNEL_USED	(0 + 0 + 0 + 0 + 1 + 0 + 0)


static uint32_t adc_converted_value[ADC_NB_OF_CHANNEL_USED];//Ce tableau contient les valeurs mesurées par l'ADC pour chaque canal.
static int8_t adc_id[ADC_CHANNEL_NB];						//Ce tableau contient les rang de chaque canal dans le tableau adc_converted_value. Usage privé à ce fichier.
static ADC_HandleTypeDef	hadc;							//Handler pour l'ADC.
static DMA_HandleTypeDef	hdma;							//Handler pour le DMA.
static volatile uint16_t t = 0;								//Chrono utilisé dans la machine a état. décrémenté toutes les millisecondes.

void DEMO_adc_process_1ms(void)
{
	if(t)
		t--;
}

/**ADC2 GPIO Configuration
PF1-OSC_OUT  ------> ADC2_IN10
PA0  --------------> ADC2_IN1
PA1  --------------> ADC2_IN2
PA4  --------------> ADC2_IN17
PA5  --------------> ADC2_IN13
PA6  --------------> ADC2_IN3
PA7  --------------> ADC2_IN4
*/

void ADC1_2_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc);
}
/**
* @brief  	Cette fonction permet de récupérer les valeurs mesurées par l'ADC.
* @func  	int16_t ADC_getValue(adc_id_e channel)
* @param	channel : un canal de ADC_0 à ADC_15
* @retval 	un entier signé sur 16 bits, correspondant à la valeur demandée, pouvant aller de 0 à 4095 (l'ADC mesure sur 12 bits).
* @retval	Cette fonction retourne -1 si l'on demande un canal ADC qui n'a pas été initialisé (le define USE_ADCx correspondant est commenté)
*/
uint32_t BSP_ADC_getValue(adc_id_e channel)
{
	if(adc_id[channel] == -1 || channel >= ADC_CHANNEL_NB)
	{
		printf("You asked for the reading of the channel %d which is non initialized or unused! Please review your software\n", channel);
		return -1;
	}
	return adc_converted_value[adc_id[channel]];
}

static callback_fun_t callback_function;
/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
static volatile uint8_t flag_new_sample_available = 0;

uint8_t ADC_is_new_sample_available(void)
{
	uint8_t ret = flag_new_sample_available;
	if(ret)
		flag_new_sample_available = 0;
	return ret;
}



void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	UNUSED(hadc);
	flag_new_sample_available = 1;
	if(callback_function)
		callback_function();
}


/**
  * @brief  Conversion DMA half-transfer callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
	UNUSED(hadc);
}


void ADC_set_callback_function(callback_fun_t callback)
{
	callback_function = callback;
}


void DMA1_Channel1_IRQHandler(void) {

	HAL_DMA_IRQHandler(&hdma);

	//See errata sheet
 //   hdma.DmaBaseAddress->IFCR = ((uint32_t)DMA_IFCR_CHTIF1 << (hdma.ChannelIndex & 0x1FU));
//    hdma.DmaBaseAddress->IFCR = ((uint32_t)DMA_IFCR_CTCIF1 << (hdma.ChannelIndex & 0x1FU));
   // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
}
