/**
 * @file Throttle.cpp
 * @brief
 * @author Travis Lane
 * @version 0.1.0
 * @date 2015-03-04
 */

#include "Throttle.h"
#include "Arduino.h"

/*
 * @brief Creates a new throttle.
 *
 * @param new_pin The pin to read from.
 * @param new_min (Optional) The minimum value. Defaults to 0.
 * @param new_max (Optional) The maximum value. Defaults to 1023.
 */
Throttle::Throttle(int new_pin, int new_min, int new_max)
{
  pin = new_pin;

  min = new_min;
  max = new_max;

  updateRange();
}

/**
 * @brief read the percentage value from the pin.
 *
 * @return A percentage. 0 to 100 as an integer.
 */
float Throttle::read()
{
  int val = analogRead(pin);
  
  if(val <= min) {
    // Low range;
    return 0.0f;
  }

  if(val >= max) {
    // High range
    return 100.0f;
  }

  val = val - min; // Shift downward
  return ((float)val / (float)range) * 100.0f; // Compute result
}

/**
 * @brief Set the minimum value for the throttle.
 *
 * @param new_min The new minimum value.
 */
void Throttle::setMin(int new_min)
{
  min = new_min;
  updateRange();
}

/**
 * @brief Set the new maximum value for the throttle.
 *
 * @param new_max The new maximum value.
 */
void Throttle::setMax(int new_max)
{
  max = new_max;
  updateRange();
}

/**
 * @brief Update the range used for calculations.
 */
void Throttle::updateRange()
{
  range = max - min;
}
