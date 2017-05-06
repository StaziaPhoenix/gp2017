#ifndef LongitudinalPIDController_H
#define LongitudinalPIDController_H

#include "Arduino.h"

class LongitudinalPIDController {
  public:
    LongitudinalPIDController() {}
    int pid(float err);
    void  incP();
    void  incD();
    void  decP();
    void  decD();
    
    float getP() const;
    float getD() const;

    void setGo(byte state);
    
  private:
    float kP  = 1.6; 
    float kD  = 2;
    float kI  = 0;
    
    float prev_err = 0;
    float I = 0;
    const byte outMax = 63;
    float threshold = 1.10;
    byte go = 0;

    int clamp(float pid);
};

#endif
