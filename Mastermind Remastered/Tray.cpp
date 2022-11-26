#include "stdafx.h"
#include "Util.h"
#include "Tray.h"
#include "Character.h"

Tray::Tray()
   : Character(typeid(Tray))
{
   SetTexture(TextureManager::tray);
   SetDisplayOrder(2);
}

Tray::~Tray()
{
}

void Tray::Process(float deltaTime)
{
  
}