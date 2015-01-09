#include "dual_shock_can.h"

void CAN_Controller_setup(void){
	Init_CAN();
}

//	Arduinoから受信したキーの状態を返す
//	左右のスティックの値は -1.0 ～ 1.0
//	その他のキーの値は 0 ～ 1.0
//	スティックは上がX正	下がX負	左がY正 右がY負としている

float CAN_Read_l_stick_x(void){
	return(((KEY_MAX_VALUE / 2.0) - psbutton.left_x.value) / (KEY_MAX_VALUE / 2.0));
}

float CAN_Read_l_stick_y(void){
	return(((KEY_MAX_VALUE / 2.0) - psbutton.left_y.value) / (KEY_MAX_VALUE / 2.0));
}

float CAN_Read_r_stick_x(void){
	return(((KEY_MAX_VALUE / 2.0) - psbutton.right_x.value) / (KEY_MAX_VALUE / 2.0));
}

float CAN_Read_r_stick_y(void){
	return(((KEY_MAX_VALUE / 2.0) - psbutton.right_y.value)) / (KEY_MAX_VALUE / 2.0));
}

float CAN_Read_key_up(void){
	return(psbutton.Up.value / KEY_MAX_VALUE);
}

float CAN_Read_key_right(void){
	return(psbutton.Right.value / KEY_MAX_VALUE);
}

float CAN_Read_key_down(void){
	return(psbutton.Down.valu / KEY_MAX_VALUE);
}

float CAN_Read_key_left(void){
	return(psbutton.Left.value / KEY_MAX_VALUE);
}

float CAN_Read_key_triangle(void){
	return(psbutton.Triangle.value / KEY_MAX_VALUE);
}

float CAN_Read_key_circle(void){
	return(psbutton.Circle.value / KEY_MAX_VALUE);
}

float CAN_Read_key_cross(void){
	return(psbutton.Cross.value / KEY_MAX_VALUE);
}

float CAN_Read_key_square(void){
	return(psbutton.Square.value / KEY_MAX_VALUE);
}

float CAN_Read_key_start(void){
	return(psbutton.start.value);
}

float CAN_Read_key_l1(void){
	return(psbutton.L1.value / KEY_MAX_VALUE);
}

float CAN_Read_key_r1(void){
	return(psbutton.R1.value / KEY_MAX_VALUE);
}

float CAN_Read_key_l2(void){
	return(psbutton.L2.value / KEY_MAX_VALUE);
}

float CAN_Read_key_r2(void){
	return(psbutton.R2.value / KEY_MAX_VALUE);
}

/******************************************************************************
*	タイトル ： コントローラ解析
*	  関数名 ： CAN_DualShock3
*	  戻り値 ： void型
*	    引数 ： CanRxMsg*
*	  作成者 ： 有本光
*	  作成日 ： 2015/1/9
******************************************************************************/
void CAN_DualShock3(CanRxMsg* RxMessage)
{

	uint8_t i;

	for(i=0; i < RxMessage->DLC; i++){

		switch(RxMessage->Data[i]){	//i=key i+1=value //i+2=#

//		case  key:		psbutton.key.value		= RxMessage->Data[i+1];
//			break;
		case start: 	psbutton.start.value 	= RxMessage->Data[i+1];
			break;
		case select:	psbutton.select.value 	= RxMessage->Data[i+1];
			break;
		case left_x:	psbutton.left_x.value 	= RxMessage->Data[1];
			break;
		case left_y:	psbutton.left_y.value 	= RxMessage->Data[1];
			break;
		case right_x:	psbutton.right_x.value 	= RxMessage->Data[i+1];
			break;
		case right_y:	psbutton.right_y.value 	= RxMessage->Data[i+1];
			break;
		case L1:    	psbutton.L1.value 		= RxMessage->Data[i+1];
			break;
		case L2:		psbutton.L2.value 		= RxMessage->Data[i+1];
			break;
		case R1:		psbutton.R1.value 		= RxMessage->Data[i+1];
			break;
		case R2:		psbutton.R2.value 		= RxMessage->Data[i+1];
			break;
		case Triangle:	psbutton.Triangle.value = RxMessage->Data[i+1];
			break;
		case Circle:	psbutton.Circle.value 	= RxMessage->Data[i+1];
			break;
		case Cross:		psbutton.Cross.value 	= RxMessage->Data[i+1];
			break;
		case Square:	psbutton.Square.value 	= RxMessage->Data[i+1];
			break;
		case Up:		psbutton.Up.value 		= RxMessage->Data[i+1];
			break;
		case Right:		psbutton.Right.value 	= RxMessage->Data[i+1];
			break;
		case Down:		psbutton.Down.value 	= RxMessage->Data[i+1];
			break;
		case Left:		psbutton.Left.value 	= RxMessage->Data[i+1];
			break;
		default:
			break;
		}
		i += 2;
	}

}
