#include "MainMenu.h"
#include <iostream>


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

    sf::Texture texture;
    texture.loadFromFile("levels/menu.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);

    MenuItem playButton;
    playButton.rect.top = 630;
    playButton.rect.left = 750;
    playButton.rect.height = 60;
    playButton.rect.width = 180;
    playButton.action = Play;

    MenuItem exitButton;
    exitButton.rect.top = 0;
    exitButton.rect.left = 0;
    exitButton.rect.height = 50;
    exitButton.rect.width =50;
    exitButton.action = Exit;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);

    window.draw(sprite);
    window.display();

return GetMenuResponse(window);
}
MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
 {
   std::cout<<x << " , "<<y<<" ";
   std::list<MenuItem>::iterator it;

   for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
   {
     sf::Rect<int> menuItemRect = (*it).rect;
       if (menuItemRect.contains(x,y))
       {
           std::cout<<x << " , "<<y<<" ";
           return it->action;
       }
   }
    return Nothing;
   //return Nothing;
 }
 MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
 {
   sf::Event menuEvent;

   while(true)
   {

     while(window.pollEvent(menuEvent))
     {
       if(menuEvent.type == sf::Event::MouseButtonPressed)
       {
         return HandleClick(menuEvent.mouseButton.x,menuEvent.mouseButton.y);
       }
       if(menuEvent.type == sf::Event::Closed)
       {

         return Exit;
       }
       if(menuEvent.type == sf::Event::KeyPressed)
       {
           if(menuEvent.key.code == sf::Keyboard::Escape)
           {
               return Exit;
           }
       }
     }
   }
 }
