#include "Linescanner.h"

void Linescanner::scan(int expose) {
  //Initialize scan (SI)
  digitalWrite(CLK,LOW);
  digitalWrite(sync,HIGH);
  digitalWrite(CLK,HIGH);
  digitalWrite(sync,LOW);
  digitalWrite(CLK,LOW);

  //CLK all pixels
  for (int i=0;i<128;i++) {
    digitalWrite(CLK,HIGH);
    digitalWrite(CLK,LOW);
  }

  //Pixel charge transfer time (t_qt)
  delayMicroseconds(expose);

  digitalWrite(sync,HIGH);
  digitalWrite(CLK,HIGH);
  digitalWrite(sync,LOW);
  digitalWrite(CLK,LOW);
}

void Linescanner::read() {
  //Reading data from cam
  for (int i=0;i<128;i++) {
    pixels[i] = analogRead(data);
    
    digitalWrite(CLK,HIGH);
    digitalWrite(CLK,LOW);
  }
}

void Linescanner::setLineWidth() {
  lineWidth = getLineWidth();
}

int Linescanner::calibrate(int expose) {
  
  byte maxIdx = findMax();
  float high_avg = average(maxIdx-5,maxIdx+5);
  float low_avg = average(0, 5, 123, 128);

  threshold = (high_avg-low_avg)/2 + low_avg;

  return threshold;
}

byte Linescanner::findMax() {
  int maxim = 0;
  byte idx = 0;
  for (int i = 0; i < 128; i++) {
    if (pixels[i] > maxim) {
      maxim = pixels[i];
      idx = i;
    }
  }
  return idx;
}

float Linescanner::average(int lowIdx, int highIdx) {
  int sum = 0;
  for (int i = lowIdx; i < highIdx+1; i++) {
    sum += pixels[i];
  }
  return sum/11;
}

float Linescanner::average(int low_lowIdx, int low_highIdx, 
              int high_lowIdx, int high_highIdx) {
  int sum = 0;
  for (int i = low_lowIdx; i < low_highIdx; i++) {
    sum += pixels[i];
  }
  for (int i = high_lowIdx; i < high_highIdx; i++) {
    sum+= pixels[i];
  }
  return sum/10;
}

void Linescanner::printPixels() {
  for (int i=0;i<128;i++) {
    BTSerial.print(pixels[i]);
    BTSerial.print(" ");
  }
  BTSerial.println();
}

void Linescanner::printDigital() {
  for (int i=0;i<128;i++) {
    BTSerial.print(digital[i]);
  }
  BTSerial.println();
}

/*
 * filters the analog data from Linescanner into digital HIGH/LOW, where
 * high indicates the line and low occurs else
 */
void Linescanner::filter() {
  for (int i = 0; i < numPixels; i++) {
    if (pixels[i] > threshold) {
      digital[i] = 1;
    } else {
      digital[i] = 0;
    }
  }
}

void Linescanner::getline() {
  scan(expose);
  read();
  calibrate(expose);
  filter();
}

/* ---------------------------------
 * FIND RIGHT EDGE
 * --------------------------------- */
int Linescanner::findRightEdge(int startIdx) {
  if (digital[startIdx] == 1 && digital[startIdx-1]== 1) {
    //BTSerial.println("At end end of right");
    return 128;
  }
  for (int i = startIdx; i > 4; i--) {
    if (digital[i] == 0 && digital[i-1] == 1 && digital[i-2] == 1 && 
        digital[i-3] == 1) {
      return i-1;
    }
  }
  // if no line
  //BTSerial.println("Could not find right edge");
  return NOLINE;
}

/* ---------------------------------
 * FIND LEFT EDGE
 * --------------------------------- */
int Linescanner::findLeftEdge(int startIdx) {
  if (digital[startIdx] == 1 && digital[startIdx+1] == 1) {
    //BTSerial.println("At end end of left");
    return 0;
  }
  for (int i = startIdx; i < numPixels-4; i++) {
    if (digital[i] == 0 && digital[i+1] == 1 && digital[i+2] == 1 && 
        digital[i+3] == 1) {
      return i+1;
    }
  }
  // if no line
  //BTSerial.println("Could not find left edge");
  return NOLINE;
}
//
//void Linescanner::findEdges() {
//  for (int i = 0; i < numPixels-4; i++) {
//    if (digital[i] == 0 && digital[i+1] && digital[i+2] == 1 &&
//        digital[i+3] == 1) {
//      leftIdx = i+1;
//      for (int j = i+4; j < numPixels-4; j++) {
//        if (digital[j] == 0) {
//          holeCount++;
//        }
//      }
//    }
//  }
//  leftIdx = NOLINE;
//}


/* ---------------------------------
 * SET LINE WIDTH
 * --------------------------------- */
int Linescanner::getLineWidth() {
  getline();

  leftIdx = findLeftEdge(0);
  rightIdx = findRightEdge(NUM_PIXELS-1);

  return rightIdx - leftIdx;
}

// ---------------------------------
bool Linescanner::checkLatCases(byte angle, Servo & servo, byte debug) {
  getline();

  leftIdx = findLeftEdge(0);
  rightIdx = findRightEdge(NUM_PIXELS-1);

//    findEdges();
  
  // lost sight of the line, stay turning in previous direction
  if (leftIdx == NOLINE || (rightIdx-leftIdx) > 80) {
    // if (leftIdx == NOLINE || holeCount > 3) {
    if (angle > 90) {
      servo.write(LEFT);
      if (debug) {
        BTSerial.println("I am running left!");
      }
    } else {
      servo.write(RIGHT);
      if (debug) {
        BTSerial.println("I am running right!");
      }
    }
    return true;
  }

//  // intersection, stay true
//  if ( (rightIdx-leftIdx) > (lineWidth+10) ) {
//    if (debug) {
//      BTSerial.println("Intersection");
//    }
//    return true;
//  }
  
  // if none of these, adjust according to PID
  return false;
}

byte Linescanner::checkLongCases(byte debug) {
  getline();

  leftIdx = findLeftEdge(0);
  rightIdx = findRightEdge(NUM_PIXELS-1);

  // lost sight of the line, return high to slow down
  if (leftIdx == NOLINE || (rightIdx-leftIdx) > 80) {
    return 0;
  }

  // intersection, stay true
  if ( (rightIdx-leftIdx) > (lineWidth+10) ) {
    if (debug) {
      BTSerial.println("Intersection");
    }
    return 1;
  }
  
  // if none of these, adjust according to PID
  return 2;
}

// ---------------------------------
float Linescanner::calcError() {
  int error_pix = (rightIdx-leftIdx)/2 + leftIdx - SETPOINT;    
  return atan2(error_pix,ADJACENT)*(180/3.141592);
}

