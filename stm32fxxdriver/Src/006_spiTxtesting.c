/*
 * 006_spiTxtesting.c
 *
 *  Created on: Sep 11, 2024
 *      Author: ADMIN
 */
#include "stm32fxx.h"
#include "string.h"
//PB15->SPI2_MOSI
//PB14->MISO
//PB13->SCLK
//PB12->NSS
//AFMODE 5
void SPI2_GPIO_Inits(void){
	//SCLK
	GPIOx_Handle_t SPIPins;
	SPIPins.pGPIOx=GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode=5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_FAST;

	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_14;
	//GPIO_Init(&SPIPins);
	//NSS
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_12;
	//GPIO_Init(&SPIPins);


}
void SPI2_Inits(void){
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx=SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig= SPI_BUS_CFG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SclkSpeed= SPI_SCLK_SPEED_DIV2;//8MHZ
	SPI2Handle.SPIConfig.SPI_DFF=SPI_DFF_8;
	SPI2Handle.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA=SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM=SPI_SSM_EN; //SOFTWARE SLAVE MANAGEMENT ENABLE FOR NSS PIN

	SPI_Init(&SPI2Handle);



}

int main(void){
	char userdata[]="Hello world";
	//Initialize gpio pins as spi2 pins
	SPI2_GPIO_Inits();
	//Initialize spi2 peripheral parameters
	SPI2_Inits();
	//NSS HIGH-> avoid MODF Error
	SPI_SSIConfig(SPI2,ENABLE);
	//enable spi2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);

	SPI_Send(SPI2, (uint8_t*)userdata, strlen(userdata));
	while(1);

	return 0;

	}
