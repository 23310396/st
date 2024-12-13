#include <SFML/Graphics.hpp>
#include <Control.hpp>
#include <iostream>

class Personaje
{
private:
    double velocidad = 0.1;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f;
    int cuadroActual = 0;
    int numFrames = 4;
    int frameWidth = 32;
    int frameHeight = 32;
    Control control;

public:
    bool atacando = false; // Estado de ataque
    sf::Sprite sprite;
    Personaje(sf::Vector2f position, std::string imagen, Control control);
    void Mover(float offsetX, float offsetY);
    void Dibujar(sf::RenderWindow &window);
    void Actualizar();
    void LeerTeclado(sf::Keyboard::Key teclaAtaque); // Modificado para recibir tecla de ataque
    const sf::Sprite &getSprite() const;
    sf::FloatRect getBounds() const;
    void Atacar(); // Nuevo método para atacar
};

Personaje::Personaje(sf::Vector2f position, std::string imagen, Control control)
    : control(control)
{
    // Cargar la imagen desde un archivo
    if (!texture.loadFromFile("assets/images/" + imagen))
    {
        throw "No se encontró imagen";
    }
    this->sprite = sf::Sprite(texture);
    this->sprite.setPosition(position); // Posición inicial del sprite
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
    if (atacando)
    {
        // Reseteamos el estado de ataque después de un breve periodo
        atacando = false;
    }
    // Actualizar el frame de la animación
    if (clock.getElapsedTime().asSeconds() >= frameTime)
    {
        cuadroActual = (cuadroActual + 1) % numFrames;
        sprite.setTextureRect(sf::IntRect((cuadroActual * 64) + 17, 133, 64, 36));
        clock.restart();
    }
}

void Personaje::LeerTeclado(sf::Keyboard::Key teclaAtaque)
{
    if (sf::Keyboard::isKeyPressed(control.MoverIzquierda()))
    {
        this->Mover(velocidad * -1, 0);
        sprite.setScale(-1.f, 1.f); // Voltear el sprite horizontalmente
    }
    if (sf::Keyboard::isKeyPressed(control.MoverDerecha()))
    {
        this->Mover(velocidad, 0);
        sprite.setScale(1.f, 1.f); // Restaurar el sprite a su orientación original
    }
    if (sf::Keyboard::isKeyPressed(control.MoverArriba()))
    {
        this->Mover(0, velocidad * -1);
    }
    if (sf::Keyboard::isKeyPressed(control.MoverAbajo()))
    {
        this->Mover(0, velocidad);
    }
    if (sf::Keyboard::isKeyPressed(teclaAtaque))
    { // Tecla de ataque
        Atacar();
        std::cout << "Ataque ejecutado!" << std::endl;
    }
}

void Personaje::Atacar()
{
    atacando = true;
    // Aquí podrías agregar animaciones de ataque o cualquier otra lógica
    std::cout << "Personaje esta atacando!" << std::endl;
}

const sf::Sprite &Personaje::getSprite() const
{
    return sprite;
}

sf::FloatRect Personaje::getBounds() const
{
    return sprite.getGlobalBounds();
}