/*
 * Author: Jon Trulson <jtrulson@ics.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <string>


#include <mraa/common.hpp>
#include <mraa/i2c.hpp>

#include <mraa/gpio.hpp>

namespace upm {
  
  // MADGWICK
  #ifndef MadgwickAHRS_h
  #define MadgwickAHRS_h
  #include <math.h>

  //--------------------------------------------------------------------------------------------
  // Variable declaration
  class Madgwick {
  private:
      static float invSqrt(float x);
      float beta;       // algorithm gain
      float q0;
      float q1;
      float q2;
      float q3; // quaternion of sensor frame relative to auxiliary frame
      float invSampleFreq;
      float roll;
      float pitch;
      float yaw;
      char anglesComputed;
      void computeAngles();

  //-------------------------------------------------------------------------------------------
  // Function declarations
  public:
      Madgwick(void);
      void begin(float sampleFrequency) { invSampleFreq = 1.0f / sampleFrequency; }
      void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
      void updateIMU(float gx, float gy, float gz, float ax, float ay, float az);
      //float getPitch(){return atan2f(2.0f * q2 * q3 - 2.0f * q0 * q1, 2.0f * q0 * q0 + 2.0f * q3 * q3 - 1.0f);};
      //float getRoll(){return -1.0f * asinf(2.0f * q1 * q3 + 2.0f * q0 * q2);};
      //float getYaw(){return atan2f(2.0f * q1 * q2 - 2.0f * q0 * q3, 2.0f * q0 * q0 + 2.0f * q1 * q1 - 1.0f);};
      float getRoll() {
          if (!anglesComputed) computeAngles();
          return roll * 57.29578f;
      }
      float getPitch() {
          if (!anglesComputed) computeAngles();
          return pitch * 57.29578f;
      }
      float getYaw() {
          if (!anglesComputed) computeAngles();
          return yaw * 57.29578f + 180.0f;
      }
      float getRollRadians() {
          if (!anglesComputed) computeAngles();
          return roll;
      }
      float getPitchRadians() {
          if (!anglesComputed) computeAngles();
          return pitch;
      }
      float getYawRadians() {
          if (!anglesComputed) computeAngles();
          return yaw;
      }
  };
  #endif

}


