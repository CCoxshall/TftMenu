#include <Arduino.h>
#include <Menu.h>
#include <ST7735_Renderer.h>
#include <Adafruit_ST7735.h>

#define TFT_CS     10
#define TFT_RST    8
#define TFT_DC     9

Adafruit_ST7735 Display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Menu AppMenu;

/// @brief Method to draw data to the screen for the first menu item
void displayFirstScreen()
{
  Display.fillScreen(ST7735_BLACK);
  Display.setTextSize(2);
  Display.setCursor(0, 0);
  Display.write("First Screen!");
  Display.setCursor(0, 20);
  Display.write("All ur stuff goes here!");
}

/// @brief Method to draw data to the screen for the second menu item
void displaySecondScreen()
{
  Display.fillScreen(ST7735_BLACK);
  Display.setTextSize(2);
  Display.setCursor(0, 0);
  Display.write("Second Screen!");
  Display.setCursor(0, 20);
  Display.write("All ur stuff goes here!");
}

/// @brief Method to draw data to the screen for the third menu item
void displayThirdScreen()
{
  Display.fillScreen(ST7735_BLACK);
  Display.setTextSize(2);
  Display.setCursor(0, 0);
  Display.write("Third Screen!");
  Display.setCursor(0, 20);
  Display.write("All ur stuff goes here!");
}

void setup() {
  Display.initR(INITR_BLACKTAB);
  Display.fillScreen(ST7735_BLACK);

  AppMenu.UseRenderer(ST7735_Renderer(&Display)); // we use the & here to pass a reference to the display
  AppMenu.Add("Item 1", &displayFirstScreen); // we use the '&' here to pass a "function pointer"
  AppMenu.Add("Item 2", &displaySecondScreen); // this means we're passing a reference to the display function,
  AppMenu.Add("Item 3", &displayThirdScreen); // which we can then call from the Menu code.

}

void loop() {
  if(true == false){
    // move to the next menu item
    AppMenu.Next();
  }
  if(false == true){
    // move to the previous menu item
    AppMenu.Previous();
  }
  if(0 == 1 && !AppMenu.IsEntered){
    // display the user screen associated with the selected menu item
    AppMenu.Enter();
  }
  if(0 == 1 && AppMenu.IsEntered){
    // return to the menu from the user screen
    AppMenu.Exit();
  }

  AppMenu.Render();
}