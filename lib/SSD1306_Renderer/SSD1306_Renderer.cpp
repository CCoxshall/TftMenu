#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <SSD1306_Renderer.h>

#define ITEMS_PER_PAGE  4
#define ITEM_HEIGHT     16

SSD1306_Renderer::SSD1306_Renderer(Adafruit_SSD1306* display)
{
    _display = display;
};

void SSD1306_Renderer::Init(vector<MenuItem>* menuItems, uint8_t* selectedIndex)
{
    _menuItems = menuItems;
    _selectedIndex = selectedIndex;

    ResetDisplay();
};

void SSD1306_Renderer::ResetDisplay()
{
    _display->setTextWrap(false);
    _display->fillScreen(SSD1306_BLACK);
    _display->setTextSize(1);
    _display->setFont(NULL);
}

void SSD1306_Renderer::Render()
{
    _pageCount = trunc(_menuItems->size() / ITEMS_PER_PAGE);
    if(_pageCount > 0){
        _scrollBar = true;
        RenderScrollBar();
    }

    if(trunc(*_selectedIndex / ITEMS_PER_PAGE) != _currentPage){
        _currentPage = ceil(*_selectedIndex / ITEMS_PER_PAGE);
    }

    for(uint8_t i = 0; i < min(ITEMS_PER_PAGE, (int)_menuItems->size()); i++){
        RenderItem(i * _currentPage);
    }

    _display->display();
};

void SSD1306_Renderer::ClearScreen()
{
    _display->clearDisplay();
};

void SSD1306_Renderer::RenderScrollBar()
{
    // draw top & bottom arrows
    _display->fillTriangle(124, 0, 128, 4, 122, 4, SSD1306_WHITE);
    _display->fillTriangle(124, 64, 128, 60, 122, 60, SSD1306_WHITE);
    //draw scrollbar container
    _display->drawRect(122, 4, 8, 60, SSD1306_WHITE);

    //get an approximate scroll block size and position
    uint8_t blockHeight = trunc(60 / _pageCount);
    uint8_t blockTop = blockHeight * _currentPage;

    //draw the scroll block
    _display->fillRect(122, blockTop, 8, blockHeight, SSD1306_WHITE);
}

ItemBounds SSD1306_Renderer::GetSelectedItemBounds()
{
    uint8_t itemWidth = _scrollBar ? 120 : 128;
    uint8_t itemTop = 16 * (*_selectedIndex - (_currentPage * ITEMS_PER_PAGE));

    ItemBounds bounds = { itemWidth, 16, 0, itemTop };

    return bounds;
}

ItemBounds SSD1306_Renderer::RenderItem(uint8_t index)
{
    uint8_t itemWidth = _scrollBar ? 120 : 128;
    uint8_t itemTop = 16 * (index - (_currentPage * ITEMS_PER_PAGE));

    ItemBounds bounds = { itemWidth, 16, 0, itemTop };

    MenuItem item = _menuItems->at(index);

    _display->setTextSize(1); // 6x8

    // draw the box - white filled for selected, black with white border for not
    _display->fillRect(bounds.Left, bounds.Top, bounds.Width, bounds.Height, item.IsSelected ? SSD1306_WHITE : SSD1306_BLACK);
    if(!item.IsSelected){
        _display->drawRect(bounds.Left, bounds.Top, bounds.Width, bounds.Height, SSD1306_WHITE);
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
    _display->setTextColor(item.IsSelected ? SSD1306_BLACK : SSD1306_WHITE);
    _display->write(itemText.c_str());

    return bounds;
};