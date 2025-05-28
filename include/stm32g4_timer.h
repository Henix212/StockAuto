/**
 *******************************************************************************
 * @file	stm32g4_timer.h
 * @author	jjo
 * @date	Apr 26, 2024
 * @brief	
 *******************************************************************************
 */

#include "main.h"

#ifndef BSP_STM32G4_TIMER_H_
#define BSP_STM32G4_TIMER_H_

#if USE_BSP_TIMER | 1
/* Defines -------------------------------------------------------------------*/

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Public types --------------------------------------------------------------*/
typedef enum
{
	TIMER1_ID = 0,
	TIMER2_ID,
	TIMER3_ID,
	TIMER4_ID,
	TIMER6_ID,
	TIMER_ID_NB
}timer_id_t;

/* Public constants ----------------------------------------------------------*/


/* Public functions declarations ---------------------------------------------*/

void BSP_TIMER_run_us(timer_id_t id, uint32_t us, uint8_t enable_irq);

void BSP_TIMER_stop(timer_id_t id);

TIM_HandleTypeDef * BSP_TIMER_get_handler(timer_id_t timer_id);

uint32_t BSP_TIMER_read(timer_id_t timer_id);

void BSP_TIMER_write(timer_id_t timer_id, uint32_t counter);

uint32_t BSP_TIMER_get_period(timer_id_t timer_id);

void BSP_TIMER_set_period(timer_id_t timer_id, uint32_t period);

uint16_t BSP_TIMER_get_prescaler(timer_id_t timer_id);

void BSP_TIMER_set_prescaler(timer_id_t timer_id, uint16_t prescaler);

void BSP_TIMER_enable_output_trigger(timer_id_t timer_id);

void BSP_TIMER_enable_PWM(timer_id_t timer_id, uint16_t TIM_CHANNEL_x, uint16_t duty, uint8_t remap, uint8_t negative_channel);

void BSP_TIMER_set_duty(timer_id_t timer_id, uint16_t TIM_CHANNEL_x, uint16_t duty);

void BSP_TIMER_set_period_with_same_duty(timer_id_t timer_id, uint16_t TIM_CHANNEL_x, uint32_t period);

#endif /* USE_BSP_TIMER */
#endif /* BSP_STM32G4_TIMER_H_ */
