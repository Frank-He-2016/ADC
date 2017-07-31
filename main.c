#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "adc.h"
int main(void)
{
adc_init();
while(1)
{
unsigned r;
r=(unsigned short)(adc_read());
unsigned char a0,a,b,c,d; 
a0=r/10000;
a=(r-a0*10000)/1000;
b=(r-a0*10000-1000*a)/100;
c=(r-a0*10000-1000*a-100*b)/10;
d=r-a0*10000-1000*a-100*b-10*c;
USART_SendData(USART1,a0+0x30);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
USART_SendData(USART1,a+0x30);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
USART_SendData(USART1,0x2E);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
USART_SendData(USART1,b+0x30);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
USART_SendData(USART1,c+0x30);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
USART_SendData(USART1,d+0x30);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
USART_SendData(USART1,0x0D);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
USART_SendData(USART1,0X0A);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}
}
