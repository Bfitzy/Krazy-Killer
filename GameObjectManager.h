#pragma once
#include "VisibleGameObject.h"

 class GameObjectManager
 {
 public:
   GameObjectManager();
   ~GameObjectManager();

   void Add(std::string name, VisibleGameObject* gameObject);
   void Remove(std::string name);
   int GetObjectCount() const;
   VisibleGameObject* Get(std::string name) const;
   void Paint(std::string _path, float x, float y);
   //VisibleGameObject* Getcollideable(std::string name) const;

   void DrawAll(sf::RenderWindow& renderWindow);
   void UpdateAll();
//   std::vector<std::weak_ptr<ICollideable>> GetCollideables();
 private:
   std::map<std::string, VisibleGameObject*> _gameObjects;
   //std::map<std::string, VisibleGameObject*> _collideables;
   sf::Clock clock;
   //std::vector<std::weak_ptr<ICollideable>> mCollideables;

   struct GameObjectDeallocator
   {
     void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
     {
       delete p.second;
     }
   };
 };
