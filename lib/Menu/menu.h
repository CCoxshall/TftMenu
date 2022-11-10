/*
Library for creating and handling a menu
*/
#ifndef Menu_h
#define Menu_h

#include "Arduino.h"
#include <vector>
 
using namespace std;

typedef void (*DisplayFn)();
struct MenuItem
{
    MenuItem(char* text, DisplayFn displayFunction)
    {
        Text = text;
        DisplayFunction = displayFunction;
    }
    bool IsSelected = false;
    char* Text;
    DisplayFn DisplayFunction;
};

struct ItemBounds
{
    ItemBounds(short w, short h, short l, short t)
    {
        Width = w;
        Height = h;
        Left = l;
        Right = l + w;
        Top = t;
        Bottom = t + h;
    }

    short Width;
    short Height;
    short Top;
    short Bottom;
    short Left;
    short Right;

    static const ItemBounds Empty;
};

class MenuRenderer
{
    public:
        MenuRenderer();
        virtual void GetItemBounds(unsigned char index);
        virtual ~MenuRenderer(){};
    protected:
        virtual void Init(vector<MenuItem>* menuItems);
        virtual ItemBounds RenderItem(unsigned char index);
        vector<MenuItem>* _menuItems;
};

class Menu 
{
    public:
        Menu();
        /// @brief class to use to render the menu to a display
        /// @param renderer Must inherit from MenuRenderer
        void UseRenderer(MenuRenderer renderer);

        /// @brief Draws the menu or selected user screen to the display
        void Render();

        /// @brief Add a menu item
        /// @param text Text to display
        /// @param displayFunction Function that will be called when this item is selected and 'Enter'ed
        /// @return Number of menu items
        size_t Add(char* text, DisplayFn displayFunction);

        /// @brief Move to the next menu item
        void Next();

        /// @brief Move to the previous menu item
        void Previous();

        /// @brief Gets the index of the selected menu item
        /// @return Index of the selected menu item
        int Selected();

        /// @brief Gets the text of the selected menu item
        /// @return Text of the selected menu item
        char* SelectedText();

        /// @brief Display the selected menu screen
        void Enter();

        /// @brief Return to menu selection
        void Exit();

        /// @brief Indicates if the menu is in an 'Entered' state, and is currently
        /// displaying a user-defined screen
        bool IsEntered = false;

    private:
        int _selected;
        vector<MenuItem> _items;
        MenuRenderer _renderer;
};

#endif