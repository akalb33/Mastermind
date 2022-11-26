#pragma once

#include "Character.h"
#include "assert.h"
#include "Button.h"
#include "Shield.h"
#include "BoardType.h"

class Piece;

class Board : public Character
{
public:
   Board();
   virtual ~Board();
   virtual void Process(float deltaTime);
   
   void Init();

   Piece* GetHole(unsigned int row, unsigned int column) const;
   void SetHole(unsigned int row, unsigned int column, Piece& piece);
   void ClearHole(unsigned int row, unsigned int column);
   unsigned int GetCurrentRow() const;
   void SetCurrentRow(unsigned int row);
   static float GetX(unsigned int row, unsigned int column);
   static float GetY(unsigned int row);
   static void SetButton(Button* pButton) { mpButton = pButton; }
   // The following two functions return -1 if a valid row/column is not found
   static int GetColumn(float x);
   static int GetRow(float y);
   void GenerateCombination();
   unsigned int CheckForBlacks(char* const pCombination);
   unsigned int CheckForWhites(char* const pGuess);

   void SetShield(Shield* pShield)
   { 
      mpShield = pShield;
      //mpShield = Character::Resurrect<Shield>();
      assert(mpShield != 0);
      if (!BoardType::IsPlayerChoosingSolution())
      {
         mpShield->mX = 1017.0f;
         mpShield->mY = 140.0f;
      }
      else
      {
         mpShield->mX = -200.0f;
         mpShield->mY = -200.0f;
      }
   }

   bool GameOver() { return mGameOver; }
   void Reset();
private:
   Piece* mpHoles[11][4];
   unsigned int mCurrentRow;
   static Button* mpButton;
   char mCombination[4];
   Shield* mpShield;
   bool mGameOver;

   class ScorePositionInfo
   {
      public: 
         ScorePositionInfo()
            : mX(0.0f)
            , mY(0.0f)
            , mDisplayOrder(0)
         {
         }
         
         ~ScorePositionInfo()
         {
         }

         void Initialize(float x, float y, unsigned int displayOrder) 
         {
            mX = x;
            mY = y;
            mDisplayOrder = displayOrder;
         }
         float GetX() const { return mX; }
         float GetY() const { return mY; }
         unsigned int GetDisplayOrder() const { return mDisplayOrder; }
      private:
         float mX;
         float mY;
         unsigned int mDisplayOrder;
   };

   ScorePositionInfo mScorePosition[4];
};
