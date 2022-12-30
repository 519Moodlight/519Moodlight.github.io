# ESE 519Moodlight
![image](https://user-images.githubusercontent.com/114244957/210037409-66f8b48e-220a-4067-9869-5d23ebac4f38.png)

## Project Showcase
Our team aims to invent a sensing device that will measure the in-room apparent temperature by detecting room temperature and humidity. The user can customize their favorite display mode. The device has five modes: 

- Mode TMEP: shows the room temperature
- Mode RHUM: shows the room relative humidity
- Mode FEEL: shows the in-room apparent temperature, i.e. how your body feels in the room 
- Mode FACE: shows either a smiling or crying face based on temperature and humidity, can be customized by the user
- Mode RAINBOW: shows a heat index map across all the measuring range for the sensor and indicate the “location” of the current measurements 

All of the indications are presented on a 16x32 RGB LED matrix panel. The device is also equipped with a person detection function. Whenever a human is in the vision area of the camera, the panel will be changed to a user’s preferred mode. For example, if the user prefers to see the RAINBOW mode, he/she will set the mode to their prefer mode first. The next time when he/she reads the the panel, the camera will detect human activity and change the display to RAINBOW mode until they leave.

![DSC00521](https://user-images.githubusercontent.com/105755054/209399661-72d4c804-97a8-429d-8177-e13ec1642303.JPG)
![DSC00517](https://user-images.githubusercontent.com/105755054/209399679-f63e8f3c-6dd7-4774-b391-c7e45855b4cc.JPG)
![DSC00518](https://user-images.githubusercontent.com/105755054/209399670-80a55a39-d921-40ad-bdda-d567670175ac.JPG)
![DSC00519](https://user-images.githubusercontent.com/105755054/209399728-d41d9359-d014-4621-a9dd-84a485e6c4e3.JPG)
![DSC00520](https://user-images.githubusercontent.com/105755054/209399611-c63fcece-f27d-4203-9335-e9cd4a059b81.JPG)

A brief introduction video:
https://youtu.be/Q91RQ9lhCjs

## Project instructions
### Components:
- Pico4ML
- PC/Laptop as REPL screen (Can be removed in real life application)
- Adafruit SHT40
- Adafruit Perma-Proto Half-sized Breadboard PCB
- Adafruit QT-PY 2040
- 16x32 RGB LED matrix panel
- Arduino Uno Rev3

### Block diagram:
![image](https://user-images.githubusercontent.com/114244957/209054737-e132e7d7-39e1-4b68-8af5-1b68817cdfec.png)

### Connection diagram:
![image](https://user-images.githubusercontent.com/114244957/210038095-91d749de-a1d0-4a9c-b667-0490e970d384.png)
![image](https://user-images.githubusercontent.com/114244957/210038099-a5e1e9bc-2d51-4218-a9d0-3027a37649e9.png)

### Development environment

- Vidusl Studio Code Version: 1.74.2
- Visual Studio Code Version: 1.73.1
```
Test on: MacBook Pro (14-inch, 2021)

Software: macOS Monterey 12.6 
```

- Arduino IDE Version: 1.8.20
```
Test on: MacBook Pro (14-inch, 2021)

Software: macOS Monterey 12.6 
```
    
### Links to codes
See Team REPO. 

## Project development
### Kick-off
This the the team’s initial proposal slideshow. A detailed description about the project is shown in the video. 
https://docs.google.com/presentation/d/1t87cv9p3CeJUlsETCPSfEi2vsW76WDrAiFLQtDDplcw/edit?usp=sharing
https://youtu.be/xyOEmyO56Lc

### Midpoint Checkup
This the the team’s midpoint checkup slideshow. It is for internal use during the development of the project.
https://docs.google.com/presentation/d/15bB733aYIH5O1ynS-uNRryCd-YGT2AP3RCA227Z42LM/edit?usp=sharing

The team has setup four midpoint checks to ensure that the team have a right pace in the project. The four checkpoint items are: - Pico4ML is able to perform person detection and return signals. - Adafruit SHT40 is able to return humidity and temperature values. - LCD can communicate with RP2040. - Some kind of REPL that returns sensor data.

In the midpoint check, the team has successfully performed person detection in Pico4ML. Pico4ML produces a “person score” that shows if the detected object is a person. The score range from negative to positive. When the score is over 90, the detected object is a person. Usually, a human in a good light and background environment will get a score at around 110. The team was thinking to use I2C to directly transfer this “person score” to RP2040. RP2040 will do the calculation.

The team has also successfully perform humidity and temperature detection in SHT40. The sensor can have a directly communication with the RP2040 using PIO. More detailed description about using PIO is discussed in the later section. However, the team realized that using a LCD as the display cannot give out the most information. Since our project highly rely on the heat index map (shown below). Our instructor gave the advice that the team should implement the heat map to the display. LCD would not be sufficient. Thus, after discussion, the team has decided to use a 16x32 RGB LED matrix panel as the final display.

![image](https://user-images.githubusercontent.com/114244957/209482149-3001af36-f5fa-468c-a7f0-c49ae5233d5d.png)

The team always had REPL to indicate the chip process and data return.

### Final Design
This is the team’s final demo day slideshow. It was initially in slides. During the demo day, it was changed to a single page poster. 
https://docs.google.com/presentation/d/1gsq2rLiZDhrBSmuCHu-VE6WdknTC6gEK/edit?usp=sharing&ouid=117714499329064750219&rtpof=true&sd=true

After a more detailed look at the RP2040 pins, the team realized that they don’t have enough pins to achieve more complex communication. Thus, the team has simplified the communication method. Instead of using I2C to communicate between Pico4ML and RP2040, the team has chosen to use GPIO high and low voltage as the signal.

During the final stage, the team ensured that all the modules are working individually. The team’s main focus was on the communication. The team’s initial plan was to use two QTPY boards to communicate. One would be responsible for getting the sensor data, the other would be the MAIN board that collects all the information and integrate the together. After discussion, the team realized that one single board can finish all the work. Since the communication process has been simplified, Pico4ML and QTPY will only communicate using one GPIO pin. The new RGB LED matrix will have to use an Arduino board. The communication between Arduino and QTPY is UART.

## Reflections
Design & components selection The team’s initial design is to use two QTPY 2040 and one Pico4ML. It was designed so that the project would be highly “modulated”. Each teammate could work on their own component without interference. However, this design would require a lot of communication among three boards. The power consumption would also be high. During project development, the team has changed their strategy to integrate all functions to as few hardware as possible. There are two reasons:

1. The team has change from LCD display to a larger LED display. The larger LED display will be more visible from long distance and contains more information. To implement the display, the team used an Arduino Uno Rev3. This increased the number of boards in the system. Thus, the team decided to reduce one QTPY 2040 to simplify the system.
2. The device was designed to be mounted on the wall. The team would like to reduce the weight and size of the device to make it more compact.

## Feature Highlights
- Transfer Humidity and Temperature values in QTPY2040 to Arduino Uno Rev3 using UART
UART needs two ports — TX and RX. The team picked port 20 and 5 as the UART ports on QTPY 2040 as recommended.
![image](https://user-images.githubusercontent.com/114244957/210037877-1ba00a3b-8046-4206-9eeb-247f92173d57.png)
```
#define UART_TX_PIN 20 //UART TX1
#define UART_RX_PIN 5 //UART RX1
```
The team picked port 12 and 13 as the TX and RX for Arduino. The communication protocol for our system is a string. For example, if the temperature is negative 9 degree calculus and humidity is 54%, the string will be STR-09H54M0FN . If the temperature is 23 degree calculus and humidity is 89%, the string will be STR 23H89M0FN . The meaning of M0 will be explained in the next.
```
//Start forming a string
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
```
- Five-mode control for Display
There are five modes for this device. 1) Temperature, 2) Humidity, 3) Feeling temperature, 4) Face visualization (specific face patterns), 5) Rainbow (10 colors to show different humidity and temperature). Every time the Mode button is pressed, the mode will increment by one.
```
//String Process about negative
if(temp < 0){
    sign = "-";
    temp = -temp;
}
itoa(temp, stemp, 10);
itoa(hum, shum, 10);
printf("Input string: temp is %s, hum is %s.\n", stemp, shum);
```
```
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
```
- Temperature and Humidity adjustment for DEMO.
Since the team would like to present all of the functions of the device, two extra buttons have been added. In this way, the temperature and humidity can be manually set for demo use.
```
//For demo use, initilize temp and hum
int32_t temp_stp = 8;
int32_t hum_stp = 6;
int32_t temp_counter = 0;
int32_t hum_counter = 0;

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
```

## PIO in use
- I2C communication protocol base on PIO

- Basic Pseudo Code of SH4X Temp.&Humidity Sensor with I2C Protocol

![Screen Shot 2022-12-23 at 14 57 51](https://user-images.githubusercontent.com/105755054/209400650-359622ef-bf4a-4e53-b3c9-4f99f7749005.png)

![Screen Shot 2022-12-23 at 15 09 40](https://user-images.githubusercontent.com/105755054/209401537-53491948-e8ca-4f8b-a470-d835c4b929f1.png)


- SHT4X Header

```
#ifndef SHT4X_H
#define SHT4X_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pio_i2c.h"

void read_temp_hum(int32_t *temp, int32_t *hum, PIO pio, uint sm, uint32_t addr);

#endif

```
-  SHT4X C code with Explanation

```
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pio_i2c.h"
#include <math.h>

//enable the sensor and measure temp. and hum.
#define INIT_CONFIG 0xFD 

//address of sht40
const int addr = 0x44; 
#define SDA 22
#define SCL 23

//using PIO0 and SM0 as I2C trasimission 
PIO pio = pio0; 
uint sm = 0;

void read_temp_hum(int32_t *temp, int32_t *hum, PIO pio, uint sm, uint32_t addr){

    //create an empty array for storing the starting-comment of SH4X
    uint8_t tx_bytes[1];  
    
    //create an empty array for storing the data reading from the I2C data parts
    uint8_t data[6];
    
    //Transmit the starting comment to SH4X sensor via I2C writing
    tx_bytes[0] = INIT_CONFIG;
    pio_i2c_write_blocking(pio, sm, addr, tx_bytes, 1, true);
    sleep_ms(10);
    
    //Read data from the I2C slaver with 6 Bytes each period
    pio_i2c_read_blocking(pio, sm, addr, data, 6, false); 
    
    //combine the raw-temperature data togeter
    int raw_temperature = data[0]*256 + data[1]; 
    
    //combine the raw-humidity data 
    int raw_humidity = data[3]*256 + data[4];
    
    //covert the raw data to readable temperatire and humidity
    float termperature = ((175 * (raw_temperature/65536.00)) - 45.00);
    float humidity = ((125 * (raw_temperature/65536.00)) - 6.00);
    
    //return the termperture and humidity with integers
    *temp = termperature;
    *hum = humidity;
}
```
### Diagram of the overall logic
- Functional Block Diagram of SH4X Sensor 

![Screen Shot 2022-12-23 at 15 14 31](https://user-images.githubusercontent.com/105755054/209403700-2b47f540-c5d8-4c41-a90c-52999b19417e.png)


- QTPY2040 and SHT40 with I2C

![Screen Shot 2022-12-23 at 15 38 48](https://user-images.githubusercontent.com/105755054/209403649-c859e95d-843f-4192-a022-69d03cebf5af.png)


### Introduction to the RP2040 PIO module
One unique feature of the RP2040 microcontroller from the Raspberry Pi Foundation is its Programmable I/O (PIO) peripheral. The focus of PIO is serial communication. Most microcontrollers have hardware support for popular serial protocols such as I²C, SPI, and UART. However, this hardware support is always limited both in the number of serial interfaces and the types of serial interfaces that can be used, such as Arduino uno Rev3 only having 1 UART port. If you have a non-standard serial interface you need to support, you may have to resort to bit-banging I/O pins to implement it, tying up the microcontroller core to get the timing right. PIO aims to solve this problem by providing a highly configurable, programmable I/O peripheral that will take care of the bit-banging and provide simple input and output FIFO queues to the microcontroller core.

There are two PIO blocks with four state machines each, that can independently execute sequential programs to manipulate GPIOs and transfer data. Unlike a general-purpose processor, PIO state machines are highly specialized for IO, with a focus on determinism, precise timing, and close integration with fixed-function hardware. Each state machine and its supporting hardware occupy approximately the same silicon area as a standard serial interface block, such as an SPI or I2C controller. However, PIO state machines can be configured and reconfigured dynamically to implement numerous different interfaces.

In our project, we used PIO_I2C to replace the traditional I2C protocol. There are some PIO examples that we have modified to be able to use in our project.
```
pio_i2c_write_blocking(pio, sm, addr, tx_bytes, 1, true);
pio_i2c_read_blocking(pio, sm, addr, data, 6, false); 
```

## Team overview 
(ideally with brief photos/bios, up to you) with links to your individual github accounts or personal pages
- Katrina Ji

Personal github: https://github.com/katrinaji

Email: katji@seas.upenn.edu

- Yuchen Wang

Personal github: wangybv@seas.upenn.edu

- Chongyuan Zhang

Email: zcy6@seas.upenn.edu


