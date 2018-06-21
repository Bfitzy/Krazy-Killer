#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include <iostream>
#include <memory>
#include "SFML/Audio.hpp"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"


Game::GameState Game::_gameState = Uninitialized;
GameObjectManager Game::_gameObjectManager;
sf::RenderWindow Game::_mainWindow;
Krazyspawner Game::_krazySpawner;
void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.create(sf::VideoMode(960,720),"Krazy Killer");
  _mainWindow.setVerticalSyncEnabled(true);
  SFMLSoundProvider soundProvider;
  ServiceLocator::RegisterServiceLocator(&soundProvider);


  Bullet *shot = new Bullet();
  _gameObjectManager.Add("shot",shot);

  Bullet *s1 = new Bullet();
  _gameObjectManager.Add("s1", s1);
  Bullet *s2 = new Bullet();
  _gameObjectManager.Add("s2", s2);
  Bullet *s3 = new Bullet();
  _gameObjectManager.Add("s3", s3);
  Bullet *s4 = new Bullet();
  _gameObjectManager.Add("s4", s4);
  Bullet *s5 = new Bullet();
  _gameObjectManager.Add("s5", s5);
  Bullet *s6 = new Bullet();
  _gameObjectManager.Add("s6", s6);

  Player *player1 = new Player();
  _gameObjectManager.Add("player1", player1);
  _gameObjectManager.AddOnTop("player1", player1);

    WeaponCrate *crate = new WeaponCrate();
  _gameObjectManager.Add("crate", crate);

  Crosshair *cross = new Crosshair();
  _gameObjectManager.Add("crosshair",cross);
  _gameObjectManager.AddOnTop("crosshair", cross);
  Map *map1 = new Map();
  map1->SetPosition(480,360);
  _gameObjectManager.Add(" map1",map1);

  /*RedKrazy *red = new RedKrazy();
  _gameObjectManager.Add("red",red);*/







  _gameState = Game::ShowingSplash;
//  _krazySpawner.AddRed();



  while(!IsExiting())
  {

    GameLoop();
  }

  _mainWindow.close();
  return;
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting) {
		_gameObjectManager.~GameObjectManager();
		_krazySpawner.~Krazyspawner();
		return true;
  }

  else
    return false;
}
sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}
const GameObjectManager& Game::GetGameObjectManager() //RIGHT!!!
{
return Game::_gameObjectManager;
}
void Game::GameLoop()
{
    sf::Event event;
    _mainWindow.pollEvent(event);

    switch(_gameState)
    {
        case Game::ShowingMenu:
        {
            ShowMenu();
        break;
        }
        case Game::Paused:
            {
                ShowMenu();
                break;
            }
        case Game::ShowingSplash:
            {
             ShowSplashScreen();
             break;
            }
        case Game::Playing:
        {
            _krazySpawner.Spawn();
/*		auto	_mCollideables = _gameObjectManager.GetCollideables();
			for (std::size_t x = 0; x < _mCollideables.size(); x++)
			{
				for (std::size_t y = x + 1; y < _mCollideables.size(); y++) {
					auto dynamic = _mCollideables[x]; auto _static = _mCollideables[y]; if (!_mCollideables[x].lock()->isStatic())
						dynamic = _mCollideables[x];
					else if (!_mCollideables[y].lock()->isStatic())
						dynamic = _mCollideables[y];

					if (_mCollideables[x].lock()->isStatic())
						_static = _mCollideables[x];
					else if (_mCollideables[x].lock()->isStatic())
						_static = _mCollideables[y];

					if (checkCollision(dynamic, _static) && dynamic.lock()->isCollisionActive && _static.lock()->isCollisionActive)
						resolveCollision(dynamic, _static);
				}
			} */

          _mainWindow.clear();
          _gameObjectManager.UpdateAll();
          _gameObjectManager.DrawAll(_mainWindow);
          _mainWindow.display();

          if(event.type == sf::Event::Closed) _gameState = Game::Exiting;
          if(event.type == sf::Event::KeyPressed)
          {
              if(event.key.code == sf::Keyboard::Escape) ShowMenu();
          }

          break;
		case Game::Exiting:
			_gameObjectManager.~GameObjectManager();
			_krazySpawner.~Krazyspawner();
		  break;}
  }
}
void Game::Add(std::string name, VisibleGameObject* object)
{
    _gameObjectManager.Add(name, object);
}
void Game::AddOnTop(std::string name, VisibleGameObject* object)
{
	_gameObjectManager.AddOnTop(name, object);
}
void Game::Paint(std::string _path, float x, float y)
{
	_gameObjectManager.Paint(_path, x, y);
}
void Game::ShowSplashScreen()
{
    SplashScreen splashscreen;
    splashscreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}
void Game::ShowMenu()
{
MainMenu mainMenu;
MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
switch(result)
   {
   case MainMenu::Exit:
       _gameState = Game::Exiting;
       break;
   case MainMenu::Play:
       _gameState = Game::Playing;
       break;
   }
}
const Krazyspawner& Game::GetKrazyspawner()
{
	return _krazySpawner;
}

/*
bool Game::checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{
	sf::Vector2f a1 = a.lock()->getPhysicsPosition() + sf::Vector2f(a.lock()->getHitBox().left, a.lock()->getHitBox().top);
	sf::Vector2f a2 = sf::Vector2f(a.lock()->getHitBox().width, a.lock()->getHitBox().height);

	sf::Vector2f b1 = b.lock()->getPhysicsPosition() + sf::Vector2f(b.lock()->getHitBox().left, b.lock()->getHitBox().top);
	sf::Vector2f b2 = sf::Vector2f(b.lock()->getHitBox().width, b.lock()->getHitBox().height);

	//float rect = (left, top, width, height)
	sf::FloatRect aRect(a1, a2);
	sf::FloatRect bRect(b1, b2);

	if (aRect.intersects(bRect))
		return true;

	return false;
}
void Game::resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{
	auto aLeft = a.lock()->getPhysicsPosition().x + a.lock()->getHitBox().left;
	auto aTop = a.lock()->getPhysicsPosition().y + a.lock()->getHitBox().top;
	auto aRight = aLeft + a.lock()->getHitBox().width;
	auto aBottom = aTop + a.lock()->getHitBox().height;

	auto bLeft = b.lock()->getPhysicsPosition().x + b.lock()->getHitBox().left;
	auto bTop = b.lock()->getPhysicsPosition().y + b.lock()->getHitBox().top;
	auto bRight = bLeft + b.lock()->getHitBox().width;
	auto bBottom = bTop + b.lock()->getHitBox().height;

	float overlapLeft{ aRight - bLeft };
	float overlapRight{ bRight - aLeft };
	float overlapTop{ aBottom - bTop };
	float overlapBottom{ bBottom - aTop };

	bool fromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
	bool fromTop(std::abs(overlapTop) < std::abs(overlapBottom)); float minOverlapX{ fromLeft ? overlapLeft : overlapRight }; float minOverlapY{ fromTop ? overlapTop : overlapBottom }; auto y_collision = [a, fromTop](float overlapX, float overlapY, bool stair = false) { if (fromTop) {
		if (stair) {
			a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
			a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x - 5.f, a.lock()->getPhysicsPosition().y - overlapY));
		}
		else
		{
			a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
			a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y - overlapY));
		}
	}
	else if (!fromTop)
	{
		a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
		a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y + overlapY));
	}
	};

	auto x_collision = [a, fromLeft, fromTop, y_collision](float overlapX, float overlapY)
	{
		if (overlapY < 20.f && fromTop) // it's probably a stair { y_collision(overlapX, overlapY, true); return; } a.lock()->setVelocity(sf::Vector2f(0.f, a.lock()->getVelocity().y));

			if (fromLeft)
			{
				a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x - overlapX, a.lock()->getPhysicsPosition().y));
			}
			else if (!fromLeft)
			{
				a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x + overlapX, a.lock()->getPhysicsPosition().y));
			}
	};

	if (a.lock()->onContactBegin(b, fromLeft, fromTop) && b.lock()->onContactBegin(a, fromLeft, fromTop))
	{
		if (std::abs(minOverlapX) > std::abs(minOverlapY)) // y overlap
		{
			y_collision(minOverlapX, minOverlapY);
		}
		//else if (std::abs(minOverlapX) < std::abs(minOverlapY)) // x overlap { x_collision(minOverlapX, minOverlapY); } a.lock()->onContactEnd(b);
			//b.lock()->onContactEnd(a);
	}
}
std::vector<std::weak_ptr<ICollideable>> Game::GetCollideables()
{
	return mCollideables;
}
*/