#ifndef mylib
#include <my_libs/basics.h>
#endif


#ifndef SDA
#define SDA eS_PORTC4
#define SCL eS_PORTC5
#define GAIN 128
#endif



unsigned long Read_HX711(void){
	unsigned long Count;
	unsigned char i;
	pinWrite(SDA,1);
	pinWrite(SCL,0);
	for (unsigned int i = 0; i < GAIN; i++) {
		pinWrite(SCL,1);
		pinWrite(SCL,0);
	}
	Count=0;
	while(SDA);
	for (i=0;i<24;i++){
		pinWrite(SCL,1);
		Count=Count<<1;
		pinWrite(SCL,0);
		if(SDA) Count++;
	}
	pinWrite(SCL,1);
	Count=Count^0x800000;
	pinWrite(SCL,0);
	return(Count);
}