
#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "gpio.h"
#include "door.h"
#include "led.h"


static os_timer_t closeDoorTimer;
static const int holdDoorOpenMilliSeconds = 4 * 1000; // 4 seconds
static bool doorOpen = false;


void ICACHE_FLASH_ATTR initDoorControl(void){

	// Tell pin mux to make it a gpio
	PIN_FUNC_SELECT(OUTPUT1_IO_MUX, OUTPUT1_IO_FUNC);
	// Set pin as an output... or am i just writing a 0?
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT1_IO_NUM), 0);
}

void ICACHE_FLASH_ATTR closeDoorCallback(void){
	os_printf("Ok, done holding door open. Closing door!\r\n");
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT1_IO_NUM), 0);
	// turn off timer
	os_timer_disarm(&closeDoorTimer);
	doorOpen = false;
}

void openBuildingDoor(void){
	if(doorOpen)
	{
		os_printf("Door already open, not touching it\n");
		return;
	}
	os_printf("Opening building door!\r\n");
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT1_IO_NUM), 1);
	os_timer_setfn(&closeDoorTimer, (os_timer_func_t *)closeDoorCallback);
	os_timer_arm(&closeDoorTimer, holdDoorOpenMilliSeconds, 0);
	os_printf("Holding door open!\r\n");
	doorOpen=true;
}


