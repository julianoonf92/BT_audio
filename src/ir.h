#ifndef IR_H
#define IR_H

#include "bt.h"

void decodeIRraw(){
  if (IrReceiver.available()) {
    IrReceiver.initDecodedIRData(); // is required, if we do not call decode();
    IrReceiver.decode();
    IrReceiver.resume(); // Early enable receiving of the next IR frame
    /*
     * Print a summary and then timing of received data
     */
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRResultRawFormatted(&Serial, true);

    Serial.println();

    /*
     * Finally, check the received data and perform actions according to the received command
     */
    auto tDecodedRawData = IrReceiver.decodedIRData.decodedRawData; // uint32_t on 8 and 16 bit CPUs and uint64_t on 32 and 64 bit CPUs
    
  }
}

void decodeIR(){
  if (IrReceiver.available()) {
    IrReceiver.initDecodedIRData(); // is required, if we do not call decode();
    IrReceiver.decode();
    IrReceiver.printIRResultShort(&Serial);
    irCode = IrReceiver.decodedIRData.command;
    parseIRCommand(irCode);
    IrReceiver.resume();
  }
}


#endif // IR_H