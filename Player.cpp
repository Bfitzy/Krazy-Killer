#include "Player.h"
#include "Game.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Bullet.h"
#include "ServiceLocator.h"
Player::Player() :
    _velocityX(0),
    _maxVelocityX(600.0f), _velocityY(0),
    _maxVelocityY(600.0f), _health(20), _delay(0)
{
    _gun = Pistol;
	Load("sprites/27.png");
	Load("sprites/28.png");
	Load("sprites/51.png");
	Load("sprites/52.png");
	Load("sprites/53.png");
	Load("sprites/54.png");
	Load("sprites/61.png");
	Load("sprites/62.png");
	Load("sprites/29.png");
	Load("sprites/30.png");
    pistol = AddGun(3,30,"sprites/0.ogg",1,4);
    magnum = AddGun(5,50,"sprites/4.ogg",5,4);
    uzi = AddGun(1,10,"sprites/2.ogg",1,10);
    laserpistol = AddGun(2,20,"sprites/3.ogg",0,1);
    shotgun = AddGun(2,50,"sprites/5.ogg",10,20);
    _shoot = false;
    GetSprite().setOrigin(18,11);
    GetSprite().scale(std::sqrt(2),std::sqrt(2));


}
Player::~Player()
{
}
void Player::Draw(sf::RenderWindow & rw)
{

    VisibleGameObject::Draw(rw);
}

float Player:: GetVelocityX() const
{
    return _velocityX;
}
float Player::GetVelocityY() const
{
    return _velocityY;
}

void Player::Update(float elapsedTime)
{
    _time+=elapsedTime;
    if((_delay == 2))
    {
		Shift(_gun * 2);
    }

    _delay++;
    if(_shoot)
    {
        _shoot = false;
    }
    _mouse = sf::Mouse::getPosition(Game::GetWindow());
    _angle = atan((_mouse.y - GetPosition().y)/(_mouse.x - GetPosition().x))/pi*180;
    distmx = (_mouse.x-GetPosition().x);
    distmy = (_mouse.y-GetPosition().y);
    distm = std::sqrt((distmx*distmx)+ (distmy*distmy));
    _tomouse = sf::Vector2f(distmx/distm, distmy/distm);
    if((_mouse.x-GetPosition().x)>0)
    {
        _nx=false;
        GetSprite().setRotation(_angle);
    }
    if((_mouse.x-GetPosition().x)<0)
    {
        GetSprite().setRotation(_angle += 180);
        _nx = true;
    }
	if ((_mouse.y - GetPosition().y) > 0) _ny = false;
	if ((_mouse.y - GetPosition().y) < 0) _ny = true;



    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

    if(_delay>=GetGun().delay)
    {
		if (_gun != Shotgun) 
		{
			Bullet* shot = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("shot"));
			ServiceLocator::GetAudio()->PlaySound(GetGun()._audio);
			shot->Shoot();
			Shift(_gun * 2 + 1);
		}
		else
		{
			Bullet* shot = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("shot"));
			Bullet* s1 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s1"));
			Bullet* s2 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s2"));
			Bullet* s3 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s3"));
			Bullet* s4 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s4"));
			Bullet* s5 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s5"));
			Bullet* s6 = dynamic_cast<Bullet*>(Game::GetGameObjectManager().Get("s6"));
			ServiceLocator::GetAudio()->PlaySound(GetGun()._audio);
			shot->Shoot();
			s1->Shoot();
			s2->Shoot();
			s3->Shoot();
			s4->Shoot();
			s5->Shoot();
			s6->Shoot();
			Shift(_gun * 2 + 1);

		}
    _shoot = true;
    _delay = 0;
    }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _velocityX-= 100.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _velocityX+= 100.0f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _velocityY+= 100.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _velocityY-= 100.0f;
    }

    if(_velocityX > _maxVelocityX)
        _velocityX = _maxVelocityX;

    if(_velocityX < -_maxVelocityX)
        _velocityX = -_maxVelocityX;

    if(_velocityY > _maxVelocityY)
        _velocityY = _maxVelocityY;

    if(_velocityY < -_maxVelocityY)
        _velocityY = -_maxVelocityY;

    sf::Vector2f pos = this->GetPosition();

    if(pos.x  < 18)
    {
        _velocityX = 18; // Bounce by current velocity in opposite direction
    }
    if(pos.x > (942))
    {
        _velocityX = -18; // Bounce by current velocity in opposite direction
    }

    if(pos.y  < 18)
    {
        _velocityY=18; // Bounce by current velocity in opposite direction
    }
    if(pos.y > (702))
    {
        _velocityY = -18; // Bounce by current velocity in opposite direction
    }



    GetSprite().move(_velocityX * elapsedTime, _velocityY * elapsedTime);
    _velocityX=0;
    _velocityY=0;
}
int Player::GetHealth()
{
    return _health;
}
Player::Gunenum Player::_gun = Pistol;
float Player::GetAngle()
{
	return _angle; // +(rand() % GetGun().spread * 2) - GetGun().spread + 180;
}

bool Player::NX() //Is the x distance negative?
{
    return _nx;
}
bool Player::NY()
{
	return _ny;
}
sf::Vector2f Player::GetVectoMouse()
{
return _tomouse;
}
void Player::NewGun()
{//8
//_gun = (Gunenum)(rand()%8+4);
_gun = (Gunenum) (rand()%4+1);
Shift(_gun * 2);
Crosshair* cross = dynamic_cast<Crosshair*>(Game::GetGameObjectManager().Get("crosshair"));
if(_gun == Pistol|| _gun == Laserpistol|| _gun == Magnum|| _gun == Uzi)
{
	cross->Switch("sprites/260.png");
}else if (_gun == LaserRifle)
{
	cross->Switch("sprites/264.png");
}else if (_gun == Shotgun)
{
	cross->Switch("sprites/262.png");
}else if (_gun == SMG)
{
	cross->Switch("sprites/261.png");
} else if (_gun == Shotgun)
{
	cross->Switch("sprites/262.png");
}
else if (_gun == SniperRifle)
{
	cross->Switch("sprites/263.png");
}
else if (_gun == BeamRifle)
{
	cross->Switch("sprites/266.png");
}
}
Gun Player::GetGun()
{
    switch(_gun)
    {
        //format: {Damage, Delay, sprite1, sprite2, recoil}
    case Pistol:
         {
             return pistol;
             break;
         }
        case Magnum:
        {
            return magnum;
            break;
        }
        case Uzi:
            {
            return uzi;
            break;}
        case Laserpistol:
            {
            return laserpistol;
            break;}
        case SMG:
            {
            return smg; //Gun {3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case Shotgun:
            {
            return shotgun; //Gun {3,50,"sprites/29.png","sprites/30.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case LaserRifle:
            {
            return laserrifle; //Gun {3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case RocketLauncher:
            {
            return rocketlauncher;//Gun {3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case BeamRifle:
            {
            return beamrifle;
            //Gun {3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case Minigun:
            {
            return minigun;
            //Gun {3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case RadioactiveShotgun:
            {
            return radioactiveshotgun;
            //Gun {3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case SniperRifle:
            {
            return sniperrifle;
            // {3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case Lightsaber:
            {
            return lightsaber;
            //{3,50,"sprites/28.png","sprites/1.png","sprites/0.wav","sprites/1.png",1};
            break;}
        case Knife:
            return knife;
    }
    return pistol;
}
    Gun Player::AddGun(int damage, int delay,
                        std::string _audio, int recoil, int spread)
    {
Gun gun;
gun.damage = damage;
gun.delay = delay;
gun._audio = _audio;
gun.recoil = recoil;
gun.spread = spread;
return gun;


    }
	int Player::Getproj()
	{
		return (int)_gun;
	}
	bool Player::dead()
	{
		if (_health < 1&&!_dead)
		{
			_dead = true;
			return true;
		}
		 return false;
	}