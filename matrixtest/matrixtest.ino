// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <SPI.h>
#include <boards.h>
#include <EEPROM.h>
#include <RBL_nRF8001.h>

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

/* Animations/Frames start */

const uint16_t eyes_blink_color = matrix.Color(255,255,255);

const uint16_t eyes_blink_color_dark = matrix.Color(150,150,150);

const uint16_t eyes_heart_color = matrix.Color(255,0,216);

const uint16_t cmd_color = matrix.Color(255,255,255);

const uint16_t apple_color = matrix.Color(255,255,255);

const uint16_t skin_color = matrix.Color(237,195,150);

const uint16_t blushing_color = matrix.Color(255,112,233);

boolean scanner_direction = true;

uint16_t colorBouncer = 0;

/* Animations/Frames End */

void setup() {
  Serial.begin(57600);
  matrix.begin();
  matrix.setBrightness(100);
  ble_set_name("H");
  ble_begin();
}

int view = 0;

/*
 * Views : 
 * 0 - Eyes blinking
 * 1 - Heart Throb
 * 2 - Scanner
 * 3 - CMD C:/
 */
int rate = 0;
int fps = 1;
int switchCount = 20;
int x = matrix.width();
short colora = 0;
short colorb = 0;
short colorc = 0;

void generateColor() {
  colora = random(0,255);
  colorb = random(0,255);
  colorc = random(0,255);
}

char partyText[] = "PLACEHOLDERWORDHERE"; 

void generateParty() {
  switch(random(0,4)) {
    case 0:
      strcpy(partyText, "PARTY");
    break;
    case 1:
      strcpy(partyText, "DANCE");
    break;
    case 2:
      strcpy(partyText, "RAGE!");
    break;
    case 3:
      strcpy(partyText, "ELECTRIC");
    break;
    case 4:
      strcpy(partyText, "WERK ME");
    break;
  }
}

void loop() {
  Serial.print("Loop");

  byte cmd;
  cmd = ble_read();
  Serial.write(cmd);
  
  // Parse data here
  switch (cmd)
  {
    case 'V': // query protocol version
      {
        //byte buf[] = {'V', 0x00, 0x00, 0x01};
        //ble_write_string(buf, 4);
        view = 1;
        fps = 0;  
      }
      break;

    case 'F':
      matrix.setBrightness(100);
      
      fps = 0;
      
      switch(ble_read()) {
        case 'A': view = 0; break;
        case 'B': view = 1; break;
        case 'C': view = 2; break;
        case 'D': view = 3; break;
        case 'E': view = 4; break;
        case 'F': view = 5; break;
        case 'G': view = 6; break;
        case 'H': view = 7; break;
        case 'I': view = 8; generateParty(); break;
        case 'J': view = 9; break;
        case 'K': view = 10; break;
        case 'L': fps = 1; scanner_direction = false; view = 11; break;
        case 'M': view = 12; break;
        case 'N': view = 13; break;
      }
    break;

  }

  matrix.fillScreen(0);
  //matrix.setCursor(5, 0);
  //matrix.print(rate);
  //matrix.setTextColor(matrix.Color(255,255,255));

  switch(view) {
    case 0:
      rate = 200;
      if(fps <= 35) {
        matrix.drawPixel(10,1, eyes_blink_color);matrix.drawPixel(11,1, eyes_blink_color);matrix.drawPixel(20,1, eyes_blink_color);matrix.drawPixel(21,1, eyes_blink_color);matrix.drawPixel(9,2, eyes_blink_color);matrix.drawPixel(12,2, eyes_blink_color);matrix.drawPixel(19,2, eyes_blink_color);matrix.drawPixel(22,2, eyes_blink_color);matrix.drawPixel(9,3, eyes_blink_color);matrix.drawPixel(12,3, eyes_blink_color);matrix.drawPixel(19,3, eyes_blink_color);matrix.drawPixel(22,3, eyes_blink_color);matrix.drawPixel(9,4, eyes_blink_color);matrix.drawPixel(12,4, eyes_blink_color);matrix.drawPixel(19,4, eyes_blink_color);matrix.drawPixel(22,4, eyes_blink_color);matrix.drawPixel(10,5, eyes_blink_color);matrix.drawPixel(11,5, eyes_blink_color);matrix.drawPixel(20,5, eyes_blink_color);matrix.drawPixel(21,5, eyes_blink_color);
      }else if(fps == 36) {
        matrix.drawPixel(9,4, eyes_blink_color);matrix.drawPixel(10,4, eyes_blink_color);matrix.drawPixel(11,4, eyes_blink_color);matrix.drawPixel(12,4, eyes_blink_color);matrix.drawPixel(19,4, eyes_blink_color);matrix.drawPixel(20,4, eyes_blink_color);matrix.drawPixel(21,4, eyes_blink_color);matrix.drawPixel(22,4, eyes_blink_color);
        fps = 0;
      }

      fps++;
    break;

    case 1:
      rate = 200;
      if(fps < 2) {
        matrix.drawPixel(9,1, eyes_heart_color);matrix.drawPixel(10,1, eyes_heart_color);matrix.drawPixel(12,1, eyes_heart_color);matrix.drawPixel(13,1, eyes_heart_color);matrix.drawPixel(18,1, eyes_heart_color);matrix.drawPixel(19,1, eyes_heart_color);matrix.drawPixel(21,1, eyes_heart_color);matrix.drawPixel(22,1, eyes_heart_color);matrix.drawPixel(8,2, eyes_heart_color);matrix.drawPixel(9,2, eyes_heart_color);matrix.drawPixel(10,2, eyes_heart_color);matrix.drawPixel(11,2, eyes_heart_color);matrix.drawPixel(12,2, eyes_heart_color);matrix.drawPixel(13,2, eyes_heart_color);matrix.drawPixel(14,2, eyes_heart_color);matrix.drawPixel(17,2, eyes_heart_color);matrix.drawPixel(18,2, eyes_heart_color);matrix.drawPixel(19,2, eyes_heart_color);matrix.drawPixel(20,2, eyes_heart_color);matrix.drawPixel(21,2, eyes_heart_color);matrix.drawPixel(22,2, eyes_heart_color);matrix.drawPixel(23,2, eyes_heart_color);matrix.drawPixel(8,3, eyes_heart_color);matrix.drawPixel(9,3, eyes_heart_color);matrix.drawPixel(10,3, eyes_heart_color);matrix.drawPixel(11,3, eyes_heart_color);matrix.drawPixel(12,3, eyes_heart_color);matrix.drawPixel(13,3, eyes_heart_color);matrix.drawPixel(14,3, eyes_heart_color);matrix.drawPixel(17,3, eyes_heart_color);matrix.drawPixel(18,3, eyes_heart_color);matrix.drawPixel(19,3, eyes_heart_color);matrix.drawPixel(20,3, eyes_heart_color);matrix.drawPixel(21,3, eyes_heart_color);matrix.drawPixel(22,3, eyes_heart_color);matrix.drawPixel(23,3, eyes_heart_color);matrix.drawPixel(9,4, eyes_heart_color);matrix.drawPixel(10,4, eyes_heart_color);matrix.drawPixel(11,4, eyes_heart_color);matrix.drawPixel(12,4, eyes_heart_color);matrix.drawPixel(13,4, eyes_heart_color);matrix.drawPixel(18,4, eyes_heart_color);matrix.drawPixel(19,4, eyes_heart_color);matrix.drawPixel(20,4, eyes_heart_color);matrix.drawPixel(21,4, eyes_heart_color);matrix.drawPixel(22,4, eyes_heart_color);matrix.drawPixel(10,5, eyes_heart_color);matrix.drawPixel(11,5, eyes_heart_color);matrix.drawPixel(12,5, eyes_heart_color);matrix.drawPixel(19,5, eyes_heart_color);matrix.drawPixel(20,5, eyes_heart_color);matrix.drawPixel(21,5, eyes_heart_color);matrix.drawPixel(11,6, eyes_heart_color);matrix.drawPixel(20,6, eyes_heart_color);
      }else if(fps > 1) {
        matrix.drawPixel(9,0, eyes_heart_color);matrix.drawPixel(10,0, eyes_heart_color);matrix.drawPixel(12,0, eyes_heart_color);matrix.drawPixel(13,0, eyes_heart_color);matrix.drawPixel(18,0, eyes_heart_color);matrix.drawPixel(19,0, eyes_heart_color);matrix.drawPixel(21,0, eyes_heart_color);matrix.drawPixel(22,0, eyes_heart_color);matrix.drawPixel(8,1, eyes_heart_color);matrix.drawPixel(11,1, eyes_heart_color);matrix.drawPixel(14,1, eyes_heart_color);matrix.drawPixel(17,1, eyes_heart_color);matrix.drawPixel(20,1, eyes_heart_color);matrix.drawPixel(23,1, eyes_heart_color);matrix.drawPixel(7,2, eyes_heart_color);matrix.drawPixel(9,2, eyes_heart_color);matrix.drawPixel(10,2, eyes_heart_color);matrix.drawPixel(11,2, eyes_heart_color);matrix.drawPixel(12,2, eyes_heart_color);matrix.drawPixel(13,2, eyes_heart_color);matrix.drawPixel(15,2, eyes_heart_color);matrix.drawPixel(16,2, eyes_heart_color);matrix.drawPixel(18,2, eyes_heart_color);matrix.drawPixel(19,2, eyes_heart_color);matrix.drawPixel(20,2, eyes_heart_color);matrix.drawPixel(21,2, eyes_heart_color);matrix.drawPixel(22,2, eyes_heart_color);matrix.drawPixel(24,2, eyes_heart_color);matrix.drawPixel(7,3, eyes_heart_color);matrix.drawPixel(9,3, eyes_heart_color);matrix.drawPixel(10,3, eyes_heart_color);matrix.drawPixel(11,3, eyes_heart_color);matrix.drawPixel(12,3, eyes_heart_color);matrix.drawPixel(13,3, eyes_heart_color);matrix.drawPixel(15,3, eyes_heart_color);matrix.drawPixel(16,3, eyes_heart_color);matrix.drawPixel(18,3, eyes_heart_color);matrix.drawPixel(19,3, eyes_heart_color);matrix.drawPixel(20,3, eyes_heart_color);matrix.drawPixel(21,3, eyes_heart_color);matrix.drawPixel(22,3, eyes_heart_color);matrix.drawPixel(24,3, eyes_heart_color);matrix.drawPixel(8,4, eyes_heart_color);matrix.drawPixel(10,4, eyes_heart_color);matrix.drawPixel(11,4, eyes_heart_color);matrix.drawPixel(12,4, eyes_heart_color);matrix.drawPixel(14,4, eyes_heart_color);matrix.drawPixel(17,4, eyes_heart_color);matrix.drawPixel(19,4, eyes_heart_color);matrix.drawPixel(20,4, eyes_heart_color);matrix.drawPixel(21,4, eyes_heart_color);matrix.drawPixel(23,4, eyes_heart_color);matrix.drawPixel(9,5, eyes_heart_color);matrix.drawPixel(11,5, eyes_heart_color);matrix.drawPixel(13,5, eyes_heart_color);matrix.drawPixel(18,5, eyes_heart_color);matrix.drawPixel(20,5, eyes_heart_color);matrix.drawPixel(22,5, eyes_heart_color);matrix.drawPixel(10,6, eyes_heart_color);matrix.drawPixel(12,6, eyes_heart_color);matrix.drawPixel(19,6, eyes_heart_color);matrix.drawPixel(21,6, eyes_heart_color);matrix.drawPixel(11,7, eyes_heart_color);matrix.drawPixel(20,7, eyes_heart_color);
        if(fps == 2) {
          fps = 0;
        }
      }

      fps++;
    break;

    case 2:
      rate = 20;
      if(scanner_direction) {
        for(int i = 0; i < 8; i++) {
          matrix.drawPixel(fps, i, matrix.Color(255,255,255));
        }
      }else{
        for(int i = 0; i < 8; i++) {
          matrix.drawPixel(32-fps, i, matrix.Color(255,255,255));
        }
      }

      if(fps == 32) {
        fps = 0;
        if(scanner_direction == true) { scanner_direction = false; } else { scanner_direction = true; }
      }

      fps++;
    break;

    case 3:
      rate = 190;
      
      matrix.drawPixel(8,1, cmd_color);matrix.drawPixel(9,1, cmd_color);matrix.drawPixel(10,1, cmd_color);matrix.drawPixel(15,1, cmd_color);matrix.drawPixel(7,2, cmd_color);matrix.drawPixel(11,2, cmd_color);matrix.drawPixel(15,2, cmd_color);matrix.drawPixel(7,3, cmd_color);matrix.drawPixel(13,3, cmd_color);matrix.drawPixel(16,3, cmd_color);matrix.drawPixel(7,4, cmd_color);matrix.drawPixel(16,4, cmd_color);matrix.drawPixel(7,5, cmd_color);matrix.drawPixel(11,5, cmd_color);matrix.drawPixel(13,5, cmd_color);matrix.drawPixel(17,5, cmd_color);matrix.drawPixel(8,6, cmd_color);matrix.drawPixel(9,6, cmd_color);matrix.drawPixel(10,6, cmd_color);matrix.drawPixel(17,6, cmd_color);
        
      if(fps > 1) {

        matrix.drawPixel(19, 6, matrix.Color(255,255,255));
        matrix.drawPixel(20, 6, matrix.Color(255,255,255));
        matrix.drawPixel(21, 6, matrix.Color(255,255,255));
        matrix.drawPixel(22, 6, matrix.Color(255,255,255));
        matrix.drawPixel(23, 6, matrix.Color(255,255,255));

        if(fps == 2) {
          fps = 0;
        }
      }

      fps++;
    break;

    case 4:
      rate = 200;

      matrix.drawPixel(17,0, apple_color);matrix.drawPixel(16,1, apple_color);matrix.drawPixel(14,2, apple_color);matrix.drawPixel(15,2, apple_color);matrix.drawPixel(17,2, apple_color);matrix.drawPixel(18,2, apple_color);matrix.drawPixel(13,3, apple_color);matrix.drawPixel(14,3, apple_color);matrix.drawPixel(15,3, apple_color);matrix.drawPixel(16,3, apple_color);matrix.drawPixel(17,3, apple_color);matrix.drawPixel(18,3, apple_color);matrix.drawPixel(19,3, apple_color);matrix.drawPixel(13,4, apple_color);matrix.drawPixel(14,4, apple_color);matrix.drawPixel(15,4, apple_color);matrix.drawPixel(16,4, apple_color);matrix.drawPixel(17,4, apple_color);matrix.drawPixel(18,4, apple_color);matrix.drawPixel(13,5, apple_color);matrix.drawPixel(14,5, apple_color);matrix.drawPixel(15,5, apple_color);matrix.drawPixel(16,5, apple_color);matrix.drawPixel(17,5, apple_color);matrix.drawPixel(18,5, apple_color);matrix.drawPixel(13,6, apple_color);matrix.drawPixel(14,6, apple_color);matrix.drawPixel(15,6, apple_color);matrix.drawPixel(16,6, apple_color);matrix.drawPixel(17,6, apple_color);matrix.drawPixel(18,6, apple_color);matrix.drawPixel(19,6, apple_color);matrix.drawPixel(14,7, apple_color);matrix.drawPixel(15,7, apple_color);matrix.drawPixel(17,7, apple_color);matrix.drawPixel(18,7, apple_color);
      if(fps == 20) {
        //view = 0;
        //fps = 30;
      }

      fps++;
    break;

    case 5:
      rate = 70;

      if (fps >= 1 && fps < 8) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 8) {
        matrix.drawPixel(fps, 3, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 9) {
        matrix.drawPixel(fps, 2, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 3, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 10) {
        matrix.drawPixel(fps, 1, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 2, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 3, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 11) {
        matrix.drawPixel(fps, 0, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 1, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 2, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 3, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 12) {
        matrix.drawPixel(fps, 1, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 0, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 1, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 2, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 3, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 13) {
        matrix.drawPixel(fps, 2, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 1, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 0, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 1, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 2, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 3, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 14) {
        matrix.drawPixel(fps, 3, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 2, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 1, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 0, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 1, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 2, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 3, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 15) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 3, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 2, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 1, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 0, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 1, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 2, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 3, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 16) {
        matrix.drawPixel(fps, 5, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 3, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 2, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 1, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 0, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 1, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 2, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 17) {
        matrix.drawPixel(fps, 6, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 5, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 3, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 2, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 1, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 0, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 1, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 18) {
        matrix.drawPixel(fps, 7, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 6, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 5, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 3, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 2, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 1, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 0, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 19) {
        matrix.drawPixel(fps, 6, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 7, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 6, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 5, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 3, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 2, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 1, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 20) {
        matrix.drawPixel(fps, 5, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 6, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 7, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 6, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 5, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 3, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 2, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 21) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 5, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 6, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 7, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 6, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 5, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 3, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 22) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 5, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 6, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 7, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 6, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 5, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 23) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 5, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 6, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 7, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 6, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 5, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 24) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 5, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 6, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 7, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 6, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 25) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 5, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 6, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 7, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 26) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 5, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 6, matrix.Color(255/10,255/10,255/10));
      }else if(fps == 27) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 5, matrix.Color(255/10,255/10,255/10));
      }else if(fps > 27) {
        matrix.drawPixel(fps, 4, matrix.Color(255,255,255));
           matrix.drawPixel(fps-1, 4, matrix.Color(255/2,255/2,255/2));
            matrix.drawPixel(fps-2, 4, matrix.Color(255/3,255/3,255/3));
             matrix.drawPixel(fps-3, 4, matrix.Color(255/4,255/4,255/4));
              matrix.drawPixel(fps-4, 4, matrix.Color(255/5,255/5,255/5));
               matrix.drawPixel(fps-5, 4, matrix.Color(255/7,255/7,255/7));
                matrix.drawPixel(fps-6, 4, matrix.Color(255/9,255/9,255/9));
                 matrix.drawPixel(fps-7, 4, matrix.Color(255/10,255/10,255/10));
      }
      
      if(fps == 32) {
        fps = 0;
      }

      fps++;
    break;

    case 6:
      rate = 40;

      if(scanner_direction) {
        matrix.drawPixel(fps, 7, matrix.Color(255,0,0));
         matrix.drawPixel(fps-1, 7, matrix.Color(255/2,0,0));
          matrix.drawPixel(fps-2, 7, matrix.Color(255/3,0,0));
           matrix.drawPixel(fps-3, 7, matrix.Color(255/4,0,0));
            matrix.drawPixel(fps-4, 7, matrix.Color(255/5,0,0));
             matrix.drawPixel(fps-5, 7, matrix.Color(255/6,0,0));
              matrix.drawPixel(fps-6, 7, matrix.Color(255/7,0,0));
               matrix.drawPixel(fps-7, 7, matrix.Color(255/8,0,0));
               
        matrix.drawPixel(fps, 6, matrix.Color(255,0,0));
         matrix.drawPixel(fps-1, 6, matrix.Color(255/2,0,0));
          matrix.drawPixel(fps-2, 6, matrix.Color(255/3,0,0));
           matrix.drawPixel(fps-3, 6, matrix.Color(255/4,0,0));
            matrix.drawPixel(fps-4, 6, matrix.Color(255/5,0,0));
             matrix.drawPixel(fps-5, 6, matrix.Color(255/6,0,0));
              matrix.drawPixel(fps-6, 6, matrix.Color(255/7,0,0));
               matrix.drawPixel(fps-7, 6, matrix.Color(255/8,0,0));

        matrix.drawPixel(fps-1, 7, matrix.Color(255,0,0));
         matrix.drawPixel(fps-2, 7, matrix.Color(255/2,0,0));
          matrix.drawPixel(fps-3, 7, matrix.Color(255/3,0,0));
           matrix.drawPixel(fps-4, 7, matrix.Color(255/4,0,0));
            matrix.drawPixel(fps-5, 7, matrix.Color(255/5,0,0));
             matrix.drawPixel(fps-6, 7, matrix.Color(255/6,0,0));
              matrix.drawPixel(fps-7, 7, matrix.Color(255/7,0,0));
               matrix.drawPixel(fps-8, 7, matrix.Color(255/8,0,0));
               
        matrix.drawPixel(fps-1, 6, matrix.Color(255,0,0));
         matrix.drawPixel(fps-2, 6, matrix.Color(255/2,0,0));
          matrix.drawPixel(fps-3, 6, matrix.Color(255/3,0,0));
           matrix.drawPixel(fps-4, 6, matrix.Color(255/4,0,0));
            matrix.drawPixel(fps-5, 6, matrix.Color(255/5,0,0));
             matrix.drawPixel(fps-6, 6, matrix.Color(255/6,0,0));
              matrix.drawPixel(fps-7, 6, matrix.Color(255/7,0,0));
               matrix.drawPixel(fps-8, 6, matrix.Color(255/8,0,0));
      }else{
        matrix.drawPixel(32-fps-7, 7, matrix.Color(255,0,0));
         matrix.drawPixel(32-fps-6, 7, matrix.Color(255/2,0,0));
          matrix.drawPixel(32-fps-5, 7, matrix.Color(255/3,0,0));
           matrix.drawPixel(32-fps-4, 7, matrix.Color(255/4,0,0));
            matrix.drawPixel(32-fps-3, 7, matrix.Color(255/5,0,0));
             matrix.drawPixel(32-fps-2, 7, matrix.Color(255/6,0,0));
              matrix.drawPixel(32-fps-1, 7, matrix.Color(255/7,0,0));
               matrix.drawPixel(32-fps, 7, matrix.Color(255/8,0,0));

        matrix.drawPixel(32-fps-7, 6, matrix.Color(255,0,0));
         matrix.drawPixel(32-fps-6, 6, matrix.Color(255/2,0,0));
          matrix.drawPixel(32-fps-5, 6, matrix.Color(255/3,0,0));
           matrix.drawPixel(32-fps-4, 6, matrix.Color(255/4,0,0));
            matrix.drawPixel(32-fps-3, 6, matrix.Color(255/5,0,0));
             matrix.drawPixel(32-fps-2, 6, matrix.Color(255/6,0,0));
              matrix.drawPixel(32-fps-1, 6, matrix.Color(255/7,0,0));
               matrix.drawPixel(32-fps, 6, matrix.Color(255/8,0,0));

        matrix.drawPixel(32-fps-8, 7, matrix.Color(255,0,0));
         matrix.drawPixel(32-fps-7, 7, matrix.Color(255/2,0,0));
          matrix.drawPixel(32-fps-6, 7, matrix.Color(255/3,0,0));
           matrix.drawPixel(32-fps-5, 7, matrix.Color(255/4,0,0));
            matrix.drawPixel(32-fps-4, 7, matrix.Color(255/5,0,0));
             matrix.drawPixel(32-fps-3, 7, matrix.Color(255/6,0,0));
              matrix.drawPixel(32-fps-2, 7, matrix.Color(255/7,0,0));
               matrix.drawPixel(32-fps-1, 7, matrix.Color(255/8,0,0));

        matrix.drawPixel(32-fps-8, 6, matrix.Color(255,0,0));
         matrix.drawPixel(32-fps-7, 6, matrix.Color(255/2,0,0));
          matrix.drawPixel(32-fps-6, 6, matrix.Color(255/3,0,0));
           matrix.drawPixel(32-fps-5, 6, matrix.Color(255/4,0,0));
            matrix.drawPixel(32-fps-4, 6, matrix.Color(255/5,0,0));
             matrix.drawPixel(32-fps-3, 6, matrix.Color(255/6,0,0));
              matrix.drawPixel(32-fps-2, 6, matrix.Color(255/7,0,0));
               matrix.drawPixel(32-fps-1, 6, matrix.Color(255/8,0,0));
      }

      if(fps == 32) {
        fps = 0;
        if(scanner_direction == true) { scanner_direction = false; } else { scanner_direction = true; }
      }

      fps++;
    break;

    case 7:
      rate = 60;  
      
      matrix.setTextColor(matrix.Color(0, 168, 255));
      matrix.setCursor(x, 0);
      matrix.print(F("FASHION"));
      if(--x < -36) {
        x = matrix.width();
      }
    break;

    case 8:
      rate = 60;

      generateColor();
      matrix.setTextColor(matrix.Color(colora, colorb, colorc));
      matrix.setCursor(x, 0);
      matrix.print(partyText);
      if(--x < -36) {
        x = matrix.width();
        generateParty();
      }
    break;

    case 9:
      rate = 30;

      if(fps <= 30) {
        matrix.drawPixel(10,1, eyes_blink_color);
        matrix.drawPixel(11,1, eyes_blink_color);
        //matrix.drawPixel(20,1, eyes_blink_color);
        //matrix.drawPixel(21,1, eyes_blink_color);
        matrix.drawPixel(9,2, eyes_blink_color);
        matrix.drawPixel(12,2, eyes_blink_color);
        //matrix.drawPixel(19,2, eyes_blink_color);
        //matrix.drawPixel(22,2, eyes_blink_color);
        matrix.drawPixel(9,3, eyes_blink_color);
        matrix.drawPixel(12,3, eyes_blink_color);
        //matrix.drawPixel(19,3, eyes_blink_color);
        //matrix.drawPixel(22,3, eyes_blink_color);
        
        matrix.drawPixel(9,4, eyes_blink_color);
        matrix.drawPixel(12,4, eyes_blink_color);
        //matrix.drawPixel(19,4, eyes_blink_color);
        //matrix.drawPixel(22,4, eyes_blink_color);
        matrix.drawPixel(10,5, eyes_blink_color);
        matrix.drawPixel(11,5, eyes_blink_color);
        //matrix.drawPixel(20,5, eyes_blink_color);
        //matrix.drawPixel(21,5, eyes_blink_color);

        matrix.drawPixel(19,4, eyes_blink_color);
        matrix.drawPixel(20,4, eyes_blink_color);
        matrix.drawPixel(21,4, eyes_blink_color);
        matrix.drawPixel(22,4, eyes_blink_color);
        
      }

      fps++;

      if(fps == 30) {
        view = 0;
        fps = 0;
      }
    break;

    case 10:
      rate = 230;
      
      if(fps < 2) {
        matrix.drawPixel(22,0, eyes_blink_color);
        matrix.drawPixel(22,1, eyes_blink_color);
        matrix.drawPixel(22,2, eyes_blink_color);
        matrix.drawPixel(23,2, eyes_blink_color);
        matrix.drawPixel(24,2, eyes_blink_color);

        matrix.drawPixel(20,0, eyes_blink_color);
        matrix.drawPixel(20,1, eyes_blink_color);
        matrix.drawPixel(20,2, eyes_blink_color);
        matrix.drawPixel(19,2, eyes_blink_color);
        matrix.drawPixel(18,2, eyes_blink_color);

        matrix.drawPixel(22,6, eyes_blink_color);
        matrix.drawPixel(22,5, eyes_blink_color);
        matrix.drawPixel(22,4, eyes_blink_color);
        matrix.drawPixel(23,4, eyes_blink_color);
        matrix.drawPixel(24,4, eyes_blink_color);

        matrix.drawPixel(20,6, eyes_blink_color);
        matrix.drawPixel(20,5, eyes_blink_color);
        matrix.drawPixel(20,4, eyes_blink_color);
        matrix.drawPixel(19,4, eyes_blink_color);
        matrix.drawPixel(18,4, eyes_blink_color);
        
      }else if(fps > 1) {
        matrix.drawPixel(22,0, eyes_blink_color_dark);
        matrix.drawPixel(22,1, eyes_blink_color_dark);
        matrix.drawPixel(22,2, eyes_blink_color_dark);
        matrix.drawPixel(23,2, eyes_blink_color_dark);
        matrix.drawPixel(24,2, eyes_blink_color_dark);

        matrix.drawPixel(22,6, eyes_blink_color_dark);
        matrix.drawPixel(22,5, eyes_blink_color_dark);
        matrix.drawPixel(22,4, eyes_blink_color_dark);
        matrix.drawPixel(23,4, eyes_blink_color_dark);
        matrix.drawPixel(24,4, eyes_blink_color_dark);

        matrix.drawPixel(20,6, eyes_blink_color_dark);
        matrix.drawPixel(20,5, eyes_blink_color_dark);
        matrix.drawPixel(20,4, eyes_blink_color_dark);
        matrix.drawPixel(19,4, eyes_blink_color_dark);
        matrix.drawPixel(18,4, eyes_blink_color_dark);

        matrix.drawPixel(20,0, eyes_blink_color_dark);
        matrix.drawPixel(20,1, eyes_blink_color_dark);
        matrix.drawPixel(20,2, eyes_blink_color_dark);
        matrix.drawPixel(19,2, eyes_blink_color_dark);
        matrix.drawPixel(18,2, eyes_blink_color_dark);
        
        if(fps == 2) {
          fps = 0;
        }
      }

      fps++;
    break;

    case 11:
      rate = 120;

      if(scanner_direction) {
        fps--;
      }else{
        fps++;
      }

      //matrix.setBrightness(100);
      
      /*matrix.drawPixel(10, 0, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(11, 0, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(12, 0, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(13, 0, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(14, 0, matrix.Color(255/fps,255/fps,255/fps));

      matrix.drawPixel(13, 1, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(12, 2, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(11, 3, matrix.Color(255/fps,255/fps,255/fps));

      matrix.drawPixel(10, 4, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(11, 4, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(12, 4, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(13, 4, matrix.Color(255/fps,255/fps,255/fps));
      matrix.drawPixel(14, 4, matrix.Color(255/fps,255/fps,255/fps));*/

      
      matrix.drawPixel(10, 0, matrix.Color(255,255,255));
      matrix.drawPixel(11, 0, matrix.Color(255,255,255));
      matrix.drawPixel(12, 0, matrix.Color(255,255,255));
      matrix.drawPixel(13, 0, matrix.Color(255,255,255));
      matrix.drawPixel(14, 0, matrix.Color(255,255,255));

      matrix.drawPixel(13, 1, matrix.Color(255,255,255));
      matrix.drawPixel(12, 2, matrix.Color(255,255,255));
      matrix.drawPixel(11, 3, matrix.Color(255,255,255));

      matrix.drawPixel(10, 4, matrix.Color(255,255,255));
      matrix.drawPixel(11, 4, matrix.Color(255,255,255));
      matrix.drawPixel(12, 4, matrix.Color(255,255,255));
      matrix.drawPixel(13, 4, matrix.Color(255,255,255));
      matrix.drawPixel(14, 4, matrix.Color(255,255,255));

      matrix.setBrightness(fps);
      
      if(fps == 0 || fps == 50) {
        delay(100);
        if(scanner_direction) { scanner_direction = false; } else { scanner_direction = true; }
      }
    break;

    case 12:
      matrix.drawPixel(7,1, skin_color);matrix.drawPixel(9,1, skin_color);matrix.drawPixel(21,1, skin_color);matrix.drawPixel(22,1, skin_color);matrix.drawPixel(23,1, skin_color);matrix.drawPixel(8,2, skin_color);matrix.drawPixel(10,2, skin_color);matrix.drawPixel(11,2, skin_color);matrix.drawPixel(12,2, skin_color);matrix.drawPixel(13,2, skin_color);matrix.drawPixel(14,2, skin_color);matrix.drawPixel(15,2, skin_color);matrix.drawPixel(16,2, skin_color);matrix.drawPixel(17,2, skin_color);matrix.drawPixel(18,2, skin_color);matrix.drawPixel(19,2, skin_color);matrix.drawPixel(20,2, skin_color);matrix.drawPixel(24,2, skin_color);matrix.drawPixel(7,3, skin_color);matrix.drawPixel(9,3, skin_color);matrix.drawPixel(24,3, skin_color);matrix.drawPixel(9,4, skin_color);matrix.drawPixel(23,4, skin_color);matrix.drawPixel(24,4, skin_color);matrix.drawPixel(8,5, skin_color);matrix.drawPixel(11,5, skin_color);matrix.drawPixel(14,5, skin_color);matrix.drawPixel(15,5, skin_color);matrix.drawPixel(16,5, skin_color);matrix.drawPixel(17,5, skin_color);matrix.drawPixel(18,5, skin_color);matrix.drawPixel(19,5, skin_color);matrix.drawPixel(20,5, skin_color);matrix.drawPixel(24,5, skin_color);matrix.drawPixel(8,6, skin_color);matrix.drawPixel(11,6, skin_color);matrix.drawPixel(14,6, skin_color);matrix.drawPixel(21,6, skin_color);matrix.drawPixel(22,6, skin_color);matrix.drawPixel(23,6, skin_color);matrix.drawPixel(9,7, skin_color);matrix.drawPixel(10,7, skin_color);matrix.drawPixel(12,7, skin_color);matrix.drawPixel(13,7, skin_color);
    break;

    case 13:
      matrix.drawPixel(7,4, blushing_color);matrix.drawPixel(8,4, blushing_color);matrix.drawPixel(23,4, blushing_color);matrix.drawPixel(24,4, blushing_color);matrix.drawPixel(6,5, blushing_color);matrix.drawPixel(7,5, blushing_color);matrix.drawPixel(8,5, blushing_color);matrix.drawPixel(9,5, blushing_color);matrix.drawPixel(22,5, blushing_color);matrix.drawPixel(23,5, blushing_color);matrix.drawPixel(24,5, blushing_color);matrix.drawPixel(25,5, blushing_color);matrix.drawPixel(6,6, blushing_color);matrix.drawPixel(7,6, blushing_color);matrix.drawPixel(8,6, blushing_color);matrix.drawPixel(9,6, blushing_color);matrix.drawPixel(22,6, blushing_color);matrix.drawPixel(23,6, blushing_color);matrix.drawPixel(24,6, blushing_color);matrix.drawPixel(25,6, blushing_color);matrix.drawPixel(7,7, blushing_color);matrix.drawPixel(8,7, blushing_color);matrix.drawPixel(23,7, blushing_color);matrix.drawPixel(24,7, blushing_color);
      matrix.drawPixel(9,1, eyes_blink_color);matrix.drawPixel(10,1, eyes_blink_color);matrix.drawPixel(11,1, eyes_blink_color);matrix.drawPixel(12,1, eyes_blink_color);matrix.drawPixel(19,1, eyes_blink_color);matrix.drawPixel(20,1, eyes_blink_color);matrix.drawPixel(21,1, eyes_blink_color);matrix.drawPixel(22,1, eyes_blink_color);matrix.drawPixel(8,2, eyes_blink_color);matrix.drawPixel(13,2, eyes_blink_color);matrix.drawPixel(18,2, eyes_blink_color);matrix.drawPixel(23,2, eyes_blink_color);
    break;
  }

  switchCount--;
  
  if(switchCount <= 0) {
    if(view == 11) {
      //view = 0;
      switchCount = 60;
      //fps = 1;
    }else{
      //view++;
      switchCount = 60;
      //fps = 1;

      /*switch(view) {
      case 0: fps = 0; break;
      case 1: fps = 0; break;
      case 2: fps = 0; switchCount = 120; break;
      case 3: fps = 0; switchCount = 120; break;
      case 4: fps = 0; break;
      case 5: fps = 0; break;
      case 6: fps = 0; switchCount = 190; break;
      case 7: fps = 0; switchCount = 190; break;
      case 8: fps = 0; switchCount = 220; generateParty(); break;
      case 9: fps = 0; switchCount = 500; break;
      case 10: fps = 0; break;
      case 11: fps = 1; scanner_direction = false; break;
    }*/
    }
  }
  
  matrix.show();
  ble_do_events();
  delay(rate);
}
