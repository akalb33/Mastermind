#pragma once

#include "Character.h"

class Button : public Character
{
public:
   Button();
   virtual ~Button();
   virtual void Process(float deltaTime);
   bool isPressed() const;

private:
   bool mPressed;
};
