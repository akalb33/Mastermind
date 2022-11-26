#pragma once
#include "Screen.h"
#include "Character.h"
#include "Menu.h"
#include "TextureManager.h"

class Game : public IMenuCallBack
{
public:
   Game();
   ~Game();

private:
   void SetMaxCharacters();
   virtual void UpdateMenuOptions();
   void StartNewWordGame();
   void StartNewColorGame();


   Screen mScreen;
   TextureManager mTextureManager;
   SoundManager mSoundManager;
   Menu mMenu;

   float mLevelSpeed;
   int mLives;
};
