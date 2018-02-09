#pragma once
#include "VisibleGameObject.h"

class Crosshair :
    public VisibleGameObject
    {
    public:
        Crosshair();
        virtual ~Crosshair();
        void Draw(sf::RenderWindow& rw);
        void Update(float elapsedTime);
        void Switch(std::string path);
    private:
        std::string _path;
    };

