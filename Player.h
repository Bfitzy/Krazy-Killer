#pragma once
#include "Bullet.h"
#include "VisibleGameObject.h"
    struct Gun
{
public:
    int damage;
    int delay;
    std::string _path;
    std::string _path2;
    std::string _audio;
    std::string _proj;
    int recoil;
	int spread;
};

class Player :
    public VisibleGameObject
    {
    public:
        Player();
        ~Player();

        enum Gunenum {Pistol, Magnum, Uzi, Laserpistol,\
        Shotgun, SMG, LaserRifle,\
        RocketLauncher, BeamRifle, Minigun,\
        RadioactiveShotgun, SniperRifle, Lightsaber, Knife};
        struct Gun pistol;
        struct Gun magnum;
        struct Gun uzi;
        struct Gun laserpistol;
        struct Gun shotgun;
        struct Gun smg;
        struct Gun laserrifle;
        struct Gun rocketlauncher;
        struct Gun beamrifle;
        struct Gun minigun;
        struct Gun radioactiveshotgun;
        struct Gun sniperrifle;
        struct Gun lightsaber;
        struct Gun knife;
        void Update(float elapsedTime);
        void Draw(sf::RenderWindow& rw);
        void NewGun();
        Gun GetGun();
        Gun AddGun(int damage, int delay, std::string _audio, int recoil, int spread);
        float GetVelocityX() const;
        float GetVelocityY() const;
        bool NX();
		bool NY();
        int GetHealth();
        void Damage(int health);
        float GetAngle();
		int Getproj();
        sf::Vector2f GetVectoMouse();


    private:
        sf::Vector2i _mouse;
        sf::Vector2f _tomouse;

        static Gunenum _gun;
        float _angle;
        bool _nx;
		bool _ny;
        float _velocityX;
        float _maxVelocityX;
        float _velocityY;
        float _maxVelocityY;
        int _health;
        float _delay;
        bool _shoot;
        float distmy;
        float distmx;
        float distm;
        float _time;

    };



