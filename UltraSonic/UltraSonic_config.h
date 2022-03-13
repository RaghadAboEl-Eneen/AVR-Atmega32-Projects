/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: UltraSonic             **********/
/**********      Date: 30-08-2021            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#ifndef ULTRASONIC_CONFIG_H_
#define ULTRASONIC_CONFOG_H

//choose pin that will output the trigger signal to the ultrasonic
#define ULTRASONIC_TRIGGER_PORT DIO_u8PORTB
#define ULTRASONIC_TRIGGER_PIN  DIO_u8PIN0


#define ULTRASONIC_ECHO_PORT	DIO_u8PORTD
#define ULTRASONIC_ECHO_PIN		DIO_u8PIN7


#endif
