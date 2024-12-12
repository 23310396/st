#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Game
{
public:
    Game(float width, float height, const std::vector<std::string> &menuItems, const std::vector<std::string> &mapFiles);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleInput();
    void moveUp();
    void moveDown();
    bool loadMap(int mapIndex);
    void drawMenu();
    void drawMap();

    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::Text> menuItemsText;
    std::vector<std::string> mapFiles;
    int selectedItemIndex;
    bool isMenuActive;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
};

// Implementación de los métodos

Game::Game(float width, float height, const std::vector<std::string> &menuItems, const std::vector<std::string> &mapFiles)
    : window(sf::VideoMode(width, height), "Menu de st"),
      menuItemsText(menuItems.size()), mapFiles(mapFiles), selectedItemIndex(0), isMenuActive(true)
{
    if (!font.loadFromFile("path/to/your/font.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }

    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        menuItemsText[i].setFont(font);
        menuItemsText[i].setString(menuItems[i]);
        menuItemsText[i].setCharacterSize(30);
        menuItemsText[i].setPosition(sf::Vector2f(width / 2 - menuItemsText[i].getGlobalBounds().width / 2, height / (menuItems.size() + 1) * (i + 1)));
        if (i == 0)
        {
            menuItemsText[i].setFillColor(sf::Color::Red); // Seleccionado
        }
        else
        {
            menuItemsText[i].setFillColor(sf::Color::White); // No seleccionado
        }
    }
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        handleInput();
    }
}

void Game::handleInput()
{
    if (isMenuActive)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            moveUp();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            moveDown();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int selectedItem = selectedItemIndex;
            if (selectedItem == menuItemsText.size() - 1)
            { // "Salir"
                window.close();
            }
            else
            {
                isMenuActive = false;
                if (!loadMap(selectedItem))
                {
                    std::cerr << "Failed to load map" << std::endl;
                    window.close();
                }
            }
        }
    }
}

void Game::update()
{
    // Aquí puedes agregar lógica adicional si es necesario
}

void Game::render()
{
    window.clear();
    if (isMenuActive)
    {
        drawMenu();
    }
    else
    {
        drawMap();
    }
    window.display();
}

void Game::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menuItemsText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItemsText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Game::moveDown()
{
    if (selectedItemIndex + 1 < menuItemsText.size())
    {
        menuItemsText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItemsText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

bool Game::loadMap(int mapIndex)
{
    if (!mapTexture.loadFromFile(mapFiles[mapIndex]))
    {
        std::cerr << "Error loading map texture" << std::endl;
        return false;
    }
    mapSprite.setTexture(mapTexture);
    return true;
}

void Game::drawMenu()
{
    for (const auto &item : menuItemsText)
    {
        window.draw(item);
    }
}

void Game::drawMap()
{
    window.draw(mapSprite);
}