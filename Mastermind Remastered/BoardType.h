#pragma once


class BoardType
{
public:
   BoardType();
   static bool IsColor() { return mColor; }
   static void SetToColor(bool color) { mColor = color; }
   static bool IsPlayerChoosingSolution() { return mPlayerChoosingSolution; }
   static void SetToChooseSolution(bool choosingSolution) { mPlayerChoosingSolution = choosingSolution; }
private:
   static bool mColor;
   static bool mPlayerChoosingSolution;
};
