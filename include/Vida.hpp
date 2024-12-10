#pragma once
#include <SFML/Graphics.hpp>

 class Vida
 {

 private:
   sf::Sprite lifebar;
   float maxLife = 100.f;
   float currentLife = maxLife;

 public:
    Vida()
    {
        // Barra de vida 
        sf::RectangleShape lifeBar(sf::Vector2f(200, 20));
        lifeBar.setFillColor(sf::Color::Green);
        lifeBar.setPosition(50, 50);

    }
    
     void Dibujar(sf::RenderWindow &window)
    {
        window.draw(this->lifebar);
    }
 };
 