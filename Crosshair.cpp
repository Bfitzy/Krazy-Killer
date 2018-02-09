#include "Crosshair.h"
#include "SFML/Window.hpp"
#include "Game.h"

Crosshair::Crosshair()
{
Load("sprites/260.png");
GetSprite().setOrigin(7,7);
}
Crosshair::~Crosshair()
{

}
void Crosshair::Draw(sf::RenderWindow & rw)
{
    sf::Vector2f m = (sf::Vector2f)sf::Mouse::getPosition(rw);
GetSprite().setPosition(m.x,m.y);
VisibleGameObject::Draw(rw);
}
void Crosshair::Update(float elapsedTime)
{

}
void Crosshair::Switch(std::string path)
{
    Load(path);
}
