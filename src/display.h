#ifndef DISPLAY_H
#define DISPLAY_H

#include "variables.h"

// Define custom characters for play, pause and volume icons
uint8_t playIcon[8] = {
 0xe0,0xb8,0x8e,0x83,0x83,0x8e,0xb8,0xe0 };

uint8_t pauseIcon[8] = {
 0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3 };

uint8_t volIcon[8] = {
 0x18,0x04,0x52,0xc9,0xc9,0x52,0x04,0x18 };

void setupDisplay() {
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("NiceAmp");
  display.println("Waiting to connect");

  display.display();
}


void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  duration = durTime / 1000;
  played = playtime / 1000;

  // Truncate each line if necessary
  String artistLine1 = artist.substring(0, charLimit);
  String artistLine2 = artist.length() > charLimit ? artist.substring(charLimit, charLimit * 2) : "";

  String albumLine1 = album.substring(0, charLimit);
  String albumLine2 = album.length() > charLimit ? album.substring(charLimit, charLimit * 2) : "";

  String titleLine1 = title.substring(0, charLimit);
  String titleLine2 = title.length() > charLimit ? title.substring(charLimit, charLimit * 2) : "";

  // Display artist over two lines
  display.setCursor(0, 0);
  display.println(titleLine1);
  display.setCursor(0, 8);
  display.println(titleLine2);

  // Display album over two lines
  display.setCursor(0, 16);
  display.println(artistLine1);
  display.setCursor(0, 24);
  display.println(artistLine2);

  // Display title over two lines
  display.setCursor(0, 32);
  display.println(albumLine1);
  display.setCursor(0, 40);
  display.println(albumLine2);

  // Display formatted duration on one line
  display.setCursor(0, 56);
  display.printf("%02d:%02d / %02d:%02d", played / 60, played % 60, duration / 60, duration % 60);
  // Display play/pause icon based on the current state
  if (isPlaying) {
    display.drawBitmap(84, 56, playIcon, 8, 8, WHITE);
  } else {
    display.drawBitmap(84, 56, pauseIcon, 8, 8, WHITE);
  }
  display.drawBitmap(100, 56, volIcon, 8, 8, WHITE);
  display.setCursor(112, 56);
  display.print(static_cast<int>(volume.volume() * 10));

  display.display();
}

#endif // DISPLAY_H