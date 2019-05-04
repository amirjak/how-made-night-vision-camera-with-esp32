#include "OV7670.h"
#include <SPI.h>
#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_SSD1331.h>      // Hardware-specific library
#include <Adafruit_ImageReader.h> // Image-reading functions

// If we are using the hardware SPI interface, these are the pins (for future ref)
#define sclk 14
#define mosi 13
#define cs   15
#define rst  2
#define dc   12

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

// to draw images from the SD card, we will share the hardware SPI interface
Adafruit_SSD1331 tft = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);



const int SIOD = 21; //SDA
const int SIOC = 22; //SCL

const int VSYNC = 18;
const int HREF = 34;

const int XCLK = 32;
const int PCLK = 33;

const int D0 = 26;
const int D1 = 27;
const int D2 = 4;
const int D3 = 19;
const int D4 = 5;
const int D5 = 23;
const int D6 = 35;
const int D7 = 25;


OV7670 *camera;

void setup()
{
  Serial.begin(115200);
  camera = new OV7670(OV7670::Mode::QQQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  tft.begin();
  tft.fillScreen(0);
  // tft.setRotation(2);
}

void displayRGB565(unsigned char * frame, int xres, int yres)
{
  tft.setAddrWindow(0, 0, xres , yres );//8//2
  int i = 0;
  for (int y = 0; y < yres; y++)
    for (int x = 0; x < xres; x++)
    {
      i = (y * xres + x) << 1;
      tft.pushColor((frame[i] | (frame[i + 1] << 8)));
    }
}

void loop()
{
  camera->oneFrame();
  displayRGB565(camera->frame, camera->xres, camera->yres);
}
