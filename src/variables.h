#ifndef VARIABLES_H
#define VARIABLES_H

#include "dependencies.h"

// Variables for display information
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String artist = "";
String album = "";
String title = "";
uint32_t durTime = 0;
uint32_t playtime = 0;
uint32_t duration;
uint32_t played;

const int charLimit = 21;

// Variables for Audio data
I2SStream i2s;
NumberFormatConverterStream convert(i2s);
VolumeStream volume(convert);
BluetoothA2DPSink a2dp_sink(volume);

LogarithmicVolumeControl lvc(0.2);
AudioInfo info(44100, 2, 32);

esp_avrc_playback_stat_t Playing;
bool isPlaying;
bool PDM_OUTPUT;

// IR commands
uint32_t irCode;

#endif // VARIABLES_H