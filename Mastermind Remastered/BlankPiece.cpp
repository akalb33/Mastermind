#include "stdafx.h"
#include "Util.h"
#include "Shield.h"
#include "Character.h"
#include "BlankPiece.h"

BlankPiece::BlankPiece()
   : Character(typeid(BlankPiece))

{
   SetTexture(TextureManager::blank);
   SetDisplayOrder(3);
   mScale = 0.25f;
}

BlankPiece::~BlankPiece()
{
}

void BlankPiece::Process(float deltaTime)
{
   ApplyInertia(deltaTime);
}