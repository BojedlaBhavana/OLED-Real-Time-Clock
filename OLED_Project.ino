#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS3231 rtc;

int mode = 0;                    // 0 = Digital, 1 = Analog
unsigned long lastChange = 0;   // 3 sec mode switch timer
unsigned long lastRefresh = 0;  // Smooth refresh timer

// -------- LOADING SCREEN --------
void showLoadingScreen() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(10, 5);
  display.println("CLOCK");

  display.setTextSize(1);
  display.setCursor(28, 25);
  display.println("BOOTING...");

  display.display();

  int barX = 10;
  int barY = 40;
  int barW = 108;
  int barH = 10;

  display.drawRect(barX, barY, barW, barH, SSD1306_WHITE);
  display.display();

  for (int i = 1; i <= barW - 2; i++) {
    display.fillRect(
      barX + 1,
      barY + 1,
      i,
      barH - 2,
      SSD1306_WHITE
    );

    display.display();
    delay(15);
  }

  delay(300);
}

// -------- ANALOG CLOCK --------
void drawAnalogClock(DateTime now) {

  int cx = 64;
  int cy = 32;
  int radius = 30;

  display.drawCircle(cx, cy, radius, SSD1306_WHITE);

  float secondAngle = now.second() * 6 * PI / 180;
  float minuteAngle = now.minute() * 6 * PI / 180;

  float hourAngle =
    ((now.hour() % 12) + now.minute() / 60.0) * 30 * PI / 180;

  // Hour hand
  int hx = cx + (radius - 12) * sin(hourAngle);
  int hy = cy - (radius - 12) * cos(hourAngle);

  display.drawLine(
    cx, cy,
    hx, hy,
    SSD1306_WHITE
  );

  // Minute hand
  int mx = cx + (radius - 6) * sin(minuteAngle);
  int my = cy - (radius - 6) * cos(minuteAngle);

  display.drawLine(
    cx, cy,
    mx, my,
    SSD1306_WHITE
  );

  // Second hand
  int sx = cx + (radius - 2) * sin(secondAngle);
  int sy = cy - (radius - 2) * cos(secondAngle);

  display.drawLine(
    cx, cy,
    sx, sy,
    SSD1306_WHITE
  );
}

// -------- SETUP --------
void setup() {

  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.setTextColor(SSD1306_WHITE);

  rtc.begin();

  showLoadingScreen();

  lastChange = millis();
  lastRefresh = millis();
}

// -------- LOOP --------
void loop() {

  // Change Digital ↔ Analog every 3 seconds
  if (millis() - lastChange >= 3000) {

    mode = !mode;

    lastChange = millis();
  }

  // Refresh display every 100ms
  if (millis() - lastRefresh < 100) {
    return;
  }

  lastRefresh = millis();

  DateTime now = rtc.now();

  display.clearDisplay();

  // -------- DIGITAL CLOCK --------
  if (mode == 0) {

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 20);

    char timeBuffer[9];

    sprintf(
      timeBuffer,
      "%02d:%02d:%02d",
      now.hour(),
      now.minute(),
      now.second()
    );

    display.println(timeBuffer);

    display.setTextSize(1);
    display.setCursor(0, 40);

    char dateBuffer[11];

    sprintf(
      dateBuffer,
      "%04d-%02d-%02d",
      now.year(),
      now.month(),
      now.day()
    );

    display.println(dateBuffer);
  }

  // -------- ANALOG CLOCK --------
  else {

    drawAnalogClock(now);
  }

  display.display();
}