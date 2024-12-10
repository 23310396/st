#include <SFML/Graphics.hpp>

class Personaje {
public:
    Personaje(sf::Vector2f position, sf::Color color) {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setPosition(position);
        shape.setFillColor(color);
    }

    void Mover(float offsetX, float offsetY) {
        shape.move(offsetX, offsetY);
    }

    void Dibujar(sf::RenderWindow& window) {
        window.draw(shape);
    }

private:
    sf::RectangleShape shape;
};

double velocidad = 0.1;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "DinoChrome");

    Personaje character(sf::Vector2f(400, 300), sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            character.Mover(velocidad * -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            character.Mover(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            character.Mover(0, velocidad * -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            character.Mover(0, velocidad);
        }

        window.clear();
        character.Dibujar(window);
        window.display();
    }

    return 0;
}