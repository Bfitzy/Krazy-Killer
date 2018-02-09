#include "RedKrazy.h"
#include "Game.h"
#include "Player.h"
#include <cmath>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "Bullet.h"
RedKrazy::RedKrazy() : _health(18)
{
    _Dead = false;
    _timedead = 0;


    Load("sprites/63.png");
	Load("sprites/64.png");
	Load("sprites/65.png");
	Load("sprites/66.png");
	Load("sprites/67.png");
	Load("sprites/68.png");
	Load("sprites/69.png");
	Shift(0);
    GetSprite().setOrigin(14,15);
    GetSprite().scale(std::sqrt(2),std::sqrt(2));
    SetPosition(rand()%100 + 10, rand()%100 +10);
	sf::FloatRect gbounds = GetBoundingRect();
	bounds = sf::FloatRect(GetSprite().getPosition().x, GetSprite().getPosition().y, GetBoundingRect().height, GetBoundingRect().width);
}
RedKrazy::~RedKrazy()
{

}
void RedKrazy::Update(float elapsedTime)
{
	if (_Dead) 
	{
		_timedead += elapsedTime; 
		if (_timedead >= 5)
		{
			_timedead = 0;
			_Dead = false;
			SetPosition(rand() % 400 + 40, rand() % 400 + 40);
			_health = 18;
			Shift(0);
		}
	}
	else {
	
	Player* player1 = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player1"));
	float angle = 0;
	if ((player1->GetPosition().x - GetPosition().x) > 0) angle = std::atan((player1->GetPosition().y - GetPosition().y) / (player1->GetPosition().x - GetPosition().x)) / 3.14159265359f * 180;
	if ((player1->GetPosition().x - GetPosition().x) < 0) angle = std::atan((player1->GetPosition().y - GetPosition().y) / (player1->GetPosition().x - GetPosition().x)) / 3.14159265359f * 180 + 180;
	GetSprite().setRotation(angle);
	float distx = (player1->GetPosition().x - GetPosition().x);
	float disty = (player1->GetPosition().y - GetPosition().y);
	float dist = std::sqrt((distx * distx) + (disty * disty));
	GetSprite().move(distx / dist, disty / dist);
	Bullet* shot = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("shot"));
	Bullet* s1 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s1"));
	Bullet* s2 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s2"));
	Bullet* s3 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s3"));
	Bullet* s4 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s4"));
	Bullet* s5 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s5"));
	Bullet* s6 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s6"));
	Bullet* _shots[7] = {shot, s1, s2, s3, s4, s5, s6};
	for (int i=0; i<7; i++)
	{
		if (_shots[i]->hit(GetBoundingRect()) && _shots[i]->shoot)
		{
			_health -= player1->GetGun().damage;
			bool a = (_health < 15);
			bool b = (_health < 10);
			bool c = (_health < 5);
			Shift(a + b + c);
			if (_health < 1) 
			{
				_Dead = true;
				if (_health < -4)
				{
					Shift(6);
				}
				else if (_health<-1)
				{
					Shift(5);
				}
				else Shift(4);

			}
		}
	}
}
}
void RedKrazy::Draw(sf::RenderWindow & rw)
{
    VisibleGameObject::Draw(rw);
}
bool RedKrazy::isDead()
{
    return _Dead;
}
void RedKrazy::Dead()
{

}