#include "stm32f4xx.h"
#include "main.h"

typedef struct {
	float voltage;
	float current;
	float power;
	float energy;
	float frequency;
	float pf;
	uint16_t alarms;
} PZEM;

void pzem_Init(UART_HandleTypeDef huart);
void pzem_READ(PZEM *pzemhandle);

