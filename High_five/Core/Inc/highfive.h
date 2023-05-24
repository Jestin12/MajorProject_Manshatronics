/*
 * highfive.h
 *
 *  Created on: May 24, 2023
 *      Author: neelbagayatkar
 */

#ifndef INC_HIGHFIVE_H_
#define INC_HIGHFIVE_H_

void highfive();

extern uint8_t string_to_send[100];
extern TIM_HandleTypeDef htim3;
extern uint8_t *led_register;

#endif /* INC_HIGHFIVE_H_ */
