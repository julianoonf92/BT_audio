#include "dependencies.h"
#include "variables.h"
#include "display.h"
#include "bt.h"
#include "ir.h"


void setup() {
  Serial.begin(115200);
  Wire.begin(22, 18);
  pinMode(RELAY_PIN, OUTPUT);

  PDM_OUTPUT = false;
  setupDisplay();
  setupBT();

  IrReceiver.begin(IR_RECEIVER_PIN, DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);

  volume.setVolume(0.3);
  
  a2dp_sink.set_auto_reconnect(true, 10);
  a2dp_sink.start("NiceAmp"); // Start Bluetooth Audio Receiver
  
}

void loop() {
  decodeIR();
  updateDisplay();

  delay(100);
}
