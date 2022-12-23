#include "pzem.h"
#include "main.h"

uint8_t buf[8] = {0xF8, 0x04, 0x00, 0x00,0x00,0x0A, 0x64, 0x64};
uint8_t rst_buf[4] = {0xF8, 0x42, 0xC2, 0x41};
uint8_t res_buf[25];
uint8_t flag =0;
uint8_t rst_flag = 0;
uint8_t scr_flag = 0;
UART_HandleTypeDef uart;


void pzem_Init(UART_HandleTypeDef huart){
	HAL_UART_Transmit(&huart, (uint8_t*) &rst_buf, 4, 10);
	HAL_UART_Receive(&huart, res_buf, 25, 250);
	uart = huart;
}

void pzem_READ(PZEM *pzemhandle){
		HAL_UART_Transmit(&uart, (uint8_t*) &buf, 8,20);
		HAL_UART_Receive(&uart, res_buf, 25, 250);

		pzemhandle->voltage = ((uint32_t)res_buf[3] << 8 | (uint32_t)res_buf[4]) / 10.0;
		pzemhandle->current = ((uint32_t)res_buf[5] << 8 | (uint32_t)res_buf[6] 
				| (uint32_t)res_buf[7] << 24 | (uint32_t)res_buf[8] << 16) / 100.0;
		pzemhandle->power = ((uint32_t)res_buf[9] << 8 | (uint32_t)res_buf[10] 
				| (uint32_t)res_buf[11] << 24 | (uint32_t)res_buf[12] << 16);
		pzemhandle->energy = ((uint32_t)res_buf[13] << 8 | (uint32_t)res_buf[14] 
				| (uint32_t)res_buf[15] << 24 | (uint32_t)res_buf[16] << 16);
		pzemhandle->frequency = ((uint32_t)res_buf[17] << 8 | (uint32_t)res_buf[18]) / 10.0;
		pzemhandle->pf = ((uint32_t)res_buf[19] << 8 | (uint32_t)res_buf[20]) / 100.0;
		pzemhandle->alarms = ((uint32_t)res_buf[21] << 8 | (uint32_t)res_buf[22]);
}
