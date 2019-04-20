#include "Menu.hpp"
#include "Windows.hpp"

#include <SFML/Graphics.hpp>

#include <time.h>

int main()
{
    //Create class object
    Windows object;
    
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML");
    Menu menu(window.getSize().x, window.getSize().y);
    
    while(window.isOpen())
    {
        sf::Event event;
        
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Up:
                            menu.Up();
                            break;
                        case sf::Keyboard::Down:
                            menu.Down();
                            break;
                        case sf::Keyboard::Return:
                            switch(menu.Press())
                            {
                                case 0:
                                    window.close();
                                    object.CreateWindow();
                                    break;
                                case 1:
                                    window.close();
                                    break;
                            }
                            break;
                    }
                    break;
                    
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        window.clear(sf::Color::White);
        menu.draw(window);
        window.display();
    }
    
    return 0;
}

