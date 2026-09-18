#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "IRDA_TEST";

#define UART_PORT        UART_NUM_1
#define TX_PIN           GPIO_NUM_17
#define RX_PIN           GPIO_NUM_16
#define BUF_SIZE         (1024)

void app_main(void) {
    uart_config_t uart_config = {
        .baud_rate  = 115200,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install(UART_PORT, BUF_SIZE * 2, BUF_SIZE * 2, 0, NULL, 0);
    uart_param_config(UART_PORT, &uart_config);
    uart_set_pin(UART_PORT, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    const uint8_t test_data[] = {0xAA, 0x55, 0xFF};
    uint8_t rx_buffer[BUF_SIZE];

    ESP_LOGI(TAG, "UART initialized, starting loopback test...");

    while (1) {
        // Transmit bytes over IrDA port
        uart_write_bytes(UART_PORT, (const char *)test_data, sizeof(test_data));
        ESP_LOGI(TAG, "Sent 3 bytes");

        // Read incoming response from IrDA port
        int len = uart_read_bytes(UART_PORT, rx_buffer, sizeof(rx_buffer), pdMS_TO_TICKS(100));
        
        if (len > 0) {
            ESP_LOGI(TAG, "Received %d bytes:", len);
            ESP_LOG_BUFFER_HEX(TAG, rx_buffer, len);
        } else {
            ESP_LOGW(TAG, "No loopback data received");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}