#pragma once
#include "VisibleGameObject.h"
#include "SFML/System.hpp"
class Cratespawner
{
public:
    Cratespawner();
    ~Cratespawner();

   void Add(std::string name, VisibleGameObject* gameObject);
   void AddCrate();
   void Remove(std::string name);
   int GetCrateCount() const;
   VisibleGameObject* Get(std::string name) const;
 private:
   sf::Clock clock;

   struct CrateDeallocator
   {
     void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
     {
       delete p.second;
     }
   };
};
