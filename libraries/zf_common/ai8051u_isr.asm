
	CSEG AT 019BH	;UART1 DMA RX中断
	LJMP 0023H		;UART1 中断
	
	CSEG AT 01ABH	;UART2 DMA RX中断
	LJMP 0043H		;UART2 中断
	
	CSEG AT 01BBH	;UART3 DMA RX中断
	LJMP 008BH		;UART3 中断
	
	CSEG AT 01CBH	;UART4 DMA RX中断
	LJMP 0093H		;UART4 中断

	CSEG AT 021BH	;TIMER11 中断
	LJMP 00C3H		;IIC 中断 
	
	END