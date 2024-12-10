#pragma once
#include <Control.hpp>

class Personaje
{

private:
    double velocidad = 0.1;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int cuadroActual = 0;
    int numFrames = 4; // Número total de frames en la animación
    int frameWidth = 32;
    int frameHeight = 32;
    Control control;

public:
    Personaje(sf::Vector2f position, std::string imagen, Control control)
    {
        this->control = control;
        // Cargar la imagen desde un archivo
        if (!texture.loadFromFile("assets/images/" + imagen))
        {
            throw "No se encontro imagen";
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
    }

    void Mover(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
  
    }

    void Dibujar(sf::RenderWindow &window)
    {
        window.draw(this->sprite);
        
    }

    void Actualizar(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            cuadroActual = (cuadroActual + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect((cuadroActual * 64)+17, 133, 64, 36));
            clock.restart();
        }
    }

    void LeerTeclado(){
        if (sf::Keyboard::isKeyPressed(control.MoverIzquierda()))
        {
            this->Mover(velocidad * -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(control.MoverDerecha()))
        {
            this->Mover(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(control.MoverArriba()))
        {
            this->Mover(0, velocidad * -1);
        }
        if (sf::Keyboard::isKeyPressed(control.MoverAbajo()))
        {
            this->Mover(0, velocidad);
        }
    }

};