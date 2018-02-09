#pragma once
#include "VisibleGameObject.h"
#include "Game.h"

class Body :
	public VisibleGameObject 
{
public:
	Body(std::string name, std::string str, float x, float y);
	~Body();
	void Draw(sf::RenderWindow& rw);
	void Update(float elapsedTime);
private:
	float _x, _y;
	std::string _path;
	float _time;
};