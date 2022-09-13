#include <Arduino.h>


String ledState (uint8_t ledState){
  if(ledState == HIGH){
    return "1";
  }
  else return "0";
}

void task1()
{
  enum class TaskStates
  {
    INIT,
    WAIT_COMMANDS
  };
  static TaskStates taskState = TaskStates::INIT;
  constexpr uint8_t led = 25;
  constexpr uint8_t button1Pin = 12;
  constexpr uint8_t button2Pin = 13;
  constexpr uint8_t button3Pin = 32;
  constexpr uint8_t button4Pin = 33;

  switch (taskState)
  {
  case TaskStates::INIT:
  {
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT_PULLUP);
    pinMode(button4Pin, INPUT_PULLUP);
    taskState = TaskStates::WAIT_COMMANDS;
    break;
  }
  case TaskStates::WAIT_COMMANDS:
  {
    if (Serial.available() > 0)
    {
      String command = Serial.readStringUntil('\n');
      if (command == "ledON")
      {
        digitalWrite(led, HIGH);
      }
      else if (command == "ledOFF")
      {
        digitalWrite(led, LOW);
      }
      else if (command == "readBUTTONS")
      {

        Serial.print("Button: ");
        Serial.print(ledState(digitalRead(button1Pin)).c_str());
        Serial.print(" Led Verde: ");
        Serial.print(ledState(digitalRead(led)).c_str());
        Serial.print('\n');
      }
    }
    break;
  }
  default:
  {
    break;
  }
  }
}
