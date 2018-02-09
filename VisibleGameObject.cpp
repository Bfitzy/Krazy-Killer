#include "VisibleGameObject.h"
#include "Game.h"
#include <iostream>
#include "GameObjectManager.h"

VisibleGameObject::VisibleGameObject()
: _isLoaded(false)
{
 //_isLoaded = false;
}

VisibleGameObject::~VisibleGameObject()
{

}
void VisibleGameObject::AddBody(std::string path, float x, float y)
{
	
}
void VisibleGameObject::Load(std::string filename)
{
if(_texture.loadFromFile(filename) == false)
  {
    _filename = "";
    _isLoaded = false;
    std::cout<<"Failed to load "+filename;
  }
  else
  {
    _filename = filename;
    _sprite.setTexture(_texture);
	textures.push_back(_texture);
    _isLoaded = true;
    std::cout<<"Successfully loaded "+filename;
  }
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
    if(_isLoaded)
    {
        renderWindow.draw(_sprite);
    }
}
void VisibleGameObject::Update(float elapsedTime)
{

}
void VisibleGameObject::SetPosition(float x, float y)
{
  if(_isLoaded)
  {
    _sprite.setPosition(x,y);
  }
}
sf::Vector2f VisibleGameObject::GetPosition() const
{
  if(_isLoaded)
  {
    return _sprite.getPosition();
  }
  return sf::Vector2f();
}


sf::Sprite& VisibleGameObject::GetSprite()
{
  return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
  return _isLoaded;
}
float VisibleGameObject::GetHeight() const
{
  return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
  return _sprite.getLocalBounds().width;
}

sf::FloatRect VisibleGameObject::GetBoundingRect() const
{
  return _sprite.getGlobalBounds();
}
void VisibleGameObject::Shift(int i)
{
	_sprite.setTexture(textures[i]);
}