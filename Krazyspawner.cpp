#include "Krazyspawner.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "RedKrazy.h"
#include "Body.h"
#include <string>

Krazyspawner::Krazyspawner():reds(0)
 {
 }

 Krazyspawner::~Krazyspawner()
 {
   std::for_each(_krazyObjects.begin(),_krazyObjects.end(),KrazyDeallocator());
 }

 void Krazyspawner::Add(std::string name, VisibleGameObject* krazyObject)
 {
   _krazyObjects.insert(std::pair<std::string,VisibleGameObject*>(name,krazyObject));
 }
 void Krazyspawner::AddRed()
 {
RedKrazy *red = new RedKrazy();
std::string name = "red";
std::string result;
char numstr[21]; // enough to hold all numbers up to 64-bits
sprintf(numstr, "%I32d", (int) reds);
result = name + numstr;
//name += std::to_string(reds);
//std::stringstream Stream;
//Stream.str(name);
//Stream << reds;
//name = Stream.str();
Add(result, red);
Game::Add(result, red);
//Game::AddOnTop(result, red);
reds++;
 }
 void Krazyspawner::AddBody(std::string _path, float x, float y)
 {
	 std::string name = "body";
	 std::string result;
	 char numstr[21]; // enough to hold all numbers up to 64-bits
	 sprintf(numstr, "%I32d",(int) _krazyObjects.size()+1);
	 result = name + numstr;
	 Body *body = new Body(result, _path, x, y);
	 Game::Add(result, body);
	 Add(result, body);
 }

 void Krazyspawner::Remove(std::string name)
 {
   std::map<std::string, VisibleGameObject*>::iterator results = _krazyObjects.find(name);
   if(results != _krazyObjects.end() )
   {
     delete results->second;
     _krazyObjects.erase(results);
   }
 }

 VisibleGameObject* Krazyspawner::Get(std::string name) const
 {
   std::map<std::string, VisibleGameObject*>::const_iterator results = _krazyObjects.find(name);
   if(results == _krazyObjects.end() )
     return NULL;
   return results->second;
 }

 int Krazyspawner::GetKrazyCount() const
 {
   return _krazyObjects.size();
 }
void Krazyspawner::Spawn()
{
    spawntimer++;
    if(reds<=3)
    {
        if(spawntimer>=300)
        {
            AddRed();
            spawntimer=0;
        }

    }

}
void Krazyspawner::DeathClock()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _krazyObjects.begin();
	float timeDelta = clock.restart().asSeconds();

	while (itr != _krazyObjects.end())
	{
		//itr->second->;
		itr++;
	}
}