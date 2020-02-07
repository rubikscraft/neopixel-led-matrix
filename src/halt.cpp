#include "halt.h"

const uint8_t scrollSpeed = 50;

Better_NeoMatrix *errorDisplay = 0;

void printToDisplay(String message, bool onlyOnce)
{
  uint32_t fullLengthInPixels = message.length() * (dispCharWidth + 1);
  uint32_t i;
  do
  {
    for (i = 0; i < fullLengthInPixels; i++)
    {
      errorDisplay->setCursor(-i, textYPos);
      errorDisplay->clear();
      errorDisplay->print(message);
      errorDisplay->show();
      delay(scrollSpeed);
      if (i == 0)
        delay(500);
    }
  } while (!onlyOnce);
}

// Stops execution and gives an error message
void halt(String message, bool onlyOnce)
{
  Serial.print("Arduino halted with: ");
  Serial.println(message);

  if (errorDisplay != 0)
  {
    printToDisplay(message, onlyOnce);
  }
  else
  {
    do
    {
      delay(10000);
      Serial.print(".");
    } while (!onlyOnce);
  }
}

void setHaltDisplay(Better_NeoMatrix *mat)
{
  errorDisplay = mat;
}