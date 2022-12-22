#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pio_i2c.h"
#include <math.h>
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "sht4x.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <string.h>

#define SDA 22
#define SCL 23
#define A0 29
#define A1 28
#define A2 27
#define QTPY_BOOT_PIN 21
#define UART_ID uart1
#define BAUD_RATE 300

#define UART_TX_PIN 20 //UART TX1
#define UART_RX_PIN 5 //UART RX1

#define GPIO_03 3 //For Pico4ML

PIO pio = pio0;
uint sm = 0;
const int addr = 0x44;

int32_t temp,hum;
char stemp[1] = "";
char shum[1] = "";

//get the temp. and humidity from sensor, for REPL use
void get_sensor(){
    read_temp_hum(&temp , &hum, pio, sm, addr);
    printf("temperature: %d\n", temp);
    printf("humidity: %d\n", hum);
    sleep_ms(50);
}

//main loop
int main(){
    stdio_init_all();

    //Setup Uart
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    //GPIO init
    gpio_init(A0);
    gpio_set_dir(A0, GPIO_IN);
    gpio_init(A1);
    gpio_set_dir(A1, GPIO_IN);
    gpio_init(A2);
    gpio_set_dir(A2, GPIO_IN);
    gpio_init(GPIO_03);
    gpio_set_dir(GPIO_03, GPIO_IN);
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    
    //while(stdio_usb_connected()!=true); //used when need to read REPL
    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, SDA, SCL);   

    int mcounter = 0; //other mode: 0-->"TEMP", 1-->"RHUM", 2-->"FACE"， 3-->"Demo"
    char *smode = "0";
    char *sign = " ";

    //For demo use, initilize temp and hum
    int32_t temp_stp = 8;
    int32_t hum_stp = 6;
    int32_t temp_counter = 0;
    int32_t hum_counter = 0;

    //For Ardiuno plotting axis
    float appt;
    float power;
    int32_t appt_int;
    int32_t x_axis;
    int32_t y_axis;

    while(true){
        char str[12] = "";
        sign = " ";
        
        //For demo
        if(gpio_get(A1) == 1){
            sleep_ms(250);
            if(temp_counter == 0){
                temp = -24;
            }
            temp = temp + temp_stp;
            temp_counter ++;
            if(temp >= 44){
                temp_counter = 0;
                temp = 44;
            }
            printf("********************\nA1 is pressed. Set temperature to %d.\n", temp);
        }
        if(gpio_get(A2) == 1){
            sleep_ms(250);
            if(hum_counter == 0){
                hum = -5; //base
            }
            hum = hum + hum_stp;
            hum_counter ++;
            if(hum >= 97){
                hum_counter = 0;
                hum = 97;
            }
            printf("********************\nA2 is pressed. Set humidity to %d.\n", hum);
        }
        /*
        //Apparent Temp
        power = (7.5*temp)/(237.7+temp);
        appt = temp + 0.556*(6.112*pow(10,power)*hum*0.01-10);
        appt_int = (int)appt;
        */

        // If Pico4ML detects a person or The mode has changed
        if(gpio_get(GPIO_03) == 1 || gpio_get(A0) == 1 || gpio_get(QTPY_BOOT_PIN) == 0){
            //Acutal use, not for demo
            //get_sensor();
            //read_temp_hum(&temp , &hum, pio, sm, addr);
            //printf("********************\nFeeling temp is %d\n", appt_int);

            //String Process about negative
            if(temp < 0){
                sign = "-";
                temp = -temp;
            }
            itoa(temp, stemp, 10);
            itoa(hum, shum, 10);
            printf("Input string: temp is %s, hum is %s.\n", stemp, shum);

            //If the mode button is pressed
            if(gpio_get(A0) ==1){
                printf("A0 is pressed.\n");
                switch (mcounter)
                {
                case 0:
                    smode = "0";
                    printf("Case TEMP\n");
                    mcounter ++;
                    break;
                case 1:
                    smode = "1";
                    printf("Case RHUM\n");
                    mcounter ++;
                    break;
                case 2:
                    smode = "2";
                    printf("Case APPT\n");
                    mcounter ++;
                    break;
                case 3:
                    smode = "3";
                    printf("Case FACE\n");
                    mcounter ++;
                    break;
                case 4:
                    smode = "4";
                    printf("Case RAINBOW\n");
                    mcounter ++;
                    break;
                case 5:
                    smode = "5";
                    printf("Case DEMO\n");
                    mcounter = 0;
                    break;
                default:
                    break;
                }

            }

            //If a human is detected
            if(gpio_get(GPIO_03) == 1){
                printf("A human is detected.\n");
                smode = "4";
                printf("Case RAINBOW\n");
            }

            strcat(str, "STR");
            strcat(str, sign);
            if(temp <= 9)
                strcat(str, "0");
            strcat(str, stemp);
            strcat(str, "H");
            if(hum <= 9)
                strcat(str, "0"); 
            strcat(str, shum);
            strcat(str, "M");
            strcat(str, smode);
            strcat(str, "FN");
            
            int32_t ustrlen;
            ustrlen = strlen(str);
            printf("%s, length is %d\n",str,ustrlen);
            printf("smode is %s\n", smode);
            
            //Uart Transmisstion
            uart_puts(UART_ID,str);
            //uart_puts(UART_ID,"STR 42H95M4FN"); // For direct testing
            sleep_ms(500);
        }
    }
}