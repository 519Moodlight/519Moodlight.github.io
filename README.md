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
![DSC00520](https://user-images.githubusercontent.com/105755054/209399611-c63fcece-f27d-4203-9335-e9cd4a059b81.JPG)
![DSC00521](https://user-images.githubusercontent.com/105755054/209399661-72d4c804-97a8-429d-8177-e13ec1642303.JPG)
![DSC00518](https://user-images.githubusercontent.com/105755054/209399670-80a55a39-d921-40ad-bdda-d567670175ac.JPG)
![DSC00517](https://user-images.githubusercontent.com/105755054/209399679-f63e8f3c-6dd7-4774-b391-c7e45855b4cc.JPG)
![DSC00519](https://user-images.githubusercontent.com/105755054/209399728-d41d9359-d014-4621-a9dd-84a485e6c4e3.JPG)

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

## Project development

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
[PIO Code Explain]


### Diagram of the overal logic

### Introduction to the RP2040 PIO module
[discuess what makes it a unique asset for a microcontroller]

## Team overview 
(ideally with brief photos/bios, up to you) with links to your individual github accounts or personal pages
- Katrina Ji

Personal github: 
- Yuchen Wang

Personal github: wangybv@seas.upenn.edu
- Ryan Zhang

Personal github:

