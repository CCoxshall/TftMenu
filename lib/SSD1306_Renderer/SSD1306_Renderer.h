
#ifndef SSD1306_Renderer_h
#define SSD1306_Renderer_h

#include <Menu.h>
#include <Adafruit_SSD1306.h>

class SSD1306_Renderer : public MenuRenderer
{
    public:
        SSD1306_Renderer(Adafruit_SSD1306* display);
        void Init(vector<MenuItem>* menuItems, uint8_t* selectedIndex);
        void Render();
        void ClearScreen();
        ItemBounds GetSelectedItemBounds();
        ~SSD1306_Renderer(){};
    private:
        Adafruit_SSD1306* _display;
        uint8_t _pageCount;
        uint8_t _currentPage;
        bool _scrollBar;
        void ResetDisplay();
        void RenderScrollBar();
    protected:
        ItemBounds RenderItem(uint8_t index);
};

#endif