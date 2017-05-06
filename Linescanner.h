#include "Arduino.h"
#include "GLOBAL.h"
#include "Servo.h"
#include "math.h"

#define numPixels 128

class Linescanner {
    byte CLK;
    byte sync;
    byte data;

    int pixels[numPixels];
    byte digital[numPixels];

    const unsigned int expose;

    int threshold;
    byte lineWidth;

    byte leftIdx;
    byte rightIdx;
    
  public:
//    Linescanner();
    
    Linescanner(int CLK,int sync,int data, unsigned int expose) : CLK(CLK), sync(sync), data(data), expose(expose) {}
    void printPixels();
    void printDigital();
    void getline();
    
    bool checkLatCases(byte angle, Servo & servo, byte debug);
    byte checkLongCases(byte debug);
    float calcError();

    void setLineWidth();
  private:

  
    byte findMax();
    float average(int lowIdx, int highIdx);
    float average(int low_lowIdx, int low_highIdx, 
              int high_lowIdx, int high_highIdx);
    void filter();
    void scan(int expose);
    void read();
    int calibrate(int expose);

    int findLeftEdge(int startIdx);
    int findRightEdge(int startIdx);
    int getLineWidth();
};
