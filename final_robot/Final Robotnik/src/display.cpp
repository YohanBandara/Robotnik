#include "display.h"
#include "pins.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Initialize Screen with YOUR pins
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// --- MENU VARIABLES ---
volatile bool stopFlag = false;

enum RobotState { STATE_MENU, STATE_RUN_TASKS, STATE_FINISHED };
RobotState state = STATE_MENU;

int startTaskIndex = 0;
int currentTaskIndex = 0;
int attemptsUsed = 0;

// Task Storage (Set from main.cpp)
TaskFn* myTasks = nullptr;
const char** myTaskNames = nullptr;
int numTasks = 0;

// Button States
bool lastUp = HIGH, lastDown = HIGH, lastStart = HIGH, lastStop = HIGH;

// --- HELPERS ---

void setupDisplay() {
  tft.initR(INITR_BLACKTAB);  
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1); // Adjust if screen is upside down
  
  // Draw Initial Splash
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 40);
  tft.print("SYSTEM INIT");
}

void showDisplay(String text, int textSize, int x, int y){
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(textSize);
  tft.setCursor(x, y);
  tft.print(text);
}

bool justPressed(int pin, bool &lastState) {
  bool current = digitalRead(pin);
  bool pressed = (lastState == HIGH && current == LOW);
  lastState = current;
  return pressed;
}

void registerTasks(TaskFn* taskArray, const char** nameArray, int count) {
    myTasks = taskArray;
    myTaskNames = nameArray;
    numTasks = count;
}

// --- MENU LOGIC ---

void drawMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("MODA KARIYA");

  tft.setTextSize(1);
  tft.setCursor(5, 25);
  tft.print("Attempts: "); tft.print(attemptsUsed);

  int y = 45;
  for (int i = 0; i < numTasks; i++) {
    if (i == startTaskIndex) tft.setTextColor(ST77XX_YELLOW); // Selected
    else tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(5, y);
    tft.print(i + 1); tft.print(". "); tft.print(myTaskNames[i]);
    y += 15;
  }
}

void handleMenu() {
  bool changed = false;
  if (justPressed(BTN_UP, lastUp)) {
    if (startTaskIndex > 0) { startTaskIndex--; changed = true; }
  }
  if (justPressed(BTN_DOWN, lastDown)) {
    if (startTaskIndex < numTasks - 1) { startTaskIndex++; changed = true; }
  }
  if (changed) drawMenu();

  if (justPressed(BTN_START, lastStart)) {
    stopFlag = false;
    currentTaskIndex = startTaskIndex;
    attemptsUsed++;
    state = STATE_RUN_TASKS;
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 60);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_GREEN);
    tft.print("STARTING...");
    delay(500);
  }
}

void runTasksSequentially() {
  for (int i = currentTaskIndex; i < numTasks; i++) {
    if (stopFlag) break;

    currentTaskIndex = i;
    
    // Update Display
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 30);
    tft.print("RUNNING:");
    tft.setCursor(5, 60);
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_CYAN);
    tft.print(myTaskNames[i]);

    // RUN THE TASK
    if (myTasks[i] != nullptr) {
        myTasks[i](); 
    }

    // Check stop again after task returns
    if (stopFlag) break;
  }

  // Finished or Stopped
  if (stopFlag) {
    stopFlag = false;
    state = STATE_MENU;
    drawMenu();
  } else {
    state = STATE_FINISHED;
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    tft.setCursor(20, 50);
    tft.print("COMPLETED");
  }
}

// THE MAIN LOOP FUNCTION
void runMenuSystem() {
  // Always check STOP button
  if (state == STATE_RUN_TASKS) {
    if (justPressed(BTN_STOP, lastStop)) {
      stopFlag = true;
    }
  }

  switch (state) {
    case STATE_MENU:      handleMenu(); break;
    case STATE_RUN_TASKS: runTasksSequentially(); break;
    case STATE_FINISHED:  
      if (justPressed(BTN_START, lastStart)) {
        state = STATE_MENU;
        drawMenu();
      }
      break;
  }
}











// #include <SPI.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_ST7735.h>

// // Your pin mapping (Mega analog pins used as digital)
// #define TFT_CS   69   // A15
// #define TFT_DC   67   // A13
// #define TFT_RST  68   // A14

// Adafruit_ST7735 TFTscreen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// void setupDisplay() {
  
//   TFTscreen.initR(INITR_BLACKTAB);  
//   TFTscreen.fillScreen(ST77XX_BLACK);

//   TFTscreen.setTextSize(2);
//   TFTscreen.setTextColor(ST77XX_WHITE);  
//   TFTscreen.setCursor(6, 57);           
// }


// void showDisplay(String text, int textSize, int x=0, int y=0){
//   TFTscreen.fillScreen(ST77XX_BLACK);
//   TFTscreen.setCursor(x, y);
//   TFTscreen.print(text);
// }




// #include "display.h"


// Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
// bool display_ok = false;


// void setupDisplay() {
//   display_ok = display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//   delay(100);
//   if (display_ok) {
//     display.clearDisplay();
//     display.setTextColor(WHITE);
//   }
// }


// void showDisplay(String text, int textSize,int x=0,int y=0) {
//   if (!display_ok) return;
  
//   display.setTextSize(textSize);
//   display.setCursor(x,y);
//   display.println(text);
//   display.display();
// }


// void clearDisplay() {
//   if (!display_ok) return;
//   display.clearDisplay();
//   display.display();
// }