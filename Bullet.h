#pragma once
#include "VisibleGameObject.h"
#include "Player.h"
#include "Game.h"

class Bullet :
    public VisibleGameObject
    {
    public:
        Bullet();
        ~Bullet();
        void Draw(sf::RenderWindow& rw);
        void Update(float elapsedTime);
        void Shoot();
		void Shotgun();
        bool shoot;
		bool hit(sf::FloatRect rect);
    private:
        float _angle;
		float _rand;
        std::string _path;
        int _health;
        float LinearVelocityX(float angle);
        float LinearVelocityY(float angle);
    };
