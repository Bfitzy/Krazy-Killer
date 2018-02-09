#include "SplashScreen.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"


void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
    sf::Texture texture;
    if(!texture.loadFromFile("sprites/start.png"))
    {
        return;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(2,2));
    renderWindow.draw(sprite);
    renderWindow.display();
    sf::Event event;
    while(true)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed
               || event.type == sf::Event::MouseButtonPressed
               || event.type == sf::Event::Closed)
            {
             return;
            }
        }
    }
}
