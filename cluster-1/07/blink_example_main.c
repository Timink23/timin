/* Blink Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

static const char* TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO4 32 //red
#define BLINK_GPIO3 4 //white
#define BLINK_GPIO2 19 //yellow
#define BLINK_GPIO1 18 //green

static uint8_t s_led_state1 = 0;
static uint8_t s_led_state2 = 0;
static uint8_t s_led_state3 = 0;
static uint8_t s_led_state4 = 0;


//#ifdef CONFIG_BLINK_LED_RMT
//static led_strip_t* pStrip_a;

static void blink_led(uint8_t s_led_state1, uint8_t s_led_state2, uint8_t s_led_state3, int8_t s_led_state4)
{
    ///* If the addressable LED is enabled */
    //if (s_led_state) {
    //    /* Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color */
    //    pStrip_a->set_pixel(pStrip_a, 0, 16, 16, 16);
    //    /* Refresh the strip to send data */
    //    pStrip_a->refresh(pStrip_a, 100);
    //}
    //else {
    //    /* Set all LED off to clear all pixels */
    //    pStrip_a->clear(pStrip_a, 50);
    //}
    gpio_set_level(BLINK_GPIO1, s_led_state1);
    gpio_set_level(BLINK_GPIO2, s_led_state2);
    gpio_set_level(BLINK_GPIO3, s_led_state3);
    gpio_set_level(BLINK_GPIO4, s_led_state4);
    vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    gpio_set_level(BLINK_GPIO1, 0);
    gpio_set_level(BLINK_GPIO2, 0);
    gpio_set_level(BLINK_GPIO3, 0);
    gpio_set_level(BLINK_GPIO4, 0);
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO1);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BLINK_GPIO2);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO2, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BLINK_GPIO3);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO3, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BLINK_GPIO4);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO4, GPIO_MODE_OUTPUT);
}

//#elif CONFIG_BLINK_LED_GPIO
//
//static void blink_led(void)
//{
//    /* Set the GPIO level according to the state (LOW or HIGH)*/
//    gpio_set_level(BLINK_GPIO, s_led_state);
//}
//
//static void configure_led(void)
//{
//    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
//    gpio_reset_pin(BLINK_GPIO);
//    /* Set the GPIO as a push/pull output */
//    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
//}
//
//#endif

void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();

    while (1) {
        blink_led(0, 0, 0, 0); //0
        blink_led(0, 0, 0, 1); //1
        blink_led(0, 0, 1, 0); //2
        blink_led(0, 0, 1, 1); //3
        blink_led(0, 1, 0, 0); //4
        blink_led(0, 1, 0, 1); //5
        blink_led(0, 1, 1, 0); //6
        blink_led(0, 1, 1, 1); //7 
        blink_led(1, 0, 0, 0); //8
        blink_led(1, 0, 0, 1); //8 
        blink_led(1, 0, 1, 0); //10
        blink_led(1, 0, 1, 1); //11
        blink_led(1, 1, 0, 0); //12
        blink_led(1, 1, 0, 1); //13
        blink_led(1, 1, 1, 0); //14
        blink_led(1, 1, 1, 1); //15

        blink_led(1, 1, 1, 1); //15
        blink_led(1, 1, 1, 0);
        blink_led(1, 1, 0, 1);
        blink_led(1, 1, 0, 0);
        blink_led(1, 0, 1, 1);
        blink_led(1, 0, 1, 0);
        blink_led(1, 0, 0, 1);
        blink_led(1, 0, 0, 0);
        blink_led(0, 1, 1, 1);
        blink_led(0, 1, 1, 0);
        blink_led(0, 1, 0, 1);
        blink_led(0, 1, 0, 0);
        blink_led(0, 0, 1, 1);
        blink_led(0, 0, 1, 0);
        blink_led(0, 0, 0, 1);
        blink_led(0, 0, 0, 0);
    }
}
