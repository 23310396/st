#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
#include <Control.hpp>
#include <Vida.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "DinoChrome");

    // Barra de vida (frente)
    sf::RectangleShape lifeBar(sf::Vector2f(200, 650));
    lifeBar.setFillColor(sf::Color::Green);

    Control control1;
    Control control2(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::A);

    Personaje Ken(sf::Vector2f(600, 350), "ken.png", control1);
    Personaje pika(sf::Vector2f(100, 350), "pikachu.png", control2);

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

        // Leer el teclado
        Ken.LeerTeclado();
        pika.LeerTeclado();


        // Actualizar objetos
        Ken.Actualizar();
        pika.Actualizar();

        // Dibujar objetos
        window.clear();
        lifeBar.Dibujar(window);
        Ken.Dibujar(window);
        pika.Dibujar(window);
        window.display();
    }

    return 0;
}