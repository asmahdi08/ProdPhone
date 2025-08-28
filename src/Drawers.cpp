#include "Drawers.h"

void pp_drawText(String content, int16_t x, int16_t y,
    uint16_t color,
    uint8_t size,
    uint16_t bg_color,
    uint8_t datum)
{
    tft.setTextSize(size);
    tft.setTextColor(color, bg_color);
    tft.setTextDatum(datum);
    tft.drawString(content, x, y);
}

void pp_drawBox(int16_t x, int16_t y, int16_t width, int16_t height, 
    uint16_t bg_color, 
    uint16_t stroke_color, 
    uint8_t radius, 
    bool stroke) 
{
    tft.fillRoundRect(x, y, width, height, radius, bg_color);
    if(stroke){
        tft.drawRoundRect(x, y, width, height, radius, stroke_color);
    }
}
