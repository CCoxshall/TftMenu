
#ifndef ST7735_Renderer_h
#define ST7735_Renderer_h

#include <Menu.h>
#include <Adafruit_ST7735.h>

class ST7735_Renderer : public MenuRenderer
{
    friend class Menu;

    public:
        ST7735_Renderer(Adafruit_ST7735* display);
    private:
        Adafruit_ST7735* _display;
        unsigned char _pageCount;
        unsigned char _currentPage;
    protected:
        void Init(vector<MenuItem>* menuItems);
        ItemBounds RenderItem(unsigned char index);
};

#endif