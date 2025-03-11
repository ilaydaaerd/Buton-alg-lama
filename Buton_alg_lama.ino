#include <Adafruit_GFX.h> 
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX_Button.h> 

MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F

#define YP A3  
#define XM A2  
#define YM 9   
#define XP 8   

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button myButton;

void setup() {
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);  
    tft.fillScreen(BLACK);

    
    myButton.initButtonUL(&tft, 60, 100, 200, 60, WHITE, BLUE, WHITE, "Click Me", 2);
    myButton.drawButton(false); // Butonu çiz
}

void loop() {
    TSPoint p = ts.getPoint();
    
    if (p.z > 200) { 
        int x = map(p.x, 100, 920, 0, 480);
        int y = map(p.y, 120, 900, 0, 320);
        
        if (myButton.contains(x, y)) { 
            myButton.press(true);
        } else {
            myButton.press(false);
        }

        if (myButton.justPressed()) {
            myButton.drawButton(true); 
            tft.fillRect(100, 200, 200, 30, BLACK); 
            tft.setCursor(130, 210);
            tft.setTextColor(GREEN);
            tft.setTextSize(2);
            tft.print("Dokundun!");
        }

        if (myButton.justReleased()) {
            myButton.drawButton(false); 
        }
    }
}
