#include "Windows.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <time.h>

//Declare Snake and Graph structs
struct Snake { int x, y; } s[100];
struct Graph { int x, y; } f;

//Precondition:     This function takes in no parameters.
//Postcondition:    This function returns void and creates the game window.
void Windows::CreateWindow()
{
    sf::Music music;
    
    //Check to see if music file was loaded properly
    if(!music.openFromFile("/Users/Turner/Desktop/Snake/images/Seed.wav"))
        std::cout << "Error Loading Music" << std::endl;
    
    //Generate a random number
    srand(static_cast<unsigned int>(time(NULL)));
    
    //Create the game Window
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake");
    sf::Texture texture1, texture2, texture3, texture4, texture5, texture6;
    
    //Load the images used for the game
    //Four colours were added
    texture1.loadFromFile("/Users/Turner/Desktop/Snake/images/white.png");
    texture2.loadFromFile("/Users/Turner/Desktop/Snake/images/red.png");
    texture3.loadFromFile("/Users/Turner/Desktop/Snake/images/maroon.png");
    texture4.loadFromFile("/Users/Turner/Desktop/Snake/images/purple.png");
    texture5.loadFromFile("/Users/Turner/Desktop/Snake/images/yellow.png");
    texture6.loadFromFile("/Users/Turner/Desktop/Snake/images/blue.png");
    
    sf::Sprite sprite1(texture1), sprite2(texture2), sprite3(texture3), sprite4(texture4), sprite5(texture5), sprite6(texture6);
    sf::Clock clock;
    
    f.x = 10;
    f.y = 10;
    
    int var = 0;
    bool decision = true;
    
    //If the window is open, the game continues running
    while(window.isOpen())
    {
        sf::Event aurora;
        
        while(window.pollEvent(aurora))
        {
            switch(aurora.type)
            {
                //Play, stop, and pause music functionality
                case sf::Event::KeyReleased:
                    if(sf::Keyboard::Key::P == aurora.key.code)
                        music.play();
                    else if(sf::Keyboard::Key::S == aurora.key.code)
                        music.stop();
                    else if(sf::Keyboard::Key::V == aurora.key.code)
                        music.pause();
                    break;
                default:
                    break;
            }
        }
        
        float time = clock.getElapsedTime().asSeconds();
        
        clock.restart();
        timer += time;
        
        sf::Event event;
        
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();
        
        //Create the keyboard controls
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dir = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dir = 2;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dir = 3;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dir = 0;
        if(timer > delay)
        {
            timer = 0;
            
            //Call Tick() class function
            Tick();
        }
        
        window.clear();
        
        for(int counter = 0; counter < N; ++counter)
            for(int innerCounter = 0; innerCounter < M; ++innerCounter)
            {
                sprite1.setPosition(counter * size, innerCounter * size);
                window.draw(sprite1);
            }
        for(int counter = 0; counter < num; ++counter)
        {
            sprite2.setPosition(s[counter].x * size, s[counter].y * size);
            window.draw(sprite2);
        }
        
        var = num % 5;
        
        //Depending on the length of the snake, the food changes colour
        switch(var)
        {
            case 1:
                sprite3.setPosition(f.x * size, f.y * size);
                window.draw(sprite3);
                decision = true;
                break;
            case 2:
                sprite4.setPosition(f.x * size, f.y * size);
                window.draw(sprite4);
                decision = true;
                break;
            case 3:
                sprite5.setPosition(f.x * size, f.y * size);
                window.draw(sprite5);
                if(decision == true)
                    delay = delay - 0.01;
                decision = false;
                break;
            case 4:
                sprite6.setPosition(f.x * size, f.y * size);
                window.draw(sprite6);
                decision = true;
                break;
            case 0:
            case 5:
                sprite2.setPosition(f.x * size, f.y * size);
                window.draw(sprite2);
                decision = true;
                break;
        }
        
        window.display();
    }
}

//Precondition:     This function takes in no parameters.
//Postcondition:    This function returns void and moves the snake around the window.
void Windows::Tick()
{
    for (int counter = num; counter > 0; --counter)
    {
        s[counter].x = s[counter - 1].x;
        s[counter].y = s[counter - 1].y;
    }
    
    if(dir == 0)
        s[0].y += 1;
    if(dir == 1)
        s[0].x -= 1;
    if(dir == 2)
        s[0].x += 1;
    if(dir == 3)
        s[0].y -= 1;
    if((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }
    if(s[0].x > N)
        s[0].x = 0;
    if(s[0].x < 0)
        s[0].x = N;
    if(s[0].y > M)
        s[0].y = 0;
    if(s[0].y < 0)
        s[0].y = M;
    
    for(int counter = 1; counter < num; ++counter)
        if(s[0].x == s[counter].x && s[0].y == s[counter].y)
            num = counter;
}
