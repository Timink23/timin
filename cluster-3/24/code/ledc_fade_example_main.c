#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include <string.h>
#include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include <stdlib.h>

#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       (18)
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0

#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE

#define LEDC_TEST_DUTY         (4000)
#define LEDC_TEST_FADE_TIME    (3000)

void app_main(void)
{
    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0,256, 0, 0, NULL, 0));

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HS_MODE,           // timer mode
        .timer_num = LEDC_HS_TIMER,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };
    
    ledc_timer_config(&ledc_timer);

    
    ledc_timer.speed_mode = LEDC_LS_MODE;
    ledc_timer.timer_num = LEDC_LS_TIMER;
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel =
    {
            .channel = LEDC_HS_CH0_CHANNEL,
            .duty = 0,
            .gpio_num = LEDC_HS_CH0_GPIO,
            .speed_mode = LEDC_HS_MODE,
            .hpoint = 0,
            .timer_sel = LEDC_HS_TIMER
    };

    ledc_channel_config(&ledc_channel);

    // Initialize fade service.
    ledc_fade_func_install(0);

    int Test_duty = 5000;

    char arr[10];

    while (1) {
        printf("Choose Led Intensity from 0-9: ");
        gets(arr);
        printf("%s\n", arr);

        if (strcmp(arr, "cycle") == 0) {
            Test_duty = 0;
            int brightness = 0;
            while (Test_duty < 5000) {
                printf("Intensity %d\n", brightness);

                ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, Test_duty);
                ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
                vTaskDelay(25);//25 ms delay req

                Test_duty += 500;
                brightness++;
            }

            vTaskDelay(25);//25 millisecond required
            Test_duty = 4000;
            brightness = 8;
            while (Test_duty >= 0) {
                printf("Intensity %d\n", brightness);
                ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, Test_duty);
                ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);

                vTaskDelay(25);//25ms delay
                Test_duty -= 500;
                brightness--;
            }
        }

        else {
            int num = atoi(arr);

            switch (num) {
            case 0:
                Test_duty = 0;
                break;
            case 1:
                Test_duty = 500;
                break;
            case 2:
                Test_duty = 1000;
                break;
            case 3:
                Test_duty = 1500;
                break;
            case 4:
                Test_duty = 2000;
                break;
            case 5:
                Test_duty = 2500;
                break;
            case 6:
                Test_duty = 3000;
                break;
            case 7:
                Test_duty = 3500;
                break;
            case 8:
                Test_duty = 4000;
                break;
            case 9:
                Test_duty = 4500;
                break;
            default:
                printf("Enter a value between 0 and 9 please.\n");
                break;
            }

            printf("LEDC selected = %d\n", Test_duty);
            ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, Test_duty);
            ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
        }
    }
}
