#include "KrazyAI.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <cmath>
#include "GameObjectManager.h"
#include "Player.h"
#include "VisibleGameObject.h"

KrazyAI::KrazyAI()
{
Load(_path);
GetSprite().setOrigin(GetSprite().getGlobalBounds().width/2, GetSprite().getGlobalBounds().height/2);
}
KrazyAI::~KrazyAI()
{
}
void KrazyAI::Update(float elapsedTime)
{

}
float KrazyAI::LinearVelocityX(float angle)
{
  angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::cos( angle * ( 3.1415926 / 180.0f ));
}

float KrazyAI::LinearVelocityY(float angle)
{
  angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::sin( angle * ( 3.1415926 / 180.0f ));
}
