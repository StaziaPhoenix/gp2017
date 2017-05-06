#ifndef COMMAND_H
#define COMMAND_H

#include "Arduino.h"
#include "GLOBAL.h"

class CommandLine {
  public:
    CommandLine() {}
    void printCmdList();
    byte getAck();
    void doSerialCmd();
    byte getSerialCmd();
    void printNewCmdLn();
    
  private:
    
};

#endif
