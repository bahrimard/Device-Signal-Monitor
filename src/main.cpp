#include <Arduino.h>

static const gpio_num_t SIGNAL_PIN = GPIO_NUM_4;
static const uint32_t STABLE_TIME_MS = 50;   // bisa 30–100ms

volatile bool interruptTriggered = false;

bool currentStableState = false;
bool lastReadState = false;

uint32_t lastChangeTime = 0;

void IRAM_ATTR handleInterrupt()
{
  interruptTriggered = true;
}

void setup()
{
  Serial.begin(115200);

  pinMode(SIGNAL_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(SIGNAL_PIN), handleInterrupt, CHANGE);

  currentStableState = digitalRead(SIGNAL_PIN);
  lastReadState = currentStableState;
  lastChangeTime = millis();

  Serial.println("Signal Monitor Started");
  Serial.printf(">>> Initial State: %d\n", currentStableState);
}

void loop()
{
  if (interruptTriggered)
  {
    interruptTriggered = false;

    bool newState = digitalRead(SIGNAL_PIN);

    if (newState != lastReadState)
    {
      lastReadState = newState;
      lastChangeTime = millis();   // reset timer tiap ada perubahan
    }
  }

  // cek stabil tanpa delay
  if ((millis() - lastChangeTime) >= STABLE_TIME_MS)
  {
    if (currentStableState != lastReadState)
    {
      currentStableState = lastReadState;

      Serial.printf(">>> Stable State: %d\n", currentStableState);

      if (currentStableState == LOW)
      {
        Serial.println(">>> DEVICE DISCONNECTED");
        Serial.println(">>> HIT API -> SEND MESSAGE");
      }
      else {
        Serial.println(">>> DEVICE CONNECTED");
      }
    }
  }
}