#include "stdafx.h"
#include "Util.h"
#include "Board.h"
#include "Score.h"
#include "Piece.h"
#include "BoardType.h"
#include "Character.h"
#include "BlankPiece.h"
#include <cmath>
#include <iostream>
#include <cstring>
#include "WordList.h"

Button* Board::mpButton = 0;

Board::Board()
   : Character(typeid(Board))
   , mCurrentRow(0)
   , mpShield(0)
{
   SetTexture(TextureManager::board);
   SetDisplayOrder(2);
   mScale = 1.8f;
}



Board::~Board()
{
}

void Board::Process(float deltaTime)
{
   if ((mpButton->isPressed() && mCurrentRow != 10 && !mGameOver) || (mpButton->isPressed() && BoardType::IsPlayerChoosingSolution()))
   {
      bool rowFilled = true;
      for(int i = 0; i < 4 && rowFilled; i++)
      {
         if(GetHole(mCurrentRow, i) == 0 || Piece::GetPieceSelected() == true)
            rowFilled = false;
      }
      if (rowFilled)
      {
         char guess[4];
         for (int o = 0; o < 4; o++)
         {
            GetHole(mCurrentRow, o)->MakeExhausted();
            guess[o] = GetHole(mCurrentRow, o)->GetPieceId();
            if (BoardType::IsPlayerChoosingSolution())
            {
               mCombination[o] = guess[o];
               GetHole(mCurrentRow, o)->Kill();
               ClearHole(mCurrentRow, o);
               if (!BoardType::IsColor())
               {
                  BlankPiece* pBlankPiece = Character::Resurrect<BlankPiece>();
                  pBlankPiece->mX = GetX(mCurrentRow, o);
                  pBlankPiece->mY = GetY(mCurrentRow);
               }
            }
         }
         if (BoardType::IsPlayerChoosingSolution())
         {
            BoardType::SetToChooseSolution(false);
            mCurrentRow = 0;
            if (BoardType::IsColor())
            {
               SetShield(mpShield);
            }
         }
         else
         {
            for (unsigned int i = 0; i < CheckForBlacks(guess) + CheckForWhites(guess); i++)
            {
               Score* pScore = Character::Resurrect<Score>();
               assert(pScore != 0);
               pScore->SetType(i >= CheckForBlacks(guess));
               float additionalY = 0.0f;
               if (!BoardType::IsColor() && mCurrentRow > 6)
               {
                  additionalY = mCurrentRow * 1.15f;
               }
               pScore->SetDestination(mScorePosition[i].GetX(),
                                      mScorePosition[i].GetY() + GetY(mCurrentRow) + additionalY);
               pScore->mX = mScorePosition[i].GetX() + 100.0f;
               pScore->mY = -500.0f * i;
               pScore->SetDisplayOrder(160 + mScorePosition[i].GetDisplayOrder());
               pScore->SetScoreDisplayOrder(150 + mScorePosition[i].GetDisplayOrder() - mCurrentRow * 4);
               pScore->SetToBigScale();
            }
            if (CheckForBlacks(guess) == 4 || mCurrentRow == 9)
            {
               if(!BoardType::IsColor())
               {
                  BlankPiece* pBlank = FindCharacter<BlankPiece>(alive);
                  while (pBlank != 0)
                  {
                     pBlank->Kill();
                     pBlank = FindCharacter<BlankPiece>(alive);
                  }
               }
               else
               {
                  mpShield->mVelocityY = -860.0f;
               }

               for (int i = 0; i < 4; i++)
               {
                  Piece* pPiece = Character::Resurrect<Piece>();
                  assert(pPiece != 0);
                  pPiece->Init(mCombination[i],
                               GetX(10, i), 
                               GetY(10),
                               Piece::dropped, 
                               3, 
                               Piece::exhausted, 
                               true);
               }
               mGameOver = true;
            }
            else
            {
               mCurrentRow++;
            }
         }
      }
   }
}

void Board::Init()
{
   float leftMostScoreX = 819.4f;
   float rightMostScoreX = 854.3f;
   float verticalScoreOffset = 16.0f;

   if (!BoardType::IsColor())
   {
      leftMostScoreX = 782.6f;
      rightMostScoreX = 815.4f;
      verticalScoreOffset = 12.0f;
   }

   mScorePosition[0].Initialize(leftMostScoreX, -verticalScoreOffset, 16);
   mScorePosition[1].Initialize(rightMostScoreX, -verticalScoreOffset, 17);
   mScorePosition[2].Initialize(leftMostScoreX, verticalScoreOffset, 18);
   mScorePosition[3].Initialize(rightMostScoreX, verticalScoreOffset, 19);
}

Piece* Board::GetHole(unsigned int row, unsigned int column) const
{
   return mpHoles[row][column];
}


void Board::SetHole(unsigned int row, unsigned int column, Piece& piece)
{
   mpHoles[row][column] = &piece;
}

void Board::ClearHole(unsigned int row, unsigned int column)
{
   mpHoles[row][column] = 0;
}

unsigned int Board::GetCurrentRow() const
{
   return mCurrentRow;
}

void Board::SetCurrentRow(unsigned int row)
{
   mCurrentRow = row;
}

float Board::GetX(unsigned int row, unsigned int column)
{
   float x = 0.0f;
   if (BoardType::IsColor())
   {
      x = 922.0f + column * 63.0f;
      if (column == 2 && row > 1)
      {
         x += 2.0f;
      }
      if (column == 3)
      {
         x += 2.0f;
      }
   }
   else
   {
      x = 898.0f + column * 61.0f;
      if (column == 2)
      {
         x -= 0.5f * row;
      }
      else if (column == 3)
      {
         x -= 0.75f * row;
      }
      else if (row == 10)
      {
         
         x -= 5.0f;
      }
      x += Util::RandomFloat(-1.25f, 1.25f);
      
   }
   return x;
}

float Board::GetY(unsigned int row)
{
   float y = 0.0f;
   if (BoardType::IsColor())
   {
      if (row == 10)
      {
         y = 146.0f;
      }
      else
      {
         y = 916.0f + row * -72.56f;
      }
   }
   else
   {
      if (row == 10)
      {
         y = 60.0f;
      }
      else
      {
         y = 838.0f + row * -54.0f;
      }
   }
   return y;
}

int Board::GetColumn(float x)
{
   int column = -1;
   for (int columnNumber = 0; columnNumber < 4; columnNumber++)
   {
      if(std::abs(x - GetX(5, columnNumber)) < 25.0f)
      {
         column = columnNumber;
      }
   }
   return column;
}

int Board::GetRow(float y)
{
   int row = -1;
   for(int rowNumber = 0; rowNumber < 11; rowNumber++)
   {
      if (std::abs(y - GetY(rowNumber)) < 25.0f)
      {
         row = rowNumber;
      }
   }
   return row;
}

void Board::GenerateCombination()
{
   if(BoardType::IsColor())
   {
      for (int i = 0; i < 4; i++)
      {
         mCombination[i] = static_cast<char>(Util::RandomInteger('1', '6'));
      }
   }
   else
   {
      std::string combination = WordList::GetWord();

      for (int i = 0; i < 4; i++)
      {
         mCombination[i] = combination.at(i);
      }
   }
}

unsigned int Board::CheckForBlacks(char* const pCombination)
{
   unsigned int blacks = 0;
   for (int i = 0; i < 4; i++)
   {
      if (pCombination[i] == mCombination[i])
      {
         blacks++;
      }
   }
   return blacks;
}

unsigned int Board::CheckForWhites(char* const pGuess)
{
   unsigned int whites = 0;
   char guess[4];
   char answer[4];
   for (unsigned int i = 0; i < sizeof(guess); i++)
   {
      guess[i] = pGuess[i];
      answer[i] = mCombination[i];
      if (guess[i] == answer[i])
      {
         guess[i] = 0;
         answer[i]  = 0;
      }
   }

   for (unsigned int i = 0; i < 4; i++)
   {
      if (guess[i] != 0)
      {
         bool done = false;
         for (unsigned int o = 0; o < 4 && !done; o++)
         {
            if (o != i)
            {
               if (guess[i] == answer[o])
               {
                  whites++;
                  answer[o] = 0;
                  done = true;
               }
            }
         }
      }
   }
   return whites;
}

void Board::Reset()
{
   mCurrentRow = 0;
   mGameOver = false;
   for (unsigned int i = 0; i < 4; i++)
   {
      for (unsigned int j = 0; j < 12; j++)
      {
         ClearHole(i, j);
      }
   }
}