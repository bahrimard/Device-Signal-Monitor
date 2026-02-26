/*
 * Device Signal Monitor
 * Board: ESP32-S3 Mini
 * Author: bahrimardiansyah@gmail.com
 */

#include <Arduino.h>

// ================= CONFIG =================
static const gpio_num_t SIGNAL_PIN = GPIO_NUM_4;
static const uint32_t DEBOUNCE_MS = 50;
// ==========================================

volatile bool signalChanged = false;
volatile uint32_t lastInterruptTime = 0;
bool currentState = false;

// Interrupt handler
void IRAM_ATTR handleInterrupt()
{
  uint32_t now = millis();
  if (now - lastInterruptTime > DEBOUNCE_MS)
  {
    signalChanged = true;
    lastInterruptTime = now;
  }
}

void setup()
{
  Serial.begin(115200);

  // Configure pin with internal pulldown
  pinMode(SIGNAL_PIN, INPUT_PULLDOWN);

  // Attach interrupt
  attachInterrupt(SIGNAL_PIN, handleInterrupt, CHANGE);

  Serial.println("Signal Monitor Started");
}

void loop()
{
  if (signalChanged)
  {
    signalChanged = false;

    bool newState = digitalRead(SIGNAL_PIN);

    if (newState != currentState)
    {
      currentState = newState;

      if (currentState)
      {
        Serial.println(">>> SIGNAL HIGH (Device Connected)");
      }
      else
      {
        Serial.println(">>> SIGNAL LOW (Device Disconnected)");
      }
    }
  }
}