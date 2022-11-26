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
      sf::Vector2f mousePosition = GetScreen()->GetMouseViewPosition();
      float x = mousePosition.x;
      float y = mousePosition.y;
      if ((x < GetMaxX() && x > GetMinX()) && (y < GetMaxY() && y > GetMinY()))
      {
         mPressed = true;
      }
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