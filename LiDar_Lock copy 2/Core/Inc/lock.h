/*
 * lock.h
 *
 *  Created on: 23 May 2023
 *      Author: neelbagayatkar
 */

#ifndef INC_LOCK_H_
#define INC_LOCK_H_

void lock1(int *y);
void lock2(int *y);
void lock3(int *y);

extern uint8_t string_to_send[100];
extern int x;
extern uint8_t *led_register;

#endif /* INC_LOCK_H_ */
