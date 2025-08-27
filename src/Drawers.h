#pragma once

#include <TFT_eSPI.h>

extern TFT_eSPI tft; 

void pp_drawText(String content, int16_t x, int16_t y,
    uint16_t color = TFT_WHITE,
    uint8_t size = 1,
    uint16_t bg_color = TFT_BLACK,
    uint8_t datum = TL_DATUM)
{
    tft.setTextSize(size);
    tft.setTextColor(color, bg_color);
    tft.setTextDatum(datum);
    tft.drawString(content, x, y);
}

void pp_drawBox(int16_t x, int16_t y, int16_t width, int16_t height, 
    uint16_t bg_color = TFT_BLACK, 
    uint16_t stroke_color = TFT_WHITE, 
    uint8_t radius = 5, 
    bool stroke = true) 
{
    tft.fillRoundRect(x, y, width, height, radius, bg_color);
    if(stroke){
        tft.drawRoundRect(x, y, width, height, radius, stroke_color);
    }
}