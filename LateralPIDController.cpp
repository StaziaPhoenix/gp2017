#include "LateralPIDController.h"

int LateralPIDController::pid(float err) {
  float change = err-prev_err;
  float pid = err*kP+ i + err*kI+(change)*kD;
  prev_err = err;
  
  return clamp(pid);
}

int LateralPIDController::clamp (int pid) {
  if (pid > outMax) {
    return outMax;
  } else if (pid < -outMax) {
    return -outMax;
  } else {
    return pid;
  }
}

void LateralPIDController::incP() {
  kP += 0.01;
}

void LateralPIDController::incD() {
  kD += 0.05;
}

void LateralPIDController::decP() {
  kP -= 0.01;
}

void LateralPIDController::decD() {
  kD -= 0.05;
}

float LateralPIDController::getP() const {
  return kP;
}

float LateralPIDController::getD() const {
  return kD;
}
