#pragma once
#include <SFML/Graphics.hpp>
#include <Control.hpp>

class Personaje
{
private:
    double velocidad = 0.1;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int cuadroActual = 0;
    int numFrames = 4; // Número total de frames en la animación
    int frameWidth = 32;
    int frameHeight = 32;
    Control control;

public:
    sf::Sprite sprite;
    Personaje(sf::Vector2f position, std::string imagen, Control control);

    void Mover(float offsetX, float offsetY);
    void Dibujar(sf::RenderWindow &window);
    void Actualizar();
    void LeerTeclado();
    const sf::Sprite &getSprite() const; // Método para obtener el sprite
    sf::FloatRect getBounds() const;     // Método para obtener los límites
};

Personaje::Personaje(sf::Vector2f position, std::string imagen, Control control)
    : control(control)
{
    // Cargar la imagen desde un archivo
    if (!texture.loadFromFile("assets/images/" + imagen))
    {
        throw "No se encontro imagen";
    }
    this->sprite = sf::Sprite(texture);
    this->sprite.setPosition(position); // Posición inicial sprite
}

void Personaje::Mover(float offsetX, float offsetY)
{
    sprite.move(offsetX, offsetY);
}

void Personaje::Dibujar(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

void Personaje::Actualizar()
{
    // Actualizar el frame de la animación
    if (clock.getElapsedTime().asSeconds() >= frameTime)
    {
        cuadroActual = (cuadroActual + 1) % numFrames;
        sprite.setTextureRect(sf::IntRect((cuadroActual * 64) + 17, 133, 64, 36));
        clock.restart();
    }
}

void Personaje::LeerTeclado()
{
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

const sf::Sprite &Personaje::getSprite() const
{
    return sprite;
}

sf::FloatRect Personaje::getBounds() const
{
    return sprite.getGlobalBounds();
}