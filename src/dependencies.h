#include <Arduino.h>
#include <Wire.h>
#include <Preferences.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <IRremote.h>

#include "BluetoothA2DPSink.h"
#include "AudioTools.h"

// OLED parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define RELAY_PIN 14
#define sdaPin 22
#define sclPin 18

// IR parameters
#define IR_RECEIVER_PIN 12
#define DECODE_NEC
//#define DECODE_DISTANCE_WIDTH
//#define DECODE_HASH
#define RAW_BUFFER_LENGTH  1000

// IR commands
#define IR_CMD_PLAY_PAUSE 0x44
#define IR_CMD_VOLUME_UP 0x9
#define IR_CMD_VOLUME_DOWN 0x15
#define IR_CMD_VOLUME_MUTE 0x47
#define IR_CMD_FORWARD 0x43
#define IR_CMD_BACKWARD 0x40
#define IR_CMD_POWER 0x45

// Sound parameters
#define VOLUME_STEP 0.1
