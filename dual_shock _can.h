#ifndef DUAL_SHOCK_H
#define DUAL_SHOCK_H
/*
#include	"stm32f4xx_usart.h"

#include	"config_usart.h"
#include	"config_systick.h"	//millis()が入ってるヘッダファイル

#include	"setting.h"
*/

#define KEY_MAX_VALUE	255.0

//Dualshock3のデータ解析用
//この列挙型の値はArduino側の設定と合わせる
enum {
	start = 'a',
	select,
	left_x,
	left_y,
	right_x,
	right_y,
	L1,L2,
	R1,R2,
	Triangle,
	Circle,
	Cross,
	Square,
	Up,
	Right,
	Down,
	Left,
	CError
}Mnemonic;
typedef struct _Button{
	uint8_t	value;
}Button;

typedef struct _DualshockBotton{
	Button	start,
			select,
			left_x,
			left_y,
			right_x,
			right_y,
			L1,
			L2,
			R1,
			R2,
			Triangle,
			Circle,
			Cross,
			Square,
			Up,
			Right,
			Down,
			Left,
			CError;
}DualshockBotton;

void CAN_Controller_setup(void);			//コントローラー初期設定

float CAN_Read_l_stick_x(void);
float CAN_Read_l_stick_y(void);
float CAN_Read_r_stick_x(void);
float CAN_Read_r_stick_y(void);
float CAN_Read_key_up(void);
float CAN_Read_key_right(void);
float CAN_Read_key_down(void);
float CAN_Read_key_left(void);
float CAN_Read_key_triangle(void);
float CAN_Read_key_circle(void);
float CAN_Read_key_cross(void);
float CAN_Read_key_square(void);
float CAN_Read_key_start(void);
float CAN_Read_key_l1(void);
float CAN_Read_key_r1(void);
float CAN_Read_key_l2(void);
float CAN_Read_key_r2(void);

void CAN_DualShock3(CanRxMsg* RxMessage);//受信記号解析

#endif
