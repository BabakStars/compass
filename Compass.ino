#include <Wire.h>
#define SCR_WD   240
#define SCR_HT   240
#include <SPI.h>
// QMC5883L Compass Library
#include <QMC5883LCompass.h>
#define GREEN 0x07E0
#define RED 0xF800
#define BLACK 0x0000
#define B 0x001F

#if (__STM32F1__) // bluepill
#define TFT_DC  PA1
#define TFT_RST PA0
//#include <Arduino_ST7789_STM.h>
#else
#define TFT_DC  7
#define TFT_RST 8
#include <Arduino_ST7789_Fast.h>
//#include <Arduino_ST7789.h>
#endif

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);

QMC5883LCompass compass;

int head;

void setup() {
  tft.begin();
  tft.fillScreen(BLACK);
  // Initialize the serial port.
  Serial.begin(9600);
  // Initialize I2C.
  Wire.begin();
  // Initialize the Compass.
  compass.init();
}

void loop() {
  int x, y, z;

  // Read compass values
  compass.read();

  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();



  Serial.print("X: ");
  Serial.print(x);
  
  Serial.print("  Y: ");
  Serial.print(y);
  
  //Serial.print("  Z: ");
  //Serial.print(z);

  //Serial.print("  H: ");
  //Serial.print((y+x)/2);

  if(x < 0)
  {
    head = map(y,-1233,900,180,0);
  }
  else
  {
    head = map(y,-1233,900,181,359);
  }
   Serial.print("  H: ");
   Serial.print(head);
   Serial.println();

    int X = sin(radians(359-head)) * 119;
    int Y = cos(radians(359-head)) * 119;

    tft.fillTriangle(120+(20*cos(radians(359-head))),120+(20*sin(radians(359-head))),120-X,120+Y,120-(20*cos(radians(359-head))),120-(20*sin(radians(359-head))),RED);
    tft.fillTriangle(120+(20*cos(radians(359-head))),120+(20*sin(radians(359-head))),120+X,120-Y,120-(20*cos(radians(359-head))),120-(20*sin(radians(359-head))),B);
    //tft.fillTriangle(140,120,120,10,100,120,RED);
    //tft.fillTriangle(140,120,120,230,100,120,B);

  delay(100);
    //tft.fillTriangle(120+(20*sin(radians(360-head))),120-(5*cos(radians(head))),X+(25*cos(radians(head))),Y+(25*sin(radians(head))),120-(5*sin(radians(head))),120+(5*cos(radians(head))),BLACK);
  tft.fillTriangle(120+(20*cos(radians(359-head))),120+(20*sin(radians(359-head))),120-X,120+Y,120-(20*cos(radians(359-head))),120-(20*sin(radians(359-head))),BLACK);
  tft.fillTriangle(120+(20*cos(radians(359-head))),120+(20*sin(radians(359-head))),120+X,120-Y,120-(20*cos(radians(359-head))),120-(20*sin(radians(359-head))),BLACK);
}
