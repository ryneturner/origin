#pragma once
#include "Windows.hpp"

#include "SFML/Graphics.hpp"

#define MAXIMUM 2

class Menu
{
    int index;
    sf::Font font;
    sf::Text menu[MAXIMUM];
    
    public:
        Menu();
        Menu(float width, float height);
        ~Menu() { }
    
        void draw(sf::RenderWindow &window);
        void Up();
        void Down();
        int Press() { return index; }
        void Factorization();
};
