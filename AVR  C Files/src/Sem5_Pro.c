/*
 * Sem5_Pro.c
 *
 * Created: 5/28/2016 9:41:42 AM
 *  Author: ijaz
 */ 


#define F_CPU 8000000
#define BAUD 9600	
#define BAUDRATE ((F_CPU/16/BAUD)-1)


#define RS eS_PORTD2
#define EN eS_PORTD3
#define D4 eS_PORTD5
#define D5 eS_PORTD6
#define D6 eS_PORTD7
#define D7 eS_PORTB0

#include <avr/io.h>
#include <util/delay.h>

#include <lib/basics.h>
#include <lib/lcd_328p.h>
#include <lib/uart.h>
#include <lib/HX711.h>


int main(void){
	DDRB = 0b00000001;
	DDRD = 0b11111111;
	DDRC = 0b00010000;
	
	Disable_Prescaler();
	USART_Init(BAUDRATE);
	
	char *cmd1 = "AT+CWMODE=1\r\n";
	char *cmd2 = "AT+CWJAP=\"ijazmobile\",\"\"\r\n";
	char *cmd3 = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80";
	char *cmd4 = "AT+CIPSEND=GET /update?api_key=PDDCEA6A2FW7DDWL&field1=13.5\r\n";
	char *cmd5 ="AT+CIPCLOSE";
	
	USART_Transmit_String(cmd1);
	Lcd4_Init();
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,4);
	Lcd4_Write_String("Gas Level");
	Lcd4_Set_Cursor(2,4);
	Lcd4_Write_String("Detector");
	_delay_ms(5000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Connecting Wifi");
	USART_Transmit_String(cmd2);
	_delay_ms(5000);
	
	
	while(1){
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Reading.....");
		//Read_HX711();
		_delay_ms(5000);
		
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Current Level");
		Lcd4_Set_Cursor(2,4);
		Lcd4_Write_String("0%");
		_delay_ms(5000);
	
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Uploading Data");
		for(int i=0;i<5;i++){
			USART_Transmit_String(cmd3);
			USART_Transmit_String(cmd4);
			//USART_Transmit_String(cmd5);
		}
		_delay_ms(5000);
	}
	
	
}
