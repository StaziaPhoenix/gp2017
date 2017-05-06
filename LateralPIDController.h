#ifndef LateralPIDController_H
#define LateralPIDController_H

#include "Arduino.h"

class LateralPIDController {
  public:
    LateralPIDController() {}
    int pid(float err);
    void  incP();
    void  incD();
    void  decP();
    void  decD();
    
    float getP() const;
    float getD() const;
    
  private:
    float kP  = 1.15; 
    float kD  = 0.8;
    float kI  = 0;
    
    float prev_err = 0;
    float i = 0;
    const byte outMax = 68;
    float threshold = 1.10;
    byte go = 0;

    int clamp(int pid);
};

#endif
