#include <util/delay.h>

#include "STD_TYPES.h"
#include "Bit_MATH.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"
#include "TactileButton_interface.h"

void INT0_ISR(void);
void INT1_ISR(void);

u8 i = 0;

u8 Net[8] = { 0b01110, 0b01110, 0b01110, 0b01110, 0b01110, 0b01110, 0b01110,
		0b01110 };

u8 Net2[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b01110,
		0b01110 };

u8 Racket1_Swung[8] = { 0b00000, 0b00000, 0b00001, 0b00011, 0b00111, 0b00110,
		0b01000, 0b10000 };

u8 Racket2_Swung[8] = { 0b00000, 0b00000, 0b10000, 0b11000, 0b11100, 0b01100,
		0b00010, 0b00001 };

u8 Ball[8] = { 0b00000, 0b00000, 0b01110, 0b01110, 0b01110, 0b00000, 0b00000,
		0b00000 };
u8 Ball2[8] = { 0b00000, 0b00000, 0b01110, 0b01110, 0b01110, 0b00000, 0b01110,
		0b01110 };
u8 Racket1_Idle[8] = { 0b01110, 0b11111, 0b11111, 0b11111, 0b11111, 0b01110,
		0b00100, 0b00100 };
u8 Racket1_Moved[8] = { 0b00000, 0b00000, 0b10000, 0b10000, 0b10000, 0b10000,
		0b10000, 0b10000 };

u8 Racket2_Moved[8] = { 0b00000, 0b00000, 0b00001, 0b00001, 0b00001, 0b00001,
		0b00001, 0b00001 };

s8 X_Position, Y_Position = 0;
u8 Going_Left_Or_Right; // 1 for left , 0 for right;
u8 Local_u8Game_End_Flag = 1;

#define RACKET_1_IDLE     Racket1_Moved
#define RACKET_2_IDLE	  Racket2_Moved
#define RACKET_1_MOVED	  Racket1_Swung
#define RACKET_2_MOVED	  Racket2_Swung

void main(void) {

	PORT_voidInit();
	EXTI_voidINT0Init();
	EXTI_voidINT1Init();
	EXTI_u8INTSetCallBack(&INT0_ISR, EXTI_INT0);
	EXTI_u8INTSetCallBack(&INT1_ISR, EXTI_INT1);
	GIE_voidEnableGlobal();

	CLCD_voidInit();
	CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
	CLCD_voidWriteSpecialCharacter(RACKET_1_IDLE, 0, 0, Y_Position);
	CLCD_voidWriteSpecialCharacter(RACKET_2_IDLE, 7, 15, Y_Position);
	CLCD_voidWriteSpecialCharacter(Net, 5, 7, 1);
	CLCD_voidWriteSpecialCharacter(Net2, 6, 7, 0);
	Going_Left_Or_Right = 0; // 1 for left , 0 for right;
	X_Position = 0;
	while (1) {

		switch (Going_Left_Or_Right) {
		case 0:
			while (Going_Left_Or_Right == 0 && Local_u8Game_End_Flag == 1) {
				if (X_Position == 16) {
					CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
					CLCD_voidGotoXY(2, 0);
					CLCD_voidWriteString("Player 1 Wins!");
					CLCD_voidGotoXY(2, 1);
					CLCD_voidWriteString("Play again?");
					Local_u8Game_End_Flag = 0;
					while (Local_u8Game_End_Flag == 0)
						;
					CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
					//Local_u8Game_End_Flag = 1;
					X_Position = 0;
					Going_Left_Or_Right = 0;
					CLCD_voidWriteSpecialCharacter(RACKET_1_IDLE, 0, 15,
							Y_Position);
					CLCD_voidWriteSpecialCharacter(Net, 5, 7, 1);
					CLCD_voidWriteSpecialCharacter(Net2, 6, 7, 0);

				}
				if (X_Position == 7) {
					CLCD_voidWriteSpecialCharacter(Ball2, 3, X_Position,
							Y_Position);
				} else if (X_Position == 15) {
					CLCD_voidWriteSpecialCharacter(RACKET_2_IDLE, 7, 15,
							Y_Position);

				} else {
					CLCD_voidWriteSpecialCharacter(Ball, 2, X_Position,
							Y_Position);
					CLCD_voidWriteSpecialCharacter(Net2, 6, 7, 0);
				}
				_delay_ms(100);
				CLCD_voidGotoXY(X_Position - 1, Y_Position);
				CLCD_voidSendData(' ');
				CLCD_voidGotoXY(X_Position, Y_Position);
				CLCD_voidWriteSpecialCharacter(RACKET_1_IDLE, 0, 0, Y_Position);
				X_Position++;
			}

			break;
		case 1:
			while (Going_Left_Or_Right == 1 && Local_u8Game_End_Flag == 1) {
				if (X_Position == -1) {
					CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
					CLCD_voidGotoXY(2, 0);
					CLCD_voidWriteString("Player 2 Wins!");
					Local_u8Game_End_Flag = 0;
					CLCD_voidGotoXY(2, 1);
					CLCD_voidWriteString("Play again?");
					while (Local_u8Game_End_Flag == 0)
						;
					CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
					//Local_u8Game_End_Flag = 1;
					X_Position = 15;
					Going_Left_Or_Right = 1;
					CLCD_voidWriteSpecialCharacter(Net, 5, 7, 1);
					CLCD_voidWriteSpecialCharacter(Net2, 6, 7, 0);
					CLCD_voidWriteSpecialCharacter(RACKET_2_IDLE, 7, 15,
							Y_Position);
				}
				if (X_Position == 7) {
					CLCD_voidWriteSpecialCharacter(Ball2, 3, X_Position,
							Y_Position);
				} else if (X_Position == 0) {
					CLCD_voidWriteSpecialCharacter(RACKET_1_IDLE, 0, 0,
							Y_Position);

				} else {

					CLCD_voidWriteSpecialCharacter(Ball, 2, X_Position,
							Y_Position);
					CLCD_voidWriteSpecialCharacter(Net2, 6, 7, 0);
				}
				_delay_ms(100);
				CLCD_voidGotoXY(X_Position + 1, Y_Position);
				CLCD_voidSendData(' ');
				CLCD_voidGotoXY(X_Position, Y_Position);
				CLCD_voidWriteSpecialCharacter(RACKET_2_IDLE, 7, 15,
						Y_Position);
				X_Position--;
			}
			break;
		}

	}

}

void INT0_ISR(void) {
	if (Local_u8Game_End_Flag == 0) {
		Local_u8Game_End_Flag = 1;
	} else {
		CLCD_voidWriteSpecialCharacter(RACKET_1_MOVED, 1, 0, Y_Position);
		if (X_Position == 0 || X_Position == 1) {
			Going_Left_Or_Right = 0;
		}
		EXTI_u8INTClearFlag(EXTI_INT0);
	}
}

void INT1_ISR(void) {
	if (Local_u8Game_End_Flag == 0) {
		Local_u8Game_End_Flag = 1;
	} else {
		CLCD_voidWriteSpecialCharacter(RACKET_2_MOVED, 1, 15, Y_Position);
		if (X_Position == 14 || X_Position == 15) {
			Going_Left_Or_Right = 1;
		}
		EXTI_u8INTClearFlag(EXTI_INT1);
	}
}
