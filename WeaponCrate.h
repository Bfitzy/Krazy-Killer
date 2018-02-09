#pragma once
#include "VisibleGameObject.h"
#include "Player.h"
#include "SFML/Graphics.hpp"


class WeaponCrate :
  public VisibleGameObject
{
public:
  WeaponCrate();
  ~WeaponCrate();
  void Update(float elapsedTime);
  void Draw(sf::RenderWindow& rw);
  bool TouchingPlayer();
  bool showing;
  float timesinceshown;
  float timeshowing;

};


