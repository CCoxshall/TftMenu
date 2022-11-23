#include <Arduino.h>
#include <Menu.h>
#include <Wire.h>
#include <ST7735_Renderer.h>
#include <Adafruit_ST7735.h>

#define TFT_CS     15
#define TFT_RST    2
#define TFT_DC     0

#define RE_SW      4
#define RE_DT      5
#define RE_CLK     16

Adafruit_ST7735 Tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Menu AppMenu;
ST7735_Renderer DisplayRenderer = {&Tft};

// rotary encoder
int counter = 0; 
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;

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

  pinMode(RE_CLK, INPUT);
  pinMode(RE_DT, INPUT);
  pinMode(RE_SW, INPUT_PULLUP);

	// Read the initial state of the rotary encoder
	lastStateCLK = digitalRead(RE_CLK);

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

	currentStateCLK = digitalRead(RE_CLK);

	if ((currentStateCLK != lastStateCLK) && currentStateCLK == 1){
		if (digitalRead(RE_DT) != currentStateCLK) {
      AppMenu.Next();
		} else {
      AppMenu.Previous();
		}
	}

  lastStateCLK = currentStateCLK;

	int btnState = digitalRead(RE_SW);

	if (btnState == LOW) {
		if (millis() - lastButtonPress > 100) {
			if(AppMenu.IsEntered){
        AppMenu.Exit();
      }
      else {
        AppMenu.Enter();
      }
		}

		lastButtonPress = millis();
	}

  AppMenu.Render();
  delay(1);
}