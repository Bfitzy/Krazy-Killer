#include "GameObjectManager.h"
#include "SFML/Graphics.hpp"
#include "Game.h"


 GameObjectManager::GameObjectManager()
 {
 }

 GameObjectManager::~GameObjectManager()
 {
   std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectDeallocator());
 }

 void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
 {
   _gameObjects.insert(std::pair<std::string,VisibleGameObject*>(name,gameObject));
 }

 void GameObjectManager::Remove(std::string name)
 {
   std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
   if(results != _gameObjects.end() )
   {
     delete results->second;
     _gameObjects.erase(results);
   }
 }
 void GameObjectManager::Paint(std::string _path, float x, float y)
 {
	 std::string name = "Paint";
	 std::string result;
	 char numstr[21]; // enough to hold all numbers up to 64-bits
	 sprintf(numstr, "%d", _gameObjects.size() + 1);
	 result = name + numstr;
	 Body *body = new Body(result, _path, x, y);
	 Game::Add(result, body);
 }
 VisibleGameObject* GameObjectManager::Get(std::string name) const
 {
   std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
   if(results == _gameObjects.end() )
     return NULL;
   return results->second;

 }

 int GameObjectManager::GetObjectCount() const
 {
   return _gameObjects.size();
 }


 void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
 {
   std::map<std::string,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
   while(itr != _gameObjects.end())
   {
     itr->second->Draw(renderWindow);
     itr++;
   }
 }
 void GameObjectManager::UpdateAll()
{
	std::map<std::string,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	float timeDelta = clock.restart().asSeconds();

	while(itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
}/*
 std::vector<std::weak_ptr<ICollideable>> GameObjectManager::GetCollideables()
 {
	 return mCollideables;
 }
 VisibleGameObject* GameObjectManager::Getcollideable(std::string name) const
 {
	 std::map<std::string, VisibleGameObject*>::const_iterator results = _collideables.find(name);
	 if (results == _collideables.end())
		 return NULL;
	 return results->second;

 }
 */