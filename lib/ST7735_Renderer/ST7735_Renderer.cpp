#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <ST7735_Renderer.h>

#define ITEMS_PER_PAGE  6
#define ITEM_HEIGHT     16

ST7735_Renderer::ST7735_Renderer(Adafruit_ST7735* display)
{
    _display = display;
};

void ST7735_Renderer::Init(vector<MenuItem>* menuItems, uint8_t* selectedIndex)
{
    _menuItems = menuItems;
    _selectedIndex = selectedIndex;

    ResetDisplay();
};

void ST7735_Renderer::ResetDisplay()
{
    _display->setTextWrap(false);
    _display->fillScreen(ST7735_BLACK);
    _display->setTextSize(1);
    _display->setFont(NULL);
}

void ST7735_Renderer::Render()
{
    _pageCount = trunc(_menuItems->size() / ITEMS_PER_PAGE);
    if(_pageCount > 0){
        _scrollBar = true;
        RenderScrollBar();
    }

    if(trunc(*_selectedIndex / ITEMS_PER_PAGE) != _currentPage){
        _currentPage = ceil(*_selectedIndex / ITEMS_PER_PAGE);
    }

    for(uint8_t i = 0; i < 6; i++){
        RenderItem(i * _currentPage);
    }
};

void ST7735_Renderer::RenderScrollBar()
{
    // draw top & bottom arrows
    _display->fillTriangle(156, 0, 160, 4, 152, 4, ST7735_WHITE);
    _display->fillTriangle(156, 128, 160, 124, 152, 124, ST7735_WHITE);
    //draw scrollbar container
    _display->drawRect(152, 4, 8, 124, ST7735_WHITE);

    //get an approximate scroll block size and position
    uint8_t blockHeight = trunc(124 / _pageCount);
    uint8_t blockTop = blockHeight * _currentPage;

    //draw the scroll block
    _display->fillRect(152, blockTop, 8, blockHeight, ST7735_WHITE);
}

ItemBounds ST7735_Renderer::RenderItem(uint8_t index)
{
    uint8_t itemWidth = _scrollBar ? 150 : 160;
    uint8_t itemTop = 16 * (index - (_currentPage * ITEMS_PER_PAGE));

    ItemBounds bounds = { itemWidth, 16, 0, itemTop };

    MenuItem item = _menuItems->at(index);

    _display->setTextSize(1); // 6x8

    // draw the box - white filled for selected, black with white border for not
    _display->fillRect(bounds.Left, bounds.Top, bounds.Width, bounds.Height, item.IsSelected ? ST7735_WHITE : ST7735_BLACK);
    if(!item.IsSelected){
        _display->drawRect(bounds.Left, bounds.Top, bounds.Width, bounds.Height, ST7735_WHITE);
    }

    // measure the text - if longer than the allotted space, remove characters until it fits
    String itemText = item.Text;

    int16_t measuredX = 0, measuredY = 0;
    uint16_t measuredWidth = 0, measuredHeight = 0;

    int16_t x = 4, y = 4; // should be vertically centered with 4px horizontal padding

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

    return bounds;
};