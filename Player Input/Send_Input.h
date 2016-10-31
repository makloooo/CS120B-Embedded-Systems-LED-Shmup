/*
 * Send_Input.h
 *
 * Created: 5/28/2016 2:09:43 AM
 *  Author: Mark
 */ 


#ifndef SEND_INPUT_H_
#define SEND_INPUT_H_

enum Send_States {Send_Start, Send_Wait, Send_Signal};
int Send_Input (int state) {
	switch (state) {
		case Send_Start:
			state = Send_Wait;
		break;
		
		case Send_Wait:
			if (p1_input) state = Send_Signal;
		break;
		
		case Send_Signal:
			state = Send_Wait;
		break;
		
		default:
		break;
	}
	
	switch (state) {
		case Send_Start:
		case Send_Wait:
		break;
		
		case Send_Signal:
			PORTB = 0xFF;
			if (USART_IsSendReady(0)) USART_Send(p1_input, 0);
			//if (USART_IsSendReady(1)) USART_Send(p2_input, 1);
		break;
		
		default:
		break;
	}
	
	return state;
}

#endif /* SEND_INPUT_H_ */