#pragma once
#include "VisibleGameObject.h"

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
		void addGore();
    private:
        float _velocityX;
        float _velocityY;
        float _angle;
        float _elapsedTimeSinceStart;
        float _speed;
        std::string _path;
        int _health;
        float _timedead;
		sf::FloatRect bounds;
		bool _dead;

        //float LinearVelocityX(float angle);
        //float LinearVelocityY(float angle);




    };
