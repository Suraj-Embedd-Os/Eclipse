/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"


#define TRUE 1
#define FALSE 0

#define 		mainONE_SHOT_TIMER_PERIOD      pdMS_TO_TICKS( 3333 )
#define			mainAUTO_RELOAD_TIMER_PERIOD   pdMS_TO_TICKS( 500 )

//function prototypes
static void prvSetupHardware(void);
void printmsg(char *msg);
static void prvSetupUart(void);
void prvSetupGpio(void);
void rtos_delay(uint32_t delay_in_ms);


static void prvPeriodicCallBackFun(TimerHandle_t xtimer);
static void prvOneShotCallBackFun(TimerHandle_t xtimer);
//global space for some variable
char usr_msg[250]={0};




TimerHandle_t xAutoReloadTimer, xOneShotTimer;
BaseType_t xTimer1Started, xTimer2Started;


int main(void)
{
	DWT->CTRL |= (1 << 0);//Enable CYCCNT in DWT_CTRL.

	//1.  Reset the RCC clock configuration to the default reset state.
	//HSI ON, PLL OFF, HSE OFF, system clock = 16MHz, cpu_clock = 16MHz
	RCC_DeInit();

	//2. update the SystemCoreClock variable
	SystemCoreClockUpdate();

	prvSetupHardware();

	//Start Recording
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	sprintf(usr_msg,"\r\nThis is Software Timer Demo\r\n");
	printmsg(usr_msg);




	xOneShotTimer=xTimerCreate("oneShot",mainONE_SHOT_TIMER_PERIOD,pdFALSE,0,prvOneShotCallBackFun);

	xAutoReloadTimer=xTimerCreate("periodic",mainAUTO_RELOAD_TIMER_PERIOD,pdPASS,0,prvPeriodicCallBackFun);

	if(xOneShotTimer!=NULL && xAutoReloadTimer!=NULL )
	{

		xTimer1Started=xTimerStart(xOneShotTimer,0);
		xTimer2Started=xTimerStart(xAutoReloadTimer,0);

		if(xTimer1Started!=NULL && xTimer2Started!=NULL)
		{

			vTaskStartScheduler();
		}

	}

	for(;;);
}

uint32_t ulCallCount;
static void prvOneShotCallBackFun(TimerHandle_t xtimer)
{
TickType_t xtick;

  xtick=xTaskGetTickCount();

    sprintf(usr_msg,"One-shot timer callback executing: %u\r\n",xtick);
  	printmsg(usr_msg);
  	ulCallCount++;
}

static void prvPeriodicCallBackFun(TimerHandle_t xtimer)
{

	TickType_t xTimeNow;
	/* Obtain the current tick count. */
	xTimeNow = xTaskGetTickCount();
	/* Output a string to show the time at which the callback was executed. */
	sprintf(usr_msg, "Auto-reload timer callback executing: %u\n\r", xTimeNow );
	printmsg(usr_msg);
	ulCallCount++;
}


static void prvSetupHardware(void)
{
	//Setup Button and LED
	prvSetupGpio();

	//setup UART2
	prvSetupUart();
}

void printmsg(char *msg)
{
	for(uint32_t i=0; i < strlen(msg); i++)
	{
		while ( USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
		USART_SendData(USART2,msg[i]);
	}

	while ( USART_GetFlagStatus(USART2,USART_FLAG_TC) != SET);

}


static void prvSetupUart(void)
{
	GPIO_InitTypeDef gpio_uart_pins;
	USART_InitTypeDef uart2_init;

	//1. Enable the UART2  and GPIOA Peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	//PA2 is UART2_TX, PA3 is UART2_RX

	//2. Alternate function configuration of MCU pins to behave as UART2 TX and RX

	//zeroing each and every member element of the structure
	memset(&gpio_uart_pins,0,sizeof(gpio_uart_pins));

	gpio_uart_pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_uart_pins.GPIO_OType= GPIO_OType_PP;
	gpio_uart_pins.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA, &gpio_uart_pins);


	//3. AF mode settings for the pins
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //PA2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //PA3

	//4. UART parameter initializations
	//zeroing each and every member element of the structure
	memset(&uart2_init,0,sizeof(uart2_init));

	uart2_init.USART_BaudRate = 115200;
	uart2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart2_init.USART_Mode =  USART_Mode_Tx | USART_Mode_Rx;
	uart2_init.USART_Parity = USART_Parity_No;
	uart2_init.USART_StopBits = USART_StopBits_1;
	uart2_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2,&uart2_init);

//	//lets enable the UART byte reception interrupt in the microcontroller
//	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
//
//	//lets set the priority in NVIC for the UART2 interrupt
//	NVIC_SetPriority(USART2_IRQn,5);
//
//	//enable the UART2 IRQ in the NVIC
//	NVIC_EnableIRQ(USART2_IRQn);

	//5. Enable the UART2 peripheral
	USART_Cmd(USART2,ENABLE);

}


void prvSetupGpio(void)
{
// this function is board specific

	//Peripheral clock enable for GPIOA and GPIOC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	GPIO_InitTypeDef led_init, button_init;
	led_init.GPIO_Mode = GPIO_Mode_OUT;
	led_init.GPIO_OType = GPIO_OType_PP;
	led_init.GPIO_Pin = GPIO_Pin_5;
	led_init.GPIO_Speed = GPIO_Low_Speed;
	led_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&led_init);

	button_init.GPIO_Mode = GPIO_Mode_IN;
	button_init.GPIO_OType = GPIO_OType_PP;
	button_init.GPIO_Pin = GPIO_Pin_13;
	button_init.GPIO_Speed = GPIO_Low_Speed;
	button_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&button_init);

	//interrupt configuration for the button (PC13)
	//1. system configuration for exti line (SYSCFG settings)
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);

	//2. EXTI line configuration 13,falling edge, interrup mode
	EXTI_InitTypeDef exti_init;
	exti_init.EXTI_Line = EXTI_Line13;
	exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init);

	//3. NVIC settings (IRQ settings for the selected EXTI line(13)
//	NVIC_SetPriority(EXTI15_10_IRQn,5);
//	NVIC_EnableIRQ(EXTI15_10_IRQn);


}




void rtos_delay(uint32_t delay_in_ms)
{
	uint32_t tick_count_local=0;

	//converting ms to ticks
	uint32_t delay_in_ticks = ( delay_in_ms  * configTICK_RATE_HZ ) / 1000;

	tick_count_local = xTaskGetTickCount();
	while ( xTaskGetTickCount() < (tick_count_local+delay_in_ticks ));
}














