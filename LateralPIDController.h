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
    float kP  = 0.6; // inverse 0.6
    float kD  = 2.0; // inverse 3
    float kI  = 0;
    
    float prev_err = 0;
    float i = 0;
    const byte outMax = 80;
    float threshold = 1.10;
    byte go = 0;

    int clamp(int pid);
};

#endif
