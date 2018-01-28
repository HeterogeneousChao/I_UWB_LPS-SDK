#include "i_uwb_lps.h"
#include "bsp\usart\usart1.h"		  
#include "modules\ilink\ilink_i_uwb_lps.h"
#include "modules\ilink\ilink_ahrs.h"

#include "system_init.h"		  

void I_UWB_LPS_Tag_Data_Update(void)
{
	if(usart1_rx_irq_updata_user_reset_status == 1)
	{
		usart1_rx_irq_updata_user_reset_status = 0;
		
		if(I_UWB_LPS_ROLE == TAG_ROLE)	I_UWB_LPS_Tag_DateFrame0_Unpack(usart1_receive_buf);//���ý������ݳ��� 
		else if(I_UWB_LPS_ROLE == AHRS_ROLE)	AHRS_DataFrame0_Unpack(usart1_receive_buf);;
		
		DMA_SetCurrDataCounter(DMA2_Stream5,usart_rx_length);//���ý������ݳ���
		DMA_Cmd(DMA2_Stream5,ENABLE);													//��DMA��׼���´ν���
	}
}

