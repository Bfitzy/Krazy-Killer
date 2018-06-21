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
				_health -= player1->GetGun().damage;
				bool a = (_health < 15);
				bool b = (_health < 10);
				bool c = (_health < 5);
				Shift(a + b + c);
				if (_health < 1)
				{
					_dead = true;
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
