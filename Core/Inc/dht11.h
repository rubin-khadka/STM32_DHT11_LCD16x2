/*
 * dht11.h
 *
 *  Created on: Feb 20, 2026
 *      Author: Rubin Khadka
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"

void DHT11_Start(void);
uint8_t DHT11_Check_Response(void);
uint8_t DHT11_Read(void);

#endif /* INC_DHT11_H_ */
