#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
#include <Control.hpp>
#include <Vida.hpp>
#include <Campo.hpp>
//#include "Menu.hpp"
#include <iostream>

// Función de colisión y resolución
bool checkCollision(Personaje &p1, Personaje &p2)
{
    if (p1.getBounds().intersects(p2.getBounds()))
    {
        sf::FloatRect intersection;
        p1.getBounds().intersects(p2.getBounds(), intersection);

        if (intersection.width < intersection.height)
        {
            if (p1.getSprite().getPosition().x < p2.getSprite().getPosition().x)
            {
                p1.Mover(-intersection.width, 0);
                p2.Mover(intersection.width, 0);
            }
            else
            {
                p1.Mover(intersection.width, 0);
                p2.Mover(-intersection.width, 0);
            }
        }
        else
        {
            if (p1.getSprite().getPosition().y < p2.getSprite().getPosition().y)
            {
                p1.Mover(0, -intersection.height);
                p2.Mover(0, intersection.height);
            }
            else
            {
                p1.Mover(0, intersection.height);
                p2.Mover(0, -intersection.height);
            }
        }
        return true;
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 435), "st");

    Control control1;
    Control control2(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::A);

    Campo campo("25.png");
    HealthBar playerHealth_1(100, {250, 30}, {381, 55});
    HealthBar playerHealth_2(100, {250, 30}, {8, 55});
    Personaje Ken(sf::Vector2f(440, 240), "pikachu.png", control1);
    Personaje pika(sf::Vector2f(130, 240), "pikachu.png", control2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Leer el teclado con teclas de ataque diferentes
        Ken.LeerTeclado(sf::Keyboard::K); // Tecla de ataque para Ken
        pika.LeerTeclado(sf::Keyboard::F); // Tecla de ataque para pika

        // Actualizar objetos
        Ken.Actualizar();
        pika.Actualizar();

        // Verificar y resolver colisiones
        if (checkCollision(Ken, pika))
        {
            std::cout << "Collision detected and resolved!" << std::endl;
        }

        // Lógica de ataque y reducción de vida
        if (Ken.atacando && checkCollision(Ken, pika))
        {
            playerHealth_2.takeDamage(10);// Reduce la vida de pika
            Ken.atacando = false;// Resetea el estado de ataque después de atacar
            std::cout << "Vida de pika: " << playerHealth_2.getCurrentHealth() << std::endl; // Mensaje de depuración
        }
        if (pika.atacando && checkCollision(pika, Ken))
        {
            playerHealth_1.takeDamage(10);// Reduce la vida de Ken
            pika.atacando = false;// Resetea el estado de ataque después de atacar
            std::cout << "Vida de Ken: " << playerHealth_1.getCurrentHealth() << std::endl; // Mensaje de depuración
        }

        // Dibujar objetos
        window.clear();
        campo.Dibujar(window);
        Ken.Dibujar(window);
        pika.Dibujar(window);
        playerHealth_1.draw(window);
        playerHealth_2.draw(window);
        window.display();
    }

    return 0;
}