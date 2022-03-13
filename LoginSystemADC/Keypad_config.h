/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: Keypad                 **********/
/**********      Date: 1-9-2020              **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


#define KEYPAD_BUTTONS_VALUES  {{1,2,3,4},{5,6,7,8},{9,0,0,0},{0,0,0,0}}

#define KEYPAD_PORT 		   DIO_u8PORTC

#define COLUMN_PIN0            DIO_u8PIN4
#define COLUMN_PIN1            DIO_u8PIN5
#define COLUMN_PIN2            DIO_u8PIN6
#define COLUMN_PIN3            DIO_u8PIN7

#define ROW_PIN0               DIO_u8PIN0
#define ROW_PIN1               DIO_u8PIN1
#define ROW_PIN2               DIO_u8PIN2
#define ROW_PIN3               DIO_u8PIN3

#define NO_PRESSED_KEY         0


#endif
