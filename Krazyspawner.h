#pragma once
#include "VisibleGameObject.h"
#include "SFML/System.hpp"
class Krazyspawner
{
public:
    Krazyspawner();
    ~Krazyspawner();

   void Add(std::string name, VisibleGameObject* gameObject);
   void AddRed();
   void AddBody(std::string _path, float x, float y);
   void Remove(std::string name);
   void Spawn();
   int GetKrazyCount() const;
   void DeathClock();
   VisibleGameObject* Get(std::string name) const;
 private:
     int reds;
     int spawntimer;
   std::map<std::string, VisibleGameObject*> _krazyObjects;
   sf::Clock clock;
   float _delay;

   struct KrazyDeallocator
   {
     void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
     {
       delete p.second;
     }
   };
};
