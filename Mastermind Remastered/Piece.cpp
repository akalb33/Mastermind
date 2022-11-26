#include "stdafx.h"
#include "Util.h"
#include "Piece.h"
#include "Character.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include <assert.h>
#include "BoardType.h"

bool Piece::mPieceSelected = false;
Board* Piece::mpBoard = 0;
float Piece::mRaisedScale;
float Piece::mDroppedScale;
const float Piece::mRaisedScaleColor = 2.4f;
const float Piece::mDroppedScaleColor = 1.8f;
const float Piece::mRaisedScaleLetter = 0.325f;
const float Piece::mDroppedScaleLetter = 0.25f;

Piece::Piece()
   : Character(typeid(Piece))
   , mPieceId('1')
   , mStage(available)
   , mOriginalX(0.0f)
   , mOriginalY(0.0f)
   , mOriginalDisplayOrder(0)
   , mInBoard(false)
{
   // BLUE - 1
   // RED - 2
   // GREEN - 3
   // YELLOW - 4
   // WHITE - 5
   // BlACK - 6
}

Piece::~Piece()
{
}

void Piece::Init(char pieceId,
                 float x,
                 float y,
                 ScaleStatus scaleStatus,
                 unsigned int displayOrder,
                 Stage stage,
                 bool inBoard)
{
   SetPieceId(pieceId);
   mX = x;
   mY = y;
   if (scaleStatus == dropped)
   {
      SetScaleToDropped();
   }
   else
   {
      SetScaleToRaised();
   }
   SetDisplayOrder(displayOrder);
   mStage = stage;
   mInBoard = inBoard;
}

void Piece::InitScaleLimits()
{
   if (BoardType::IsColor())
   {
      mRaisedScale = mRaisedScaleColor;
      mDroppedScale = mDroppedScaleColor;
   }
   else
   {
      mRaisedScale = mRaisedScaleLetter;
      mDroppedScale = mDroppedScaleLetter;
   }
}

void Piece::Process(float deltaTime)
{
   // Selected means that a piece is currently being held by the mouse, aka being moved or dragged in the moment.
   if(mStage == selected)
   {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
         sf::Vector2f mousePosition = GetScreen()->GetMouseViewPosition();
         float x = mousePosition.x;
         float y = mousePosition.y;
         mX = x - mMouseOffsetX;
         mY = y - mMouseOffsetY;
         if (mScale < mRaisedScale)
         {
            mScale += (mRaisedScale - mDroppedScale) * deltaTime / 0.1f;
            if(mScale > mRaisedScale)
            {
               mScale = mRaisedScale;
            }
         }
      }
      else
      {
         int column = Board::GetColumn(mX);
         int row = Board::GetRow(mY);
         Piece* pCurrentHole = mpBoard->GetHole(row, column);
         if (column != -1 && row == mpBoard->GetCurrentRow())
         {
            if (pCurrentHole != 0)
            {
               pCurrentHole->Kill();
            }
            Piece* pPiece = Character::Resurrect<Piece>();
            pPiece->Init(mPieceId, 
                         mpBoard->GetX(row, column), 
                         mpBoard->GetY(row), 
                         Piece::raised, 
                         20,
                         Piece::available, 
                         true);
            mpBoard->SetHole(row, column, *pPiece);
         }
         if(pCurrentHole != this)
         {
            if (!mInBoard)
            {
               mX = mOriginalX;
               mY = mOriginalY;
               SetDisplayOrder(mOriginalDisplayOrder);
            }
            else
            {
               Kill();
               if (Board::GetRow(mOriginalY) != row || Board::GetColumn(mOriginalX) != column)
               {
                  mpBoard->ClearHole(Board::GetRow(mOriginalY), Board::GetColumn(mOriginalX));
               }
            }
         }
         mStage = available;
         mPieceSelected = false;
      }
   }
   // Available is any piece that can be picked up and moved to another place.
   // Exhausted is any piece that is stuck or solidified in a row, it can no longer move and you would only find this in a row that has been used as a guess.
   else
   {
      if (BoardType::IsPlayerChoosingSolution())
      {
         mpBoard->SetCurrentRow(10);
      }
      if (mScale > mDroppedScale && !mpBoard->GameOver())
      {
         mScale -= (mRaisedScale - mDroppedScale) * deltaTime / 0.1f;
         if (mScale <= mDroppedScale)
         {
            mScale = mDroppedScale;
            if(mInBoard)
            {
               SetDisplayOrder(14 - mpBoard->GetCurrentRow());
            }
            else
            {
               SetDisplayOrder(mOriginalDisplayOrder);
            }
         }
      }
      if (!mpBoard->GameOver() && (mStage == available || mStage == exhausted))
      {
         if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mPieceSelected)
         {
            sf::Vector2f mousePosition = GetScreen()->GetMouseViewPosition();
            float x = mousePosition.x;
            float y = mousePosition.y; 
            // UNCOMMENT FOR DEBUG CLICK CODE
            //std::cout << "x: " << x << "\n";
            //std::cout << "y: " << y << "\n";

            if ((x < GetMaxX() && x > GetMinX()) && (y < GetMaxY() && y > GetMinY()))
            {
               Piece* pPiece = this;
               if (mStage == exhausted)
               {
                  pPiece = Character::Resurrect<Piece>();
                  pPiece->Init(mPieceId, mX, mY, dropped, 200, selected, true);
               }
               pPiece->mStage = selected;
               pPiece->mPieceSelected = true;
               pPiece->mMouseOffsetX = x - mX;
               pPiece->mMouseOffsetY = y - mY;
               pPiece->mOriginalX = mX;
               pPiece->mOriginalY = mY;
               pPiece->mOriginalDisplayOrder = mDisplayOrder;
               pPiece->SetDisplayOrder(200);
            }
         }
      }
   }
}

void Piece::SetPieceId(char pieceId)
{
   mPieceId = pieceId;
   switch (mPieceId)
   {
   case '1':
      SetTexture(TextureManager::blue);
      break;
   case '2':
      SetTexture(TextureManager::red);
      break;
   case '3':
      SetTexture(TextureManager::green);
      break;
   case '4':
      SetTexture(TextureManager::yellow);
      break;
   case '5':
      SetTexture(TextureManager::white);
      break;
   case '6':
      SetTexture(TextureManager::black);
      break;
   case 'A':
      SetTexture(TextureManager::A);
      break;
   case 'B':
      SetTexture(TextureManager::B);
      break;
   case 'C':
      SetTexture(TextureManager::C);
      break;
   case 'D':
      SetTexture(TextureManager::D);
      break;
   case 'E':
      SetTexture(TextureManager::E);
      break;
   case 'F':
      SetTexture(TextureManager::F);
      break;
   case 'G':
      SetTexture(TextureManager::G);
      break;
   case 'H':
      SetTexture(TextureManager::H);
      break;
   case 'I':
      SetTexture(TextureManager::I);
      break;
   case 'J':
      SetTexture(TextureManager::J);
      break;
   case 'K':
      SetTexture(TextureManager::K);
      break;
   case 'L':
      SetTexture(TextureManager::L);
      break;
   case 'M':
      SetTexture(TextureManager::M);
      break;
   case 'N':
      SetTexture(TextureManager::N);
      break;
   case 'O':
      SetTexture(TextureManager::O);
      break;
   case 'P':
      SetTexture(TextureManager::P);
      break;
   case 'Q':
      SetTexture(TextureManager::Q);
      break;
   case 'R':
      SetTexture(TextureManager::R);
      break;
   case 'S':
      SetTexture(TextureManager::S);
      break;
   case 'T':
      SetTexture(TextureManager::T);
      break;
   case 'U':
      SetTexture(TextureManager::U);
      break;
   case 'V':
      SetTexture(TextureManager::V);
      break;
   case 'W':
      SetTexture(TextureManager::W);
      break;
   case 'X':
      SetTexture(TextureManager::X);
      break;
   case 'Y':
      SetTexture(TextureManager::Y);
      break;
   case 'Z':
      SetTexture(TextureManager::Z);
      break;

   default:
      assert(true);
   }

}

void Piece::SetOriginalX(float x)
{
   mOriginalX = x;
}

void Piece::SetOriginalY(float y)
{
   mOriginalY = y;
}
