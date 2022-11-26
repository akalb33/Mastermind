#include "stdafx.h"
#include "Util.h"
#include "AnswerTray.h"
#include "Character.h"

AnswerTray::AnswerTray()
   : Character(typeid(AnswerTray))

{
   SetTexture(TextureManager::wordTray);
   SetDisplayOrder(2);
   mScale = 1.0f;
}

AnswerTray::~AnswerTray()
{
}

void AnswerTray::Process(float deltaTime)
{
   ApplyInertia(deltaTime);
}