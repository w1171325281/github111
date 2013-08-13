/******************** (C) COPYRIGHT 2012 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Tools development Team
* Date First Issued  : January 2012
* Description        : This code is used for MB1034 board test
********************************************************************************
* History:
**
*
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_conf.h"


/* Private typedef -----------------------------------------------------------*/

#define TEST_LSE_no


// LEDs definition: LD3~LD4
#define  GPIO_LED_LD3   GPIO_Pin_9
#define  GPIO_LED_LD4   GPIO_Pin_8

uint32_t TickValue=0;
void Init_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  // Enable GPIOA, GPIOC clocks
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
  GPIO_Init(GPIOC, &GPIO_InitStructure);
   

  // Init User/Wakeup button B1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void TimingDelay_Decrement(void)
{
    TickValue--;  
}


//------------------------------------------------------------------------------
// Function Name : delay
// Description   : delay for some time in counts(rough)
// Input         : counts is how many counts of time to delay
//------------------------------------------------------------------------------
void delay(uint32_t counts)
{
  while(counts-- != 0)
    ;
}
 void EXTI_Configuration(void)
 {
  EXTI_DeInit();
  EXTI_InitTypeDef   EXTI_InitStructure;
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt ;//Interrupt is level  Event is trigger signal
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  //EXTI_GenerateSWInterrupt(EXTI_Line0); 
 }
void NVIC_Configuration(void)
{
  NVIC_SetPriority (EXTI0_1_IRQn , (1<<__NVIC_PRIO_BITS) - 1);//Set the interrupt priority level

  NVIC_InitTypeDef NVIC_InitStructure;  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;/*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be a value of @ref IRQn_Type 
                                            (For the complete STM32 Devices IRQ Channels list, 
                                            please refer to stm32f0xx.h file) */
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void RCC_Configuration(void)
{
   RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);
  // Enable PLL
  RCC_PLLCmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {
  }
// Select PLL as system clock source
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while(RCC_GetSYSCLKSource() != 0x08)
{
}
  // Enable PWR clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  // Enable access to the backup register, so LSE can be enabled
  PWR_BackupAccessCmd(ENABLE);
  // RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOC, ENABLE);
       /* SYSCFG Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Led_Green(void)
{
  GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET );
   delay(2000000);
   GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    delay(2000000);
     GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET );
   delay(2000000);
   GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    delay(2000000);
    GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET );
   delay(2000000);
   GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    delay(2000000);
    
}
void Led_Blue()
{
  GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET );
   delay(2000000);
   GPIO_ResetBits(GPIOC, GPIO_Pin_8);
    delay(2000000);
     GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET );
   delay(2000000);
   GPIO_ResetBits(GPIOC, GPIO_Pin_8);
    delay(2000000);
    GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET );
   delay(2000000);
   GPIO_ResetBits(GPIOC, GPIO_Pin_8);
    delay(2000000);}

void Led_Green_Blue()
{
  GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET );
  GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET );
   delay(200000);
   GPIO_ResetBits(GPIOC, GPIO_Pin_8);
   GPIO_ResetBits(GPIOC, GPIO_Pin_9);
}
int main(void)
{
  uint8_t i=0;
  #ifdef DEBUG
    debug();
  #endif 
 
  Init_GPIO();    
  RCC_Configuration();
  EXTI_Configuration(); 
  NVIC_Configuration();
  Led_Green();
   while(1)
   {
     if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
     {
       delay(200000);
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)&i==0)
        {
          delay(1000000);
         i++;
        GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET );
        PWR_EnterSleepMode(PWR_SLEEPEntry_WFI);
        GPIO_ResetBits(GPIOC, GPIO_Pin_9);
        }
        else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)&i==1)
        {
          delay(1000000);
          i++;
        GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET );
        delay(1000000);
        PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
        RCC_Configuration();//从停机模式下唤醒时钟会变慢，要重新配置时钟。
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
        }
        else 
        {
         delay(1000000);
         GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET );
         GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET );
         delay(10000000);
         PWR_WakeUpPinCmd(PWR_WakeUpPin_1,ENABLE);//  Under the standby must be used
         PWR_EnterSTANDBYMode();//外设不保持原先状态
        }      
     }
   }
  
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {

      }
}
#endif
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
