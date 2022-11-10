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

    unsigned char itemWidth = _pageCount > 1 ? 150 : 160;

    ItemBounds bounds = { itemWidth, 16, 0, 16 * (index - (_currentPage * 6)) };

    MenuItem item = _menuItems->at(index);

    _display->setTextSize(1); // 6x8

    // draw the box
    _display->fillRect(bounds.Left, bounds.Top, bounds.Width, bounds.Height, item.IsSelected ? ST7735_WHITE : ST7735_BLACK);
    _display->drawRect(bounds.Left, bounds.Top, bounds.Width, bounds.Height, ST7735_WHITE);
    

    // measure the text - if longer than the allotted space, remove characters until it fits
    String itemText = item.Text;

    int16_t measuredX = 0, measuredY = 0;
    uint16_t measuredWidth = 0, measuredHeight = 0;

    int16_t x = 4, y = 4;

    bool modified = false;
    _display->getTextBounds(itemText, x, y, &measuredX, &measuredY, &measuredWidth, &measuredHeight);
    while (measuredWidth > itemWidth - 8)
    {
        modified = true;
        itemText = itemText.substring(0, itemText.length() - 1);
        _display->getTextBounds(itemText, x, y, &measuredX, &measuredY, &measuredWidth, &measuredHeight);
    }
    
    _display->setCursor(x, bounds.Top + y);
    _display->setTextColor(item.IsSelected ? ST7735_BLACK : ST7735_WHITE);
    _display->write(itemText.c_str());
};