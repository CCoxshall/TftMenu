#include "Arduino.h"
#include "Menu.h"

Menu::Menu(){
    _selected = 0;
}

void Menu::UseRenderer(MenuRenderer renderer)
{
    _renderer = renderer;
    _renderer.Init(&_items, &_selected);
}

size_t Menu::Add(char* text, DisplayFn displayFunction)
{
    _items.push_back(MenuItem(text, displayFunction));
    size_t count = _items.size();
    if(count == 1){
        _items.at(0).IsSelected = true;
    }
    return count;
}

void Menu::Next()
{
    _items.at(_selected).IsSelected = false;
    _selected++;
    if(_selected >= _items.size()){
        _selected = 0;
    }
    _items.at(_selected).IsSelected = true;
}

void Menu::Previous()
{
    _items.at(_selected).IsSelected = false;
    _selected--;
    if(_selected < 0){
        _selected = (_items.size() - 1);
    }
    _items.at(_selected).IsSelected = true;
}

uint8_t Menu::Selected()
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
    IsEntered = false;
}

void Menu::Render()
{
    _renderer.Render();
}