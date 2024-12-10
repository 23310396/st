#pragma once
#include <SFML/Graphics.hpp>

 class Vida
 {
 private:
    float maxLife = 100.f;
    float currentLife = maxLife;

 public:
    Vida()
    {
        // Barra de vida (frente)
        sf::RectangleShape lifeBar(sf::Vector2f(200.f, 20.f));
        lifeBar.setFillColor(sf::Color::Green);
        lifeBar.setPosition(50.f, 50.f);

    }
    ~Vida();
 };
 