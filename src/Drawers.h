#pragma once

#include <TFT_eSPI.h>

extern TFT_eSPI tft; 

void pp_drawText(String content, int16_t x, int16_t y,
    uint16_t color = TFT_WHITE,
    uint8_t size = 1,
    uint16_t bg_color = TFT_BLACK,
    uint8_t datum = TL_DATUM);

void pp_drawBox(int16_t x, int16_t y, int16_t width, int16_t height, 
    uint16_t bg_color = TFT_BLACK, 
    uint16_t stroke_color = TFT_WHITE, 
    uint8_t radius = 5, 
    bool stroke = true);