#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <ST7735_Renderer.h>

ST7735_Renderer::ST7735_Renderer(Adafruit_ST7735* display)
{
    _display = display;
};

void ST7735_Renderer::Init(vector<MenuItem>* menuItems)
{
    // perform initial layout - work out item sizes, 
    // number of pages & scrollbar requirement

    _menuItems = menuItems;
    _pageCount = menuItems->size() / 6; // 16 px height = 6 items per page
};

ItemBounds ST7735_Renderer::RenderItem(unsigned char index)
{
    if(abs(index / 6) != _currentPage)
    {
        return ItemBounds::Empty;
    }
};