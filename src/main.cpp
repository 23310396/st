#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
#include <Control.hpp>
#include <Vida.hpp>
#include <Campo.hpp>
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

    // Cargar la fuente para el puntaje
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Minecraft.ttf"))
    {
        // Manejar el error si no se puede cargar la fuente
        return -1;
    }

    // Crear los personajes
    Personaje Ken(sf::Vector2f(440, 240), "pikachu.png", control1, {381, 55});
    Personaje pika(sf::Vector2f(130, 240), "pikachu.png", control2, {8, 55});

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
        Ken.LeerTeclado(sf::Keyboard::K);  // Tecla de ataque para Ken
        pika.LeerTeclado(sf::Keyboard::F); // Tecla de ataque para Pika

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
            pika.takeDamage(10);  // Reduce la vida de Pika
            Ken.atacando = false; // Resetea el estado de ataque después de atacar
        }
        if (pika.atacando && checkCollision(pika, Ken))
        {
            Ken.takeDamage(10);    // Reduce la vida de Ken
            pika.atacando = false; // Resetea el estado de ataque después de atacar
        }

        // Verificar si el juego ha terminado
        if (Ken.getHealth() <= 0 || pika.getHealth() <= 0)
        {
            std::cout << (Ken.getHealth() <= 0 ? "Pika gana!" : "Ken gana!") << std::endl;
            window.close(); // Cerrar la ventana si un personaje ha ganado
        }

        // Dibujar objetos
        window.clear();
        campo.Dibujar(window);
        Ken.Dibujar(window);
        pika.Dibujar(window);

        // Mostrar el puntaje de ambos personajes
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Puntaje de Ken: " + std::to_string(Ken.getScore()) + "  |  Puntaje de Pika: " + std::to_string(pika.getScore()));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10); // Ajusta la posición de acuerdo a tu preferencia

        window.draw(scoreText); // Dibujar el puntaje

        window.display();
    }

    return 0;
}