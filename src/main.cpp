#include <Arduino.h>
#include <Menu.h>
#include <Wire.h>
#include <ST7735_Renderer.h>
#include <Adafruit_ST7735.h>

#define TFT_CS     15
#define TFT_RST    2
#define TFT_DC     0

Adafruit_ST7735 Tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Menu AppMenu;
// SSD1306_Renderer DisplayRenderer = {&Oled};
ST7735_Renderer DisplayRenderer = {&Tft};

/// @brief Method to draw data to the screen for the first menu item
void displayFirstScreen()
{
  Tft.setCursor(0, 0);
  Tft.write("First Screen!");
  Tft.setCursor(0, 20);
  Tft.write("All ur stuff goes here!");
}

/// @brief Method to draw data to the screen for the second menu item
void displaySecondScreen()
{
  Tft.setCursor(0, 0);
  Tft.write("Second Screen!");
  Tft.setCursor(0, 20);
  Tft.write("All ur stuff goes here!");
}

/// @brief Method to draw data to the screen for the third menu item
void displayThirdScreen()
{
  Tft.setCursor(0, 0);
  Tft.write("Third Screen!");
  Tft.setCursor(0, 20);
  Tft.write("All ur stuff goes here!");
}

void setup() {

  Serial.begin(115200);

  Wire.begin();

  // Oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, false);
  // Oled.clearDisplay();
  // Oled.setTextColor(WHITE);
  // Oled.setTextSize(1);

  Tft.initR(INITR_BLACKTAB);
  Tft.fillScreen(ST7735_BLACK);

  AppMenu.UseRenderer(&DisplayRenderer); // we use the & here to pass a reference to the display
  AppMenu.Add("Item 1", &displayFirstScreen); // we use the '&' here to pass a "function pointer"
  AppMenu.Add("Item 2", &displaySecondScreen); // this means we're passing a reference to the display function,
  AppMenu.Add("Item 3", &displayThirdScreen); // which we can then call from the Menu code.
  AppMenu.Add("Item 4", &displayFirstScreen); // we use the '&' here to pass a "function pointer"
  AppMenu.Add("Item 5", &displaySecondScreen); // this means we're passing a reference to the display function,
  AppMenu.Add("Item 6", &displayThirdScreen); // which we can then call from the Menu code.
  AppMenu.Add("Item 7", &displayFirstScreen); // we use the '&' here to pass a "function pointer"
  AppMenu.Add("Item 8", &displaySecondScreen); // this means we're passing a reference to the display function,
  AppMenu.Add("Item 9", &displayThirdScreen); // which we can then call from the Menu code.
  AppMenu.Add("Item 10", &displayFirstScreen); // we use the '&' here to pass a "function pointer"
  AppMenu.Add("Item 11", &displaySecondScreen); // this means we're passing a reference to the display function,
  AppMenu.Add("Item 12", &displayThirdScreen); // which we can then call from the Menu code.

}

void loop() {
  
  char command = Serial.read();
  
  uint8_t x, y;

  switch (command)
  {
    case 'n':
      // move to the next menu item
      AppMenu.Next();
      Serial.println(AppMenu.SelectedText());
      AppMenu.SelectedTopLeft(&x, &y);
      Serial.println("X: " + String(x) + " Y: " + String(y));
      break;
    case 'p':
      // move to the previous menu item
      AppMenu.Previous();
      Serial.println(AppMenu.SelectedText());
      Serial.println("X: " + String(x) + " Y: " + String(y));
      break;
    case 'e':
      if(AppMenu.IsEntered){
        // return to the menu from the user screen
        AppMenu.Exit();
        Serial.println("Exited");
      }
      else {
          // display the user screen associated with the selected menu item
        AppMenu.Enter();
        Serial.println("Entered");
      }
      break;
    default:
      break;
  }

  AppMenu.Render();
}