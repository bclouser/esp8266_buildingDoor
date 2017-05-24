#include <c_types.h>
#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "led.h"


os_timer_t timer;

LOCAL u8 leds[e_numLeds] = {PWM_0_OUT_IO_NUM, PWM_1_OUT_IO_NUM, PWM_2_OUT_IO_NUM, PWM_3_OUT_IO_NUM};

bool ICACHE_FLASH_ATTR setLed(LedNumEnum ledNum, bool on)
{
	if(ledNum < 0 || ledNum > e_numLeds){
		return false;
	}

	if(on)
	{
		os_printf("Setting led(%d) (io num %d) on\n", ledNum, leds[ledNum]);
		// active low
		GPIO_OUTPUT_SET(GPIO_ID_PIN(leds[ledNum]), 0);
	}
	else
	{
		os_printf("Setting led(%d) (io num %d) off\n", ledNum, leds[ledNum]);
		// active low
		GPIO_OUTPUT_SET(GPIO_ID_PIN(leds[ledNum]), 1);
		gpio16_output_set(0);
	}
}

void turnLedsOff()
{
	os_printf("TUrning all leds off\n");
	GPIO_OUTPUT_SET(GPIO_ID_PIN(leds[e_ledNum1]), 1);
}

LOCAL void ICACHE_FLASH_ATTR ledBlink_cb(u8* led)
{
	os_printf("Got a callback\n");
}

void ICACHE_FLASH_ATTR blinkLed(LedNumEnum led, int delay)
{
	os_timer_disarm(&timer);
	os_timer_setfn(&timer, (os_timer_func_t *)ledBlink_cb, &leds[led]);
	os_timer_arm(&timer, 300, 1);
}

void ICACHE_FLASH_ATTR initLeds()
{
	os_printf("Initializing leds\n");
	PIN_FUNC_SELECT(PWM_0_OUT_IO_MUX, PWM_0_OUT_IO_FUNC);
	PIN_FUNC_SELECT(PWM_1_OUT_IO_MUX, PWM_1_OUT_IO_FUNC);
	PIN_FUNC_SELECT(PWM_2_OUT_IO_MUX, PWM_2_OUT_IO_FUNC);
	PIN_FUNC_SELECT(PWM_3_OUT_IO_MUX, PWM_3_OUT_IO_FUNC);

	// gpio is active low, this is turning the led off
	GPIO_OUTPUT_SET(GPIO_ID_PIN(leds[e_ledNum1]), 1);
}