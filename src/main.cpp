#include "dependencies.h"
#include "variables.h"
#include "display.h"
#include "bt.h"
#include "ir.h"

/*
On PCM5102 there are 4 exposed groups of 3 pads that must be soldered
1 - FLT - Filter select : Normal latency (Low) / Low latency (High)
2 - DEMP - De-emphasis control for 44.1kHz sampling rate: Off (Low) / On (High)
3 - XSMT - Soft mute control(1): Soft mute (Low) / soft un-mute (High)
4 - FMT - Audio format selection : I2S (Low) / Left justified (High)
*/


void setup() {
  Serial.begin(115200);

  AudioLogger::instance().begin(Serial, AudioLogger::Info);
  
  Wire.begin(sdaPin, sclPin); //SDA, SCL
  pinMode(RELAY_PIN, OUTPUT);
  a2dp_sink.disconnect();

  PDM_OUTPUT = false;
  setupDisplay();
  setupBT();

  IrReceiver.begin(IR_RECEIVER_PIN, DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);

  preferences.begin("audio", false);  // Open the namespace "audio" in read-write mode
  float newVolume = preferences.getFloat("volume", 0.3);  // Default to 0.3 if not set
  volume.setVolume(newVolume);
  
  a2dp_sink.set_auto_reconnect(true, 10);
  a2dp_sink.start("NiceAmp"); // Start Bluetooth Audio Receiver
  
}

void loop() {
  decodeIR();
  updateDisplay();

  delay(100);
}
