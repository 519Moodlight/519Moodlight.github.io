#include <SoftwareSerial.h>
#include <RGBmatrixPanel.h>
#include<string.h>
#include<math.h>
#include<stdio.h>
#define CLK  8  
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define PICO_ML 11

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void draw_smile_face();
void draw_cry_face();
void read_temp_humidity();
void display_temp();
void display_humidity();
void display_feel_temp();
int get_temp();
int get_hum();
void face_indicator();
void plot_grad();
void display_position();

const byte rxPin = 12;
const byte txPin = 13;

char t0, t1, t2, h1, h2, mode;
int val;

SoftwareSerial mySerial(rxPin,txPin);

void setup() {
  Serial.begin(9600);
  matrix.begin();
  mySerial.begin(300);
  pinMode(PICO_ML, INPUT);
}

void loop() {
  read_temp_humidity(&t0, &t1, &t2, &h1, &h2, &mode);
  val = digitalRead(PICO_ML);
  //display_position(t0, t1, t2, h1, h2);
  //delay(100);

  if (mode == '0'){
    if (val == 1){
      display_position(t0, t1, t2, h1, h2);
    }
    else{
    display_temp(t0, t1, t2);
    }
  }
  else if (mode == '1'){
    if (val == 1){
      display_position(t0, t1, t2, h1, h2);
    }
    else{
    display_humidity(h1, h2);
    }
  }
  else if (mode == '2'){
     if (val == 1){
      display_position(t0, t1, t2, h1, h2);
    }
    else{
    display_feel_temp(t0, t1, t2, h1, h2);
    }
  }
  else if (mode == '3'){
     if (val == 1){
      display_position(t0, t1, t2, h1, h2);
    }
    else{
    face_indicator(t0, t1, t2, h1, h2);
    }
  }
 if (mode == '4' ){
    if (val == 1){
      display_position(t0, t1, t2, h1, h2);
    }
    else{
    display_position(t0, t1, t2, h1, h2);
    }
  }
  else if (mode == '5'){
    if (val == 1){
      display_position(t0, t1, t2, h1, h2);
    }
    else{
    display_temp(t0, t1, t2);
    display_humidity(h1, h2);
    display_feel_temp(t0, t1, t2, h1, h2);
    face_indicator(t0, t1, t2, h1, h2);
    display_position(t0, t1, t2, h1, h2);
    }
  }
 
  //delay(1000);
}

void read_temp_humidity(char *t0, char *t1, char *t2, char *h1, char *h2, char *m1){
  String data = "STR 22H55FN";
  if (mySerial.available() > 0){
    data = mySerial.readString();
    
    //start reading data and makesure the first 3bit is STR 
    if (data[0] == 'S' || data[1] == 'T' || data[2] == 'R'){
      *t0 = data[3];
      *t1 = data[4];
      *t2 = data[5];
    }
    
    if (data[6] == 'H'){
      *h1 = data[7];
      *h2 = data[8];
      
    }

    if (data[9] == 'M'){
      *m1 = data[10];
    }
    Serial.println(data);
  }
}

void draw_smile_face(){
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.drawCircle(7, 7, 7, matrix.Color333(7, 7, 0));
  matrix.drawPixel(4-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(7-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(6-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(10, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(12, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(11, 5-1, matrix.Color333(7, 0, 0));
 
  // fill a violet circle
  //matrix.fillCircle(23, 7, 7, matrix.Color333(7, 7, 0));
  matrix.drawLine(6, 11, 8, 11, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5, 10, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 10, matrix.Color333(7, 0, 0));
  delay(1500);
}

void draw_cry_face(){
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.drawCircle(7, 7, 7, matrix.Color333(7, 0, 0));
  matrix.drawPixel(4-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(7-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(6-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(10, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(12, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(11, 5-1, matrix.Color333(7, 0, 0));
 
  // fill a violet circle
  //matrix.fillCircle(23, 7, 7, matrix.Color333(7, 7, 0));
  matrix.drawLine(6, 11-1, 8, 11-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5, 12-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 12-1, matrix.Color333(7, 0, 0));
  delay(1500);
  }
 
void display_temp(char t0, char t1, char t2){
  int r, g, b;
  int temp;
  if(t0 == ' '){
    temp = ((int) t1 - 48)*10 + ((int) t2 -48);
  }
  else if (t0 == '-'){
    temp = -1 *(((int) t1 - 48)*10 + ((int) t2 -48));
  }

  if (temp < 0){
    r = 0;
    g = 0;
    b = 7;
  }
  else if (1 <= temp && temp < 10){
    r = 0;
    g = 7;
    b = 7;
    }
  else if (10 <= temp && temp < 20){
    r = 4;
    g = 7;
    b = 0;
    }
  else if (20 <= temp && temp < 25){
    r = 7;
    g = 7;
    b = 0;
    }
  else if (25<= temp && temp < 30){
    r = 7;
    g = 4;
    b = 0; 
    }   
   else if (30<= temp ){
    r = 7;
    g = 0;
    b = 0;
    } 
    
  //Serial.println(temp);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('T');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('E');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('M');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('P');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print(':');
  
  matrix.setCursor(1, 9);  //next line
  matrix.setTextSize(1);   // size 1 == 8 pixels high
  
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print(t0);
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print(t1);
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print(t2);

  //matrix.drawPixel(21,9, matrix.Color333(7,7,7));
  matrix.drawPixel(20,9, matrix.Color333(7,7,7));
  matrix.drawPixel(21,8, matrix.Color333(7,7,7));
  matrix.drawPixel(20,8, matrix.Color333(7,7,7));
  matrix.setCursor(22, 9);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1); 
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('C');

  delay(1500); 
}

void display_humidity(char h1, char h2){
  int r, g, b;
  int hum;
  hum = ((int) h1 - 48)*10 + ((int) h2 -48);

  if (hum < 30){
    r = 7;
    g = 0;
    b = 0;
   }
  else if (30 <= hum && hum< 60){
    r = 3;
    g = 7;
    b = 3;
   }
  else if (60 <= hum){
    r = 0;
    g = 0;
    b = 7; 
   }   
//Serial.println(hum);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('R');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('H');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('U');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('M');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print(':');
  
  matrix.setCursor(1, 9);  //next line
  matrix.setTextSize(1);   // size 1 == 8 pixels high
  
  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print(' ');
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print(h1);
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print(h2);
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('%');

  delay(1500);

}

void display_feel_temp(char t0, char t1, char t2, char h1, char h2){
  int r, g, b;
  int T, H;
  int HI;

  T = get_temp(t0, t1, t2);
  H = get_hum(h1, h2);

  float c1 = (7.5*T)/(237.7+T);
  
  HI = T + 0.556*(6.112*pow(10,c1)*H*0.01-10);

  char feel_temp[2];
  itoa(HI, feel_temp, 10);
  //Serial.println(feel_temp);

  if (HI < 0){
    r = 0;
    g = 0;
    b = 7;
  }
  else if (1 <= HI && HI < 10){
    r = 0;
    g = 7;
    b = 7;
    }
  else if (10 <= HI && HI < 20){
    r = 4;
    g = 7;
    b = 0;
    }
  else if (20 <= HI && HI < 25){
    r = 7;
    g = 7;
    b = 0;
    }
  else if (25<= HI && HI < 30){
    r = 7;
    g = 4;
    b = 0; 
    }   
   else if (30<= HI ){
    r = 7;
    g = 0;
    b = 0;
    } 
    
  //Serial.println(temp);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('F');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('E');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('E');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('L');
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print(':');
  
  matrix.setCursor(1, 9);  //next line
  matrix.setTextSize(1);   // size 1 == 8 pixels high
  
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print('*');
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print(feel_temp[0]);
  matrix.setTextColor(matrix.Color333(r,g,b));
  matrix.print(feel_temp[1]);

  //matrix.drawPixel(21,9, matrix.Color333(7,7,7));
  matrix.drawPixel(20,9, matrix.Color333(7,7,7));
  matrix.drawPixel(21,8, matrix.Color333(7,7,7));
  matrix.drawPixel(20,8, matrix.Color333(7,7,7));
  matrix.setCursor(22, 9);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1); 
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('C');
  Serial.println(HI);
  delay(1500); 
  
}

int get_temp(char t0, char t1, char t2){
  int temp;
  if(t0 == ' '){
    temp = ((int) t1 - 48)*10 + ((int) t2 -48);
  }
  else if (t0 == '-'){
    temp = -1 *(((int) t1 - 48)*10 + ((int) t2 -48));
  }
  return temp;
}

int get_hum(char h1, char h2){

  int hum;
  hum = ((int) h1 - 48)*10 + ((int) h2 -48);
  return hum;
  }

void face_indicator(char t0, char t1, char t2, char h1, char h2){
  int temp, humidity;
  temp = get_temp(t0, t1, t2);
  humidity = get_hum(h1, h2);
  if ((humidity >= 40 && humidity <= 60) && (temp >= 18 && temp <= 24)){
    draw_smile_face();
  }
  else{
    draw_cry_face();
    }
}

void plot_grad(){
  //C1
  matrix.fillRect(0,0,3,16,matrix.Color333(7,0,7));
  matrix.drawLine(3,4,3,15, matrix.Color333(7,0,7));

  //C2
  matrix.fillRect(3,0,5,4,matrix.Color333(7,3,6));
  matrix.fillRect(4,4,4,12,matrix.Color333(7,3,6));
  matrix.drawLine(8,11,8,15, matrix.Color333(7,3,6));

  //C3
  matrix.fillRect(8,0,2,11,matrix.Color333(0,0,7));
  matrix.drawLine(9,11,9,15, matrix.Color333(0,0,7));
  matrix.drawLine(10,4,10,15, matrix.Color333(0,0,7));

  //C4
  matrix.fillRect(10,0,4,4,matrix.Color333(0,2,7));
  matrix.fillRect(11,4,4,6,matrix.Color333(0,2,7));
  matrix.fillRect(11,10,5,6,matrix.Color333(0,2,7));
  matrix.drawPixel(16, 15, matrix.Color333(0, 2, 7));

  //C5
  matrix.fillRect(14,0,2,2,matrix.Color333(0,6,7));
  matrix.fillRect(14,2,3,2,matrix.Color333(0,6,7));
  matrix.fillRect(15,4,2,6,matrix.Color333(0,6,7));
  matrix.drawLine(17,7,17,9, matrix.Color333(0,6,7));
  matrix.fillRect(16,10,2,5,matrix.Color333(0,6,7));
  matrix.drawLine(18,11,18,15, matrix.Color333(0,6,7));
  matrix.drawPixel(17, 15, matrix.Color333(0, 6, 7));
  matrix.drawPixel(19, 14, matrix.Color333(0, 6, 7));
  matrix.drawPixel(19, 15, matrix.Color333(0, 6, 7));

  //C6
  matrix.drawPixel(16, 0, matrix.Color333(7, 5, 1));
  matrix.drawPixel(17, 0, matrix.Color333(7, 5, 1));
  matrix.drawPixel(16, 1, matrix.Color333(7, 5, 1));
  matrix.fillRect(17,1,2,4,matrix.Color333(7,5,1));
  matrix.fillRect(17,5,3,2,matrix.Color333(7,5,1));
  matrix.fillRect(18,7,2,2,matrix.Color333(7,5,1));
  matrix.fillRect(18,9,3,2,matrix.Color333(7,5,1));
  matrix.drawPixel(19, 11, matrix.Color333(7,5,1));
  matrix.drawPixel(20, 11, matrix.Color333(7,5,1));
  matrix.fillRect(19,12,3,2,matrix.Color333(7,5,1));
  matrix.fillRect(20,14,3,2,matrix.Color333(7,5,1));

  //C7
  matrix.drawPixel(18, 0, matrix.Color333(7,7,0));
  matrix.drawPixel(19, 0, matrix.Color333(7,7,0));
  matrix.fillRect(19,1,2,4,matrix.Color333(7,7,0));
  matrix.fillRect(20,5,2,4,matrix.Color333(7,7,0));
  matrix.drawPixel(22, 8, matrix.Color333(7,7,0));
  matrix.fillRect(21,9,2,3,matrix.Color333(7,7,0));
  matrix.drawPixel(23, 10, matrix.Color333(7,7,0));
  matrix.drawPixel(23, 11, matrix.Color333(7,7,0));
  matrix.fillRect(22,12,3,2,matrix.Color333(7,7,0));
  matrix.fillRect(23,14,3,2,matrix.Color333(7,7,0));

  //C8
  matrix.drawPixel(20, 0, matrix.Color333(6,3,1));
  matrix.drawLine(21,0,21,4, matrix.Color333(6,3,1));
  matrix.drawLine(22,3,22,7, matrix.Color333(6,3,1));
  matrix.drawLine(23,6,23,9, matrix.Color333(6,3,1));
  matrix.drawLine(24,9,24,11, matrix.Color333(6,3,1));
  matrix.drawLine(25,11,25,13, matrix.Color333(6,3,1));
  matrix.drawLine(26,13,26,15, matrix.Color333(6,3,1));
  matrix.drawLine(27,14,27,15, matrix.Color333(6,3,1));
  matrix.drawPixel(28, 15, matrix.Color333(6,3,1));

  //C9
  matrix.drawPixel(22, 2, matrix.Color333(7,2,0));
  matrix.fillRect(22,0,2,2,matrix.Color333(7,2,0));
  matrix.fillRect(23,2,2,4,matrix.Color333(7,2,0));
  matrix.drawPixel(25, 5, matrix.Color333(7,2,0));
  matrix.fillRect(24,6,2,3,matrix.Color333(7,2,0));
  matrix.drawPixel(26, 8, matrix.Color333(7,2,0));
  matrix.fillRect(25,9,2,2,matrix.Color333(7,2,0));
  matrix.fillRect(25,9,2,2,matrix.Color333(7,2,0));
  matrix.drawPixel(27, 10, matrix.Color333(7,2,0));
  matrix.fillRect(26,11,3,2,matrix.Color333(7,2,0));
  matrix.drawLine(27,13,29,13, matrix.Color333(7,2,0));
  matrix.drawLine(28,14,30,14, matrix.Color333(7,2,0));
  matrix.drawLine(29,15,31,15, matrix.Color333(7,2,0));

  //C10
  matrix.fillRect(24,0,8,2,matrix.Color333(7,0,0));
  matrix.fillRect(25,2,7,3,matrix.Color333(7,0,0));
  matrix.fillRect(26,5,6,3,matrix.Color333(7,0,0));
  matrix.fillRect(27,8,5,2,matrix.Color333(7,0,0));
  matrix.drawLine(28,10,31,10, matrix.Color333(7,0,0));
  matrix.fillRect(29,11,3,2,matrix.Color333(7,0,0));
  matrix.drawLine(30,13,31,13, matrix.Color333(7,0,0));
  matrix.drawPixel(31, 14, matrix.Color333(7,0,0));

}

void display_position(char t0, char t1, char t2, char h1, char h2){
  int x, y, t, h;
  plot_grad();
  t= get_temp(t0, t1, t2);
  h = get_hum(h1, h2);
  
  //temp
  if (t <= -18){
    x = 0;
  }
  else if (t > -18 && t <= -16){
    x = 1;
  }
  else if (t > -16 && t <= -14){
    x = 2;
  }
  else if (t > -14 && t <= -12){
    x = 3;
  }
  else if (t > -12 && t <= -10){
    x = 4;
  }
  else if (t > -10 && t <= -8){
    x = 5;
  } 
  else if (t > -8 && t <= -6){
    x = 6;
  } 
  else if (t > -6 && t <= -4){
    x = 7;
  }
  else if (t > -4 && t <= -2){
    x = 8;
  }
  else if (t > -2 && t <= 0){
    x = 9;
  }
  else if (t > 0 && t <= 2){
    x = 10;
  }
  else if (t > 2 && t <= 4){
    x = 11;
  } 
  else if (t > 4 && t <= 6){
    x = 12;
  } 
  else if (t > 6 && t <= 8){
    x = 13;
  }
  else if (t > 8 && t <= 10){
    x = 14;
  }
  else if (t > 10 && t <= 12){
    x = 15;
  }
  else if (t > 12 && t <= 14){
    x = 16;
  }
  else if (t > 14 && t <= 16){
    x = 17;
  } 
  else if (t > 16&& t <= 18){
    x = 18;
  } 
  else if (t > 18 && t <= 20){
    x = 19;
  }
  else if (t > 20 && t <= 22){
    x = 20;
  }
  else if (t > 22 && t <= 24){
    x = 21;
  }
  else if (t > 24 && t <= 26){
    x = 22;
  }
  else if (t > 26 && t <= 28){
    x = 23;
  } 
  else if (t > 28 && t <= 30){
    x = 24;
  } 
  else if (t > 30 && t <= 32){
    x = 25;
  }
  else if (t > 32 && t <= 34){
    x = 26;
  } 
  else if (t > 34&& t <= 36){
    x = 27;
  } 
  else if (t > 36 && t <= 38){
    x = 28;
  }
  else if (t > 38 && t <= 40){
    x = 29;
  }
  else if (t > 40 && t <= 42){
    x = 30;
  }
  else if (t > 42){
    x = 31;
  }

//Humidity
  if (h >= 91){
    y = 0;
  }
  else if (h > 85 && h <= 91){
    y = 1;
  }
  else if (h > 79 && h <= 85){
    y = 2;
  }
  else if (h > 73 && h <= 79){
    y = 3;
  }
  else if (h > 67 && h <= 73){
    y = 4;
  }
  else if (h> 61 && h <= 67){
    y = 5;
  } 
  else if (h > 55 && h <= 61){
    y = 6;
  } 
  else if (h > 49 && h <= 55){
    y = 7;
  }
  else if (h > 43 && h <= 49){
    y = 8;
  }
  else if (h > 37 && h <= 43){
    y = 9;
  }
  else if (h > 31 && h <= 37){
    y = 10;
  }
  else if (h > 25 && h <= 31){
    y = 11;
  } 
  else if (h > 19 && h <= 25){
    y = 12;
  } 
  else if (h > 13 && h <=19){
    y = 13;
  }
  else if ( h > 7 && h <= 13){
    y = 14;
  }
  else if (h <= 7){
    y = 15;
  }
 
  matrix.fillRect(x,y,2,2,matrix.Color333(0,0,0));
  delay(1500);
  matrix.fillRect(x,y,2,2,matrix.Color333(7,7,7));
  delay(2500);
}
