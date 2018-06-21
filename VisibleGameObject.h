#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Config.hpp"
#include "SFML/Window.hpp"
#include <cassert>
class VisibleGameObject
{
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();

    virtual void Load(std::string filename);
    virtual void Draw(sf::RenderWindow & window);
    virtual void Update(float elapsedTime);
	virtual void AddBody(std::string path, float x, float y);
    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual bool IsLoaded() const;
    virtual float GetWidth() const;
  virtual float GetHeight() const;
  virtual void Shift(int i);

  virtual sf::FloatRect GetBoundingRect() const;
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::string _filename;
    bool _isLoaded;
	std::vector<sf::Texture> textures;
protected:
  sf::Sprite& GetSprite();
};
