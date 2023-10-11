# USART_interrupt

This code is made for NUCLEOF303RE board. 
The problem I am facing that it seems that another interrupt is being triggered (probably the default interrupt wwdg).
I am using only the USART1_interrupt and I have no idea what is trigeering the other interrupt.
please note that once i enable the global interrupt,
the code does not into the while true loop. meaning that it is stuck in another interrupt