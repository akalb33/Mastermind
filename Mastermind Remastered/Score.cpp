#include "stdafx.h"
#include "Util.h"
#include "Score.h"
#include "assert.h"
#include "Character.h"

Score::Score()
   : Character(typeid(Score))
   , mDestinationX(0.0f)
   , mDestinationY(0.0f)
   , mScoreDisplayOrder(0)
{
   SetTexture(TextureManager::blackScore);
}

// Type 0 = black
// Type 1 = white


Score::~Score()
{
}

void Score::Process(float deltaTime)
{
   if (mScale > mBigScale - 0.01f)
   {
      if (MoveTowardLocation(mDestinationX, mDestinationY, 500.0f, deltaTime))
      {
         mScale = mBigScale - 0.02f;
      }
   }
   else if(mScale > mSmallScale)
   {
      mScale -= (mBigScale - mSmallScale) * deltaTime / 1.0f;
   }
   else
   {
      SetDisplayOrder(mScoreDisplayOrder);
   }
}

void Score::SetType(unsigned int type)
{
   switch (type)
   {
   case 0:
      SetTexture(TextureManager::blackScore);
      mSmallScale = 1.8f;
      break;
   case 1:
      SetTexture(TextureManager::whiteScore);
      mSmallScale = 1.6f;
      break;
   default:
      assert(true);
      break;
   }
}
