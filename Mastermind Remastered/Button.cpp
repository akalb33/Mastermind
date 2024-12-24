#include "stdafx.h"
#include "Util.h"
#include "Button.h"
#include "Character.h"

Button::Button()
   : Character(typeid(Button))
   , mPressed(false)
{
   SetTexture(TextureManager::button);
   SetDisplayOrder(2);
}



Button::~Button()
{
}

void Button::Process(float deltaTime)
{
   if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
   {
      mPressed = isPosInBounds(GetScreen()->GetMouseViewPosition());
   }
   else if (sf::Touch::isDown(0))
   {
      mPressed = isPosInBounds(sf::Touch::getPosition(0));
   }
   else
   {
      mPressed = false;
   }
}

bool Button::isPressed() const
{
   return mPressed;
}