#include <stdint.h>
#include "reg.h"
#include "blink.h"

int main(void)
{
	//RCC Enable GPIOA*********
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTA));

	//GPIO Configurations********
	//MODER led pin = 00 => General purpose input mode
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET, MODERy_1_BIT(0));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET, MODERy_0_BIT(0));

	//OT led pin = 0 => Output push-pull
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OTYPER_OFFSET, OTy_BIT(0));

	//OSPEEDR led pin = 00 => Low speed
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(0));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(0));

	//PUPDR led pin = 00 => No pull-up, pull-down
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(0));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(0));

	//RCC Enable SYSCFG**************
	SET_BIT(RCC_BASE + RCC_APB2ENR_OFFSET , SYSCFGEN_BIT); 

	//SYSCFG Configurations***************
    //0000 to select PA0
    WRITE_BITS(SYSCFG_BASE + SYSCFG_EXTICR1_OFFSET , EXTI0_3_BIT ,EXTI0_0_BIT,0b0000);
    
	

	//EXTI Configurations**************
	//set interrupt mask register to "not mask"
	SET_BIT(EXTI_BASE + EXTI_IMR_OFFSET , 0);
    //set falling triger
	SET_BIT(EXTI_BASE + EXTI_FTSR_OFFSET , 0);
    

	//NVIC Configurations
	SET_BIT(NVIC_ISER_BASE + NVIC_ISERn_OFFSET(0), 6); //IRQ6

	blink(LED_BLUE);
}

void exti0_handler(void)
{
	blink_count(LED_ORANGE, 10);

	//clear pending
	SET_BIT(EXTI_BASE + EXTI_PR_OFFSET, 0);
}
