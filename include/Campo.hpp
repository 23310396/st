#pragma once

class Campo
{

private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Campo(std::string imagen)
    {

        // Cargar la imagen desde un archivo
        if (!texture.loadFromFile("assets/images/" + imagen))
        {
            throw "No se encontro imagen";
        }
        this->sprite = sf::Sprite(texture);
    }

    void Dibujar(sf::RenderWindow &window)
    {
        window.draw(this->sprite);
    }
};