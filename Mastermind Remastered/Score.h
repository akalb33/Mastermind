#pragma once

#include "Character.h"

class Score : public Character
{
public:
   Score();
   virtual ~Score();
   virtual void Process(float deltaTime);
   void SetType(unsigned int type);
   void SetDestination(float x, float y) { mDestinationX = x; mDestinationY = y;}
   void SetToBigScale() { mScale = mBigScale; }
   void SetScoreDisplayOrder(unsigned int displayOrder) { mScoreDisplayOrder = displayOrder; }
private:
   float mDestinationX;
   float mDestinationY;
   const float mBigScale = 3.2f;
   float mSmallScale;
   unsigned int mScoreDisplayOrder;
};
