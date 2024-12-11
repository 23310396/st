#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
#include <Control.hpp>
#include <Vida.hpp>
#include <Campo.hpp>
#include <Mapa.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 435), "DinoChrome");

    Control control1;
    Control control2(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::A);

    std::vector<std::string> menuItems = {"Mapa 1", "Mapa 2", "Mapa 3", "Salir"};
    Menu menu(window.getSize().x, window.getSize().y, menuItems);

    bool isMenuActive = true;

    HealthBar playerHealth_1(100, {250, 30}, {381, 55});
    HealthBar playerHealth_2(100, {250, 30}, {8, 55});
    Campo Campo("25.png");
    Personaje Ken(sf::Vector2f(440, 240), "ken.png", control1);
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

            if (isMenuActive)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu.moveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu.moveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int selectedItem = menu.getSelectedItemIndex();
                        if (selectedItem == 3)
                        { // "Salir"
                            window.close();
                        }
                        else
                        {
                            isMenuActive = false;
                            loadMap(selectedItem, window);
                        }
                    }
                }
            }
        }

        // Leer el teclado
        Ken.LeerTeclado();
        pika.LeerTeclado();

        // Actualizar objetos
        Ken.Actualizar();
        pika.Actualizar();

        // Dibujar objetos
        if (isMenuActive)
        {
            window.clear();
            menu.draw(window);
            window.display();
        }

        /*window.clear();
        Campo.Dibujar(window);
        Ken.Dibujar(window);
        pika.Dibujar(window);
        playerHealth_1.draw(window);
        playerHealth_2.draw(window);
        window.display()*/
    }

    return 0;
}