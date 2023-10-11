#include "mbed.h"
#include "stm32f303xe.h"
void USART1_IRQHandler(void);
int main()
{ 
    //enable clock of USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    //USART1_Tx PC4 USART1_Rx PC5
    //enable cock of portC and portA
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOAEN;  
    
    //Tx is output of alternate function mode
    GPIOC->MODER &=~GPIO_MODER_MODER4_0 ;
    GPIOC->MODER |=GPIO_MODER_MODER4_1;
    //Rx is output of alternate function mode
    GPIOC->MODER &=~GPIO_MODER_MODER5_0 ;
    GPIOC->MODER |=GPIO_MODER_MODER5_1;
    // PA5 led is output
    GPIOA->MODER |=GPIO_MODER_MODER5_0;

    //Tx output type push-pull
    GPIOC->OTYPER &=~ GPIO_OTYPER_OT_4;
    //Rx output type push-pull
    GPIOC->OTYPER |= GPIO_OTYPER_OT_5;

    //high speed for Tx
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
    //high speed for Rx
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;
    
    //alternate function af7 in pc4 and pc5
    GPIOC->AFR[0] |=(1<<16) | (1<<17) | (1<<18) | (1<<20) | (1<<21) | (1<<22);
    GPIOC->AFR[0] &=~(1<<19) | (1<<23);

    //UARTdiv value
    USART1->BRR = 0x1D4C;

    //enbale transfer,reciever and UART registers
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE ;
    
    //ENABLE TRANSMIT DATA REGISTER EMPTY AND RECIEVE DATA REGISTER NOT EMPTY interrupts
    USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;

    NVIC_SetPriority(USART1_IRQn, 1);
    NVIC_SetPriorityGrouping(2);
    //ENABLE GOLBAL INTERRUPT
    NVIC_EnableIRQ(USART1_IRQn);
    
    while (true) 
    {    
        /*GPIOA->BSRR |= GPIO_BSRR_BS_5;
        HAL_Delay(2000);
        GPIOA->BSRR |= GPIO_BSRR_BR_5;
        HAL_Delay(2000);
       if(USART1->ISR & USART_ISR_RXNE)
        {
            // store recieved data in varibale temp
            char temp = USART1->RDR;
            // set transmitted data as the same as the recieved data
            USART1->TDR = temp;
            //wait until transmission is complete
            while(!(USART1->ISR & USART_ISR_TC))
                ;
        }*/

    }
}

void USART1_IRQHandler(void)
{
    // set led to on
    GPIOA->BSRR |= GPIO_BSRR_BS_5;
    // if received data not empty register equals 1 // there is recieved data
    if(USART1->ISR & USART_ISR_RXNE)
    {
        // store recieved data in varibale temp
        char temp = USART1->RDR;
        // set transmitted data as the same as the recieved data
        USART1->TDR = temp;
        //wait until transmission is complete
        while(!(USART1->ISR & USART_ISR_TC))
        {
            ;
        }
    
    }
    if(USART1->ISR & USART_ISR_TXE)
    {

    }

}

