#pragma once
#include "VisibleGameObject.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"

class RedKrazy :
    public VisibleGameObject
    {
    public:
        RedKrazy();
        ~RedKrazy();
        void Draw(sf::RenderWindow& rw);
        void Update(float elapsedTime);
		void Dead();
        bool isDead();
    private:
        float _velocityX;
        float _velocityY;
        float _angle;
        float _elapsedTimeSinceStart;
        float _speed;
        std::string _path;
        int _health;
        float _timedead;
        bool _Dead;
		sf::FloatRect bounds;


        float LinearVelocityX(float angle);
        float LinearVelocityY(float angle);




    };
