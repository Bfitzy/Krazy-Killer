#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include <cstdlib>
#include <cmath>

Bullet::Bullet()
{
    GetSprite().scale(std::sqrt(2),std::sqrt(2));
    GetSprite().setOrigin(0,0);
	Load("sprites/1.png");
	Load("sprites/3.png");
	Load("sprites/2.png");
	Load("sprites/4.png");
	Load("sprites/1.png");
	Load("sprites/3.png");
}
Bullet::~Bullet()
{

}

void Bullet::Draw(sf::RenderWindow & rw)
{
    if(shoot)
    {
        shoot = false;
        VisibleGameObject::Draw(rw);
    }

}void Bullet::Shoot()
{
    Player* player = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player1"));
	Shift(player->Getproj());
    _angle = player->GetAngle();
	int spread = player->GetGun().spread;
    _rand = (rand() % spread - spread / 2);
	GetSprite().setRotation(_angle+=_rand);
    GetSprite().setPosition(player->GetPosition());
    GetSprite().move(player->GetVectoMouse().x * 13, player->GetVectoMouse().y * 13);
    shoot = true;
}
void Bullet::Shotgun()
{
	
}
void Bullet::Update(float elapsedTime)
{

}
bool Bullet::hit(sf::FloatRect rect)
{
	Player* player = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player1"));

	float x = GetSprite().getPosition().x;
	float y = GetSprite().getPosition().y;
	float mx = player->GetVectoMouse().x;
	float my = player->GetVectoMouse().y;
	float p_angle = player->GetAngle();
	
	float dx = (cosf(_angle / 180 * pi)); // cos (p_angle + _rand)
	float dy = (sinf(_angle / 180 * pi));//(my * cosf(_rand) + mx *sinf(_rand));
	//if (player->NX()) dx = -dx;
	//if (player->NY()) dy = -dy;
	for (int i=0;i<100;i++)
	{
		if (rect.contains(x, y)) return true;
		x += dx*5;
		y += dy*5;
	}
	return false;
}