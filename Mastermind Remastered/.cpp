#include "stdafx.h"
#include "Util.h"
#include "Shield.h"
#include "Character.h"
#include "BoardType.h"

Shield::Shield()
   : Character(typeid(Shield))

{
   SetDisplayOrder(15);
   mScale = 1.8f;
}

Shield::~Shield()
{
}

void Shield::Process(float deltaTime)
{
   if (BoardType::IsColor())
   {
      SetTexture(TextureManager::shield);
   }
   else
   {
      SetTexture(TextureManager::wordTray);
   }
   ApplyInertia(deltaTime);
}