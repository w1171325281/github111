/**
  ******************************************************************************
  * @file    SysTick/SysTick_Example/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V0.1.0
  * @date    11-November-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "main.h"

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SysTick_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void Func()
{ 
  int i;
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
        PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
        RCC_Configuration();//从停机模式下唤醒时钟会变慢，要重新配置时钟。
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
        }
        else 
        {
         delay(1000000);
         GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET );
         GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET );
         delay(1000000);
         PWR_WakeUpPinCmd(PWR_WakeUpPin_1,ENABLE);//  Under the standby must be used
         PWR_EnterSTANDBYMode();//外设不保持原先状态
        }      
     }
  
   }
}
void  EXTI0_1_IRQHandler(void)
{
    
  if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
  {
    PWR_EnterSleepMode(PWR_SLEEPEntry_WFI);
    EXTI_ClearITPendingBit(EXTI_Line0);
   }
}
void NMI_Handler(void)
{
}
/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
