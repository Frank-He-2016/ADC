#include "adc.h"


void adc_init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
  
  GPIO_InitTypeDef gpio_parameter;
  gpio_parameter.GPIO_Mode=GPIO_Mode_AIN;//模拟输入
  gpio_parameter.GPIO_Pin=GPIO_Pin_1;
  gpio_parameter.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&gpio_parameter);
  
  GPIO_InitTypeDef gpio_usart_parameter;
  gpio_usart_parameter.GPIO_Mode=GPIO_Mode_AF_PP;
  gpio_usart_parameter.GPIO_Pin=GPIO_Pin_9;
  gpio_usart_parameter.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&gpio_usart_parameter);
  
  USART_InitTypeDef USART_Parameter;
  USART_Parameter.USART_BaudRate=9600;
  USART_Parameter.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
  USART_Parameter.USART_Mode=USART_Mode_Tx;
  USART_Parameter.USART_Parity=USART_Parity_No;
  USART_Parameter.USART_StopBits=USART_StopBits_1;
  USART_Parameter.USART_WordLength=USART_WordLength_8b;
  USART_Init(USART1,&USART_Parameter);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //使能接收中断
  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_Cmd(USART1, ENABLE);
  
  ADC_DeInit(ADC1);
  ADC_InitTypeDef adc_para;
  adc_para.ADC_ContinuousConvMode=DISABLE;//单次模式
  adc_para.ADC_DataAlign=ADC_DataAlign_Right;//数据右对齐
  adc_para.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//软件触发
  adc_para.ADC_Mode=ADC_Mode_Independent;//独立工作模式
  adc_para.ADC_NbrOfChannel=1;//一个通道
  adc_para.ADC_ScanConvMode=DISABLE;//单通道模式
  ADC_Init(ADC1,&adc_para);
  
  ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);//PA1为ADC1的第1个通道
  ADC_Cmd(ADC1,ENABLE);//使能ADC1
  ADC_ResetCalibration(ADC1);//重置校准寄存器
  while(ADC_GetResetCalibrationStatus(ADC1));//直到重置完成
  ADC_StartCalibration(ADC1);//指定校准寄存器
  while(ADC_GetCalibrationStatus(ADC1));//直到指定完成
  ADC_SoftwareStartConvCmd(ADC1,ENABLE);//使能ADC1软件转化启动功能
  
}

float adc_read(void)
{
  int result=0;
  float s;
  unsigned short id;
  unsigned short i;
  for(i=0;i<1000;i++)
  {
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    do
    {
      id=ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC);
    }while(!id);
    result=result+ADC_GetConversionValue(ADC1);
  }
  result=result/1000;
  s=(float)(result);
  s=(float)(s*0.1623);
  return s;
}
