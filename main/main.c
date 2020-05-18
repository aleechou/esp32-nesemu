#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "nofrendo.h"
#include "esp_partition.h"
#include "st7789.h"



char *osd_getromdata() {
	char* romdata;
	const esp_partition_t* part;
	spi_flash_mmap_handle_t hrom;
	esp_err_t err;
	nvs_flash_init();
	part=esp_partition_find_first(0x40, 1, NULL);
	if (part==0) printf("Couldn't find rom part!\n");
	err=esp_partition_mmap(part, 0, 3*1024*1024, SPI_FLASH_MMAP_DATA, (const void**)&romdata, &hrom);
	if (err!=ESP_OK) printf("Couldn't map rom part!(error:%d)\n", err);
	printf("Initialized. ROM@%p\n", romdata);
    return (char*)romdata;
}


esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}




int app_main(void)
{
	// printf("start :)\n");
	
	// TFT_t dev;
	// spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	// lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

	// // 清屏
	// lcdDrawFillRect(&dev, 0, 0, 239, 239, rgb565_conv(0, 0, 0));


	// uint16_t color = rgb565_conv(0, 0, 200);


	// lcdDrawPixel(&dev, 50, 50, color) ;
	// lcdDrawPixel(&dev, 51, 51, color) ;
	// lcdDrawPixel(&dev, 52, 52, color) ;
	// lcdDrawPixel(&dev, 53, 53, color) ;
	// lcdDrawPixel(&dev, 54, 54, color) ;
	// lcdDrawPixel(&dev, 55, 55, color) ;

	// while(1){}


	printf("NoFrendo start!\n");
	nofrendo_main(0, NULL);
	printf("NoFrendo died? WtF?\n");
	asm("break.n 1");
    return 0;
}

