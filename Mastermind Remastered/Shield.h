#pragma once

#include "Character.h"

class Shield : public Character
{
public:
   Shield();
   virtual ~Shield();
   virtual void Process(float deltaTime);
public:

private:
};
