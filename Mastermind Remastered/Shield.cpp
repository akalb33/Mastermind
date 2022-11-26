#include "stdafx.h"
#include "Util.h"
#include "Shield.h"
#include "Character.h"
#include "BoardType.h"

Shield::Shield()
   : Character(typeid(Shield))

{
   SetTexture(TextureManager::shield);
   SetDisplayOrder(15);
   mScale = 1.8f;
}

Shield::~Shield()
{
}

void Shield::Process(float deltaTime)
{
   ApplyInertia(deltaTime);
}