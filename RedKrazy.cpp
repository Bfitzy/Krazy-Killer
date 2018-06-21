#include "RedKrazy.h"
#include "Game.h"
#include <cmath>
#include <cstdlib>
#include "SFML/Graphics.hpp"
RedKrazy::RedKrazy() : _health(18)
{
    _dead = false;
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
	if (_dead)
	{
		_timedead += elapsedTime;
		if (_timedead >= 5)
		{
			_timedead = 0;
			_dead = false;
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
		Bullet* _shots[7] = { shot, s1, s2, s3, s4, s5, s6 };
		for (int i = 0; i<7; i++)
		{
			if (_shots[i]->hit(GetBoundingRect()) && _shots[i]->shoot)
			{
				addGore();
				_health -= player1->GetGun().damage;
				bool a = (_health < 15);
				bool b = (_health < 10);
				bool c = (_health < 5);
				Shift(a + b + c);
				if (_health < 1 && !_dead)
				{
					_dead = true;
					Dead();
					if (_health < -4)
					{
						Game::Paint("sprites/69.png", GetPosition().x, GetPosition().y);
					}
					else if (_health<-1)
					{
						Game::Paint("sprites/68.png", GetPosition().x, GetPosition().y);
					}
					else
					{
						Game::Paint("sprites/67.png", GetPosition().x, GetPosition().y);
					}
				} 
			}
		}
	}
}
void RedKrazy::Draw(sf::RenderWindow & rw)
{
    if(!_dead){VisibleGameObject::Draw(rw);}
	
}
bool RedKrazy::isDead()
{
	if (_health < 1 && !_dead)
	{
		_dead = true;
		return true;
	}
	return false;
}
void RedKrazy::Dead()
{
	
}
void RedKrazy::addGore()
{
	switch (rand() % 15)
	{
	case 1:
		Game::Paint("sprites/103.png", GetPosition().x, GetPosition().y);
		break;
	case 2:
		Game::Paint("sprites/104.png", GetPosition().x, GetPosition().y);
		break;
	case 3:
		Game::Paint("sprites/105.png", GetPosition().x, GetPosition().y);
		break;
	case 4:
		Game::Paint("sprites/106.png", GetPosition().x, GetPosition().y);
		break;
	case 5:
		Game::Paint("sprites/107.png", GetPosition().x, GetPosition().y);
		break;
	case 6:
		Game::Paint("sprites/108.png", GetPosition().x, GetPosition().y);
		break;
	case 7:
		Game::Paint("sprites/109.png", GetPosition().x, GetPosition().y);
		break;
	case 8:
		Game::Paint("sprites/110.png", GetPosition().x, GetPosition().y);
		break;
	case 9:
		Game::Paint("sprites/110.png", GetPosition().x, GetPosition().y);
		break;
	case 10:
		Game::Paint("sprites/111.png", GetPosition().x, GetPosition().y);
		break;
	case 11:
		Game::Paint("sprites/112.png", GetPosition().x, GetPosition().y);
		break;
	case 12:
		Game::Paint("sprites/113.png", GetPosition().x, GetPosition().y);
		break;
	case 13:
		Game::Paint("sprites/114.png", GetPosition().x, GetPosition().y);
		break;
	case 14:
		Game::Paint("sprites/115.png", GetPosition().x, GetPosition().y);
		break;/*
	case 15:
		Game::Paint("sprites/107.png", GetPosition().x, GetPosition().y);
		break;
	case 16:
		Game::Paint("sprites/108.png", GetPosition().x, GetPosition().y);
		break;
	case 17:
		Game::Paint("sprites/109.png", GetPosition().x, GetPosition().y);
		break;
	case 18:
		Game::Paint("sprites/110.png", GetPosition().x, GetPosition().y);
		break;
	case 19:
		Game::Paint("sprites/110.png", GetPosition().x, GetPosition().y);
		break; */
	}
	//Game::Paint("sprites/67.png", GetPosition().x, GetPosition().y);
}