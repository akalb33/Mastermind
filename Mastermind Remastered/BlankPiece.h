#pragma once

#include "Character.h"

class BlankPiece : public Character
{
public:
   BlankPiece();
   virtual ~BlankPiece();
   virtual void Process(float deltaTime);
public:

private:
};
