#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Menu
{
public:
    Menu(float width, float height, const std::vector<std::string> &menuItems);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
};

Menu::Menu(float width, float height, const std::vector<std::string> &items)
{
    if (!font.loadFromFile("path/to/your/font.ttf"))
    {
        // Manejo de errores
    }

    selectedItemIndex = 0;

    for (size_t i = 0; i < items.size(); ++i)
    {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(30);

        // Posicionar los elementos del menú
        text.setPosition(sf::Vector2f(width / 2 - text.getGlobalBounds().width / 2, height / (items.size() + 1) * (i + 1)));

        menuItems.push_back(text);
    }

    menuItems[selectedItemIndex].setFillColor(sf::Color::Red); // Colorea el elemento seleccionado
}

void Menu::draw(sf::RenderWindow &window)
{
    for (const auto &item : menuItems)
    {
        window.draw(item);
    }
}

void Menu::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 < menuItems.size())
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedItemIndex() const
{
    return selectedItemIndex;
}

void loadMap(int mapIndex, sf::RenderWindow &window)
{
    // Aquí puedes cargar el mapa correspondiente basado en mapIndex
    // Por ejemplo, podrías tener un array de texturas de mapas

    sf::Texture mapTexture;
    std::string mapFiles[] = {"1.png", "2.png", "3.png", "4.png", "5.png", "6.png", "7.png", "8.png", "9.png", "10.png", "11.png", "12.png"};

    if (!mapTexture.loadFromFile(mapFiles[mapIndex]))
    {
        std::cerr << "Error al cargar la textura del mapa" << std::endl;
    }

    sf::Sprite mapSprite(mapTexture);

    // Bucle de renderizado para mostrar el mapa seleccionado
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(mapSprite);
        window.display();
    }
}