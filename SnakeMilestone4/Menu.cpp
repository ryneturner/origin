#include "Menu.hpp"

//Create menu
Menu::Menu(float width, float height)
{
    //Load font using filepath on Macintosh
    if(!font.loadFromFile("/System/Library/Fonts/SFNSText.ttf"))
        exit(1);
    
    //Set font, initial colour, tite of option, and position relative to screen size
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Blue);
    menu[0].setString("Play Snake");
    menu[0].setPosition(sf::Vector2f(width / 2.5, height / (MAXIMUM + 1)));
    
    menu[1].setFont(font);
    menu[1].setColor(sf::Color::Black);
    menu[1].setString("Exit Snake");
    menu[1].setPosition(sf::Vector2f(width / 2.5, height / (MAXIMUM + 1) * 2));
    
    index = 0;
}

//Create window
void Menu::draw(sf::RenderWindow &window)
{
    for(int counter = 0; counter < MAXIMUM; ++counter)
        window.draw(menu[counter]);
}

//Move up
void Menu::Up()
{
    if(index - 1 >= 0)
    {
        menu[index].setColor(sf::Color::Black);
        
        --index;
        
        menu[index].setColor(sf::Color::Blue);
    }
}

//Move down
void Menu::Down()
{
    if(index + 1 < MAXIMUM)
    {
        menu[index].setColor(sf::Color::Black);
        
        ++index;
        
        menu[index].setColor(sf::Color::Blue);
    }
}
