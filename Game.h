#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Bullet.h"
#include <memory>
#include "Player.h"
#include "Map.h"
#include "GameObjectManager.h"
#include "RedKrazy.h"
#include "Crosshair.h"
#include "VisibleGameObject.h"
#include "Krazyspawner.h"
#include "WeaponCrate.h"
#include "Body.h"
#define pi 3.1415926535897

class Game
{

public:
  static void Start();
  static sf::RenderWindow& GetWindow();
  const static GameObjectManager& GetGameObjectManager();
  const static Krazyspawner& GetKrazyspawner();
  static void Add(std::string, VisibleGameObject* object);
//  bool checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);
//  void resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);
//  std::vector<std::weak_ptr<ICollideable>> GetCollideables();
private:
  static bool IsExiting();
  static void GameLoop();
//  std::vector<std::weak_ptr<ICollideable>> mCollideables;
  static void ShowSplashScreen();
  static void ShowMenu();



  enum GameState { Uninitialized, ShowingSplash, Paused,
          ShowingMenu, Playing, Exiting };

  static GameState _gameState;
  static sf::RenderWindow _mainWindow;
  static GameObjectManager _gameObjectManager;
  static Krazyspawner _krazySpawner;
};
