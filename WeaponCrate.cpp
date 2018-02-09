#include "WeaponCrate.h"
#include "Game.h"
#include <cstdlib>
#include <cmath>



WeaponCrate::WeaponCrate()
{
    showing=false;
    timeshowing=0;
    timesinceshown=0;
    SetPosition(rand()%400 + 40, rand()%400 +40);
    GetSprite().setOrigin(14,15);
    GetSprite().scale(std::sqrt(2),std::sqrt(2));
    Load("sprites/5.png");

}
WeaponCrate::~WeaponCrate()
{
}
void WeaponCrate::Update(float elapsedTime)
{

    if(showing==false) timesinceshown += elapsedTime;
    if(timesinceshown>=10)
    {
        //do{
            SetPosition((rand()%420 + 260), (rand()%665+55));
        //}while();
        showing=true;
        timesinceshown=0;
    }
    if (showing)
    {
    timeshowing+=elapsedTime;

    if(timeshowing>=17)
    {
        showing=false;
        timeshowing=0;
    }
    if(TouchingPlayer())
    {
        showing=false;
        timeshowing=0;
    }
}

}
void WeaponCrate::Draw(sf::RenderWindow & rw)
{
    if(showing) VisibleGameObject::Draw(rw);
}
bool WeaponCrate::TouchingPlayer()
{
Player* player = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player1"));
  bool touch = player->GetBoundingRect().intersects(GetBoundingRect());
  if(touch) player->NewGun();
  return touch;
}
