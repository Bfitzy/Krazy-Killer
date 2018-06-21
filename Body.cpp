#include "Body.h"
#define sq2 sqrt(2)
Body::Body(std::string name, std::string str, float x, float y)
{

	_path = str;
	_x = x;
	_y = y;
	_time = 0;
	Load(_path);
	GetSprite().scale(sq2, sq2);
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
	SetPosition(_x,_y);
}
Body::~Body()
{

}
void Body::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}
void Body::Update(float elapsedTime)
{
	_time += elapsedTime;
	
}