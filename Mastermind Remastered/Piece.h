#pragma once

#include "Character.h"
#include "Board.h"
#include "Button.h"

class Piece : public Character
{
public:
   Piece();
   virtual ~Piece();
   enum ScaleStatus
   {
      dropped,
      raised
   };

   enum Stage
   {
      exhausted,
      available,
      selected
   };

   void Init(char pieceId, 
             float x, 
             float y, 
             ScaleStatus scaleStatus, 
             unsigned int displayOrder,
             Stage stage,
             bool inBoard);
   static void InitScaleLimits();
   virtual void Process(float deltaTime);

   char GetPieceId() { return mPieceId; }
   void SetPieceId(char pieceId);

   void SetOriginalX(float x);
   void SetOriginalY(float y);

   void MakeExhausted() { mStage = exhausted; }

   static void SetBoard(Board* pBoard) { mpBoard = pBoard; }
   static bool GetPieceSelected() { return mPieceSelected; }

   void SetScaleToDropped() { mScale = mDroppedScale; }
   void SetScaleToRaised() { mScale = mRaisedScale; }
private:
   char mPieceId;
   Stage mStage;

   float mOriginalX;
   float mOriginalY;
   unsigned int mOriginalDisplayOrder;
   float mMouseOffsetX;
   float mMouseOffsetY;
   bool mInBoard;

   static bool mPieceSelected;
   static Board* mpBoard;
   static Button* mpButton;

   static float mRaisedScale;
   static float mDroppedScale;
   static const float mRaisedScaleColor;
   static const float mDroppedScaleColor;
   static const float mRaisedScaleLetter;
   static const float mDroppedScaleLetter;
};


