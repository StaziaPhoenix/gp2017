#include "CommandLine.h"

void CommandLine::printCmdList() {
  BTSerial.print("COMMANDS:\r\n");
  
  //Servo
  BTSerial.print("   Servo:\r\n");
  BTSerial.print("      <w>    Straight \r\n");
  BTSerial.print("      <a>    Left \r\n");
  BTSerial.print("      <d>    Right \r\n");

  //motor
  BTSerial.print("   Motor Config:\r\n");
//  BTSerial.print("      <o>    PWM 255 (100%)\r\n");
  BTSerial.print("      <9>    PWM 230  (90%)\r\n");
  BTSerial.print("      <8>    PWM 204  (80%)\r\n");
  BTSerial.print("      <7>    PWM 179  (70%)\r\n");
  BTSerial.print("      <6>    PWM 153  (60%)\r\n");
  BTSerial.print("      <5>    PWM 128  (50%)\r\n");
  BTSerial.print("      <4>    PWM 102  (40%)\r\n");
  BTSerial.print("      <3>    PWM  77  (30%)\r\n");
  BTSerial.print("      <2>    PWM  51  (20%)\r\n");
  BTSerial.print("      <1>    PWM  26  (10%)\r\n");  
  BTSerial.print("      <0>    PWM   0   (0%)\r\n");  

  // PID
  BTSerial.print("   PID Config:\r\n");
  BTSerial.print("      <l>    Increase p by 1%\r\n");
  BTSerial.print("      <k>    Decrease p by 1%\r\n");
  BTSerial.print("      <m>    Inc d by 10%\r\n");
  BTSerial.print("      <n>    Dec d by 10%\r\n");

  BTSerial.print("      <x>    Set minSpeed++\r\n");
  BTSerial.print("      <z>    Set minSpeed--\r\n");

  BTSerial.print("      <p>    Set maxSpeed++\r\n");
  BTSerial.print("      <o>    Set maxSpeed--\r\n");
  
  // modes
  BTSerial.print("   Options:\r\n");
  BTSerial.print("      <h>    Help (Command List)\r\n"); 
  BTSerial.print("      <r>    Go (Operates Autonomously)\r\n");
  BTSerial.print("      <t>    Motor only\r\n");
  BTSerial.print("      <s>    Servo Only\r\n");
  BTSerial.print("      <c>    Cameras Only\r\n");
  
  // misc
  BTSerial.print("      <g>    Toggle debug statements\r\n");
  BTSerial.print("      <e>    Stop\r\n");

  BTSerial.print("\n");
}

byte CommandLine::getAck() {
  BTSerial.print("\r\nPress <h> for command list\r\n");
    BTSerial.print(">");
    byte inByte = BTSerial.read();

    if ( inByte == 'c' ) {
      BTSerial.print(inByte);
      BTSerial.print("\r\n");
      printCmdList();
      printNewCmdLn();
      return 1;
    }   
    return 0;
}

// Prompts User for input BTSerial command
//    Returns BTSerial command
byte CommandLine::getSerialCmd() {
  byte inByte;
  if (BTSerial.available()) {
    inByte = BTSerial.read();
    BTSerial.print(inByte);
    BTSerial.print("\r\n");
    return inByte;
  } else {
    return NONE;
  }
}

// Prints a new command line cursor
void CommandLine::printNewCmdLn() {
  BTSerial.print("\r\n");
  BTSerial.print(">");
}

