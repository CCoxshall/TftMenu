#include "Arduino.h"
#include "Menu.h"

Menu::Menu(){
    _selected = 0;
}

void Menu::UseRenderer(MenuRenderer renderer)
{
    _renderer = renderer;
}

size_t Menu::Add(char* text, DisplayFn displayFunction)
{
    _items.push_back(MenuItem(text, displayFunction));
    return _items.size();
}

void Menu::Next()
{
    _selected++;
    if(_selected >= _items.size()){
        _selected = 0;
    }
}

void Menu::Previous()
{
    _selected--;
    if(_selected < 0){
        _selected = (_items.size() - 1);
    }
}

int Menu::Selected()
{
    return _selected;
}

char* Menu::SelectedText()
{
    return _items.at(_selected).Text;
}

void Menu::Enter()
{
    _items.at(_selected).DisplayFunction();
    IsEntered = true;
}

void Menu::Exit()
{
    //_renderer.RenderPage();
    IsEntered = false;
}