# 519Moodlight.github.io
All contents are written first in the README file.

Contents from Canvas:
- A project showcase (brief project overview with cool photos/videos, probably on your main page).
- Project instructions, in enough detail that someone else could re-create your project (components used, assembly details, block diagrams, description of your RP2040 dev environment, links to your code, etc).
- Narrative overview of your project's development, and how it evolved from proposal to demo day (showing photos/screenshots/gifs at each stage).
- Any significant issues you had to troubleshoot, and how you solved them or adapted your plans (including diagrams, REPL sessions, scope traces, etc.)
- Reflections on your design and components/parts you selected, including advantages/disadvantages, whether you would recommend a similar design to future teams, and other design approaches/components you might try next time.
- A bit more detail about some feature or accomplishment you found particularly satisfying.
- An explanation of the PIO part of your code, including a diagram of the overal logic, as well as an introduction to the RP2040 PIO module and what makes it a unique asset for a microcontroller.
- Team overview (ideally with brief photos/bios, up to you) with links to your individual github accounts or personal pages.

- Use your new team github organization to publish a repo containing your project code. Include a README.md file with a brief overview and block diagram of the code in this repo. 
- Upload all photos/videos you've taken for project documentation (components, debugging, progress, final demos, demo day action shots), as well as your demo day slides you set up on your monitors, to this Google Drive Links to an external site.under your team folder. Send me a note if you're planning to upload more than 10GB.

## Project Showcase
Our team aims to invent a sensing device that will measure the in-room apparent temperature by detecting room temperature and humidity. The user can customize their favoriate display mode. The device has six modes: 
- Mode TMEP: shows the room temperature
- Mode RHUM: shows the room relative humidity
- Mode FEEL: shows the in-room apparent temperature, i.e. how your body feels in the room
- Mode FACE: shows either a smiling or crying face based on temperatuer and humidity, can be customized by the user
- Mode RAINBOW: shows a heat index map across all the measuing range for the sensor and indicate the "location" of the current measurements
- Mode ROLL: shows all the five modes in a rolling sequence

All of the indications are presented on a 16x32 RGB LED matrix panel. The device is also equipped with a person detection function. When ever a human is reading the infomation on the panel, the panel will be changed to the user's favorite mode. For example, if the user prefers to see the RAINBOW mode, he/she will set the mode to their prefer mode. The next time when he/she reads the the panel, the camera will detect human activity and change the display to RAINBOW mode until they leave.

![DSC00521](https://user-images.githubusercontent.com/105755054/209399661-72d4c804-97a8-429d-8177-e13ec1642303.JPG)
![DSC00517](https://user-images.githubusercontent.com/105755054/209399679-f63e8f3c-6dd7-4774-b391-c7e45855b4cc.JPG)
![DSC00518](https://user-images.githubusercontent.com/105755054/209399670-80a55a39-d921-40ad-bdda-d567670175ac.JPG)
![DSC00519](https://user-images.githubusercontent.com/105755054/209399728-d41d9359-d014-4621-a9dd-84a485e6c4e3.JPG)
![DSC00520](https://user-images.githubusercontent.com/105755054/209399611-c63fcece-f27d-4203-9335-e9cd4a059b81.JPG)

## Project instrcutions
### Components:
- Pico4ML
- Adafruit SHT40 
- Adafruit QT-PY 2040
- 16x32 RGB LED matrix panel 
- PC/Laptop as REPL screen (Can be removed in realiife application)
- Jump wires
- Resistors [Need to specify actual values]
- Adafruit Perma-Proto Half-sized Breadboard PCB

### Block diagram:

![image](https://user-images.githubusercontent.com/114244957/209054737-e132e7d7-39e1-4b68-8af5-1b68817cdfec.png)

### Connection diagram: [maybe can be simplified more, combine two diagrams together]

![WechatIMG581](https://user-images.githubusercontent.com/114244957/209051956-f2047703-e310-42d6-8110-a75a9b334fee.jpeg)

![WechatIMG582](https://user-images.githubusercontent.com/114244957/209051972-e2344b0c-3826-45e2-a542-591ec6ee5786.jpeg)

### RP2040 development environment

### Links to codes
There are mainly 
## Project development
### Beginning

### Midpoint Checkput
The team has setup four midpoint checks to ensure that the team have a right pace in the project. The four checkput items are:
- Pico4ML is able to perform person detection and return signals.
- Adafruit SHT40 is able to return humidity and temperature values.
- LCD can communicate with RP2040.
- Some kind of REPL that returns sensor data.

In the midepoint check, the team has successfully performed person detection in Pico4ML. Pico4ML produces a "person score" that shows if the detected object is a person. The score range from negative to positive. When the score is over 90, the detected object is a person. Usually, a human in a goot light and backgroun environemnt will get a score at around 110. The team was thinking to use I2C to directly tansfer this "person score" to RP2040. RP2040 will do the calculation.

The team has also successfully perform humidity and temperature detection in SHT40. THe sensor can have a directly communication with the RP2040 using PIO. More detailed discription about using PIO is discussed in the later section. However, the team realized that using a LCD as the display cannot give out the most infomation. Since our project highly rely on the heat index map (shown below). Our instructor gave the advice that the team should inplement the heat map to the display. LCD would not be sufficient. Thus, after discussion, the team has decided to use a 16x32 RGB LED matrix panel as the final display.

![image](https://user-images.githubusercontent.com/114244957/209482149-3001af36-f5fa-468c-a7f0-c49ae5233d5d.png)




### Final Design
After a more detailed look at the RP2040 pins, the team realized that they don't have enough pins to achieve more complex communication. Thus, the team has simplified the communication method. Instead of useing I2C to communciate between Pico4ML and RP2040, the team has chosen to use ```GPIO``` high and low voltage as the signal. 

The team's initial plan is to use two QTPY boards to communicate. One is only responsible for getting the sensor data, the other will be the MAIN board that collects all the information and intergrate the together. After discussion, the team realized that one single board can finish all the work. Thus, 


## Reflections
Design & components selection (advantages and disadvantages)

## Feature Highlights
- Transfer Humidity and Temperature values to QTPY2040 using uart
- Translate PWM signal output into Arduino readable signal (PWM or Analog) ??? need modification
- Concise information transferred from Pico4ML about person detection 
- Intelligent sensor that will only turn on when a human is close-by 
- Vivid graphic display using LED matrix 
- 6 models display control -- humidity adjust, temperature adjust, feeling temperature, visualization (specific face patterns), rainbow (10 colors to show different humidity and temperature), DEMO (being able to control HUMIDITY ADJUST & TEMPERATURE ADJUST)

## PIO in use
- I2C communication protocol base on PIO 

- Basic Pseudo Code of SH4X Temp.&Humidity Sensor with I2C Protocol

![Screen Shot 2022-12-23 at 14 57 51](https://user-images.githubusercontent.com/105755054/209400650-359622ef-bf4a-4e53-b3c9-4f99f7749005.png)

![Screen Shot 2022-12-23 at 15 09 40](https://user-images.githubusercontent.com/105755054/209401537-53491948-e8ca-4f8b-a470-d835c4b929f1.png)


- SHT4X Hearder

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
-  SHT4X C code with Explaination

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
### Diagram of the overal logic
- Functional Block Diagram of SH4X Sensor 

![Screen Shot 2022-12-23 at 15 14 31](https://user-images.githubusercontent.com/105755054/209403700-2b47f540-c5d8-4c41-a90c-52999b19417e.png)


- QTPY2040 and SHT40 with I2C

![Screen Shot 2022-12-23 at 15 38 48](https://user-images.githubusercontent.com/105755054/209403649-c859e95d-843f-4192-a022-69d03cebf5af.png)


### Introduction to the RP2040 PIO module
[discuess what makes it a unique asset for a microcontroller]

## Team overview 
(ideally with brief photos/bios, up to you) with links to your individual github accounts or personal pages
- Katrina Ji

Personal github: https://github.com/katrinaji

Email: katji@seas.upenn.edu

- Yuchen Wang

Personal github: wangybv@seas.upenn.edu


