#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

class Menu
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Font font; // Esta sigue siendo privada
    sf::Text text;
    std::vector<std::string> imagePaths;
    int currentImageIndex = 0;
    sf::Clock clock;
    float switchTime = 1.0f;

public:
    Menu(std::vector<std::string> imagenes)
    {
        imagePaths = imagenes;

        if (!texture.loadFromFile("assets/images/" + imagePaths[currentImageIndex]))
        {
            throw "No se encontró imagen";
        }
        sprite = sf::Sprite(texture);

        if (!font.loadFromFile("assets/fonts/Minecraft.ttf"))
        {
            throw "No se pudo cargar la fuente";
        }

        text.setFont(font);
        text.setString("Bienvenido a ST\nPresiona Enter para jugar");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(160, 180);
    }

    void Dibujar(sf::RenderWindow &window)
    {
        window.draw(this->sprite);
        window.draw(text);
    }

    bool IniciarJuego()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            return true;
        }
        return false;
    }

    void Actualizar()
    {
        if (clock.getElapsedTime().asSeconds() >= switchTime)
        {
            currentImageIndex = (currentImageIndex + 1) % imagePaths.size();

            if (!texture.loadFromFile("assets/images/" + imagePaths[currentImageIndex]))
            {
                throw "No se encontró la imagen";
            }
            sprite.setTexture(texture);

            clock.restart();
        }
    }

    // Método público para obtener la fuente
    sf::Font &getFont()
    {
        return font;
    }
};

// Clase Control
class Control
{
private:
    sf::Keyboard::Key arriba;
    sf::Keyboard::Key abajo;
    sf::Keyboard::Key derecha;
    sf::Keyboard::Key izquierda;

public:
    Control() : arriba(sf::Keyboard::Up), abajo(sf::Keyboard::Down), derecha(sf::Keyboard::Right), izquierda(sf::Keyboard::Left) {}
    Control(sf::Keyboard::Key arriba, sf::Keyboard::Key abajo, sf::Keyboard::Key derecha, sf::Keyboard::Key izquierda)
        : arriba(arriba), abajo(abajo), derecha(derecha), izquierda(izquierda) {}
    sf::Keyboard::Key MoverArriba() { return arriba; }
    sf::Keyboard::Key MoverAbajo() { return abajo; }
    sf::Keyboard::Key MoverIzquierda() { return izquierda; }
    sf::Keyboard::Key MoverDerecha() { return derecha; }
};

// Clase Vida
class Vida
{
private:
    int maxHealth;
    int currentHealth;
    sf::Font font;
    sf::Text healthText;
    sf::Vector2f position;

public:
    Vida(int maxHealth, sf::Vector2f position)
        : maxHealth(maxHealth), currentHealth(maxHealth), position(position)
    {
        if (!font.loadFromFile("./assets/fonts/Minecraft.ttf"))
        {
            throw std::runtime_error("No se pudo cargar la fuente");
        }
        healthText.setFont(font);
        healthText.setCharacterSize(24);
        healthText.setFillColor(sf::Color::Green);
        healthText.setPosition(position);
        healthText.setString(std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
    }

    void takeDamage(int damage)
    {
        currentHealth -= damage;
        if (currentHealth < 0)
            currentHealth = 0;
        healthText.setString(std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
    }

    void draw(sf::RenderWindow &window)
    {
        sf::RectangleShape healthBar(sf::Vector2f(static_cast<float>(currentHealth) / maxHealth * 100, 10));
        healthBar.setFillColor(sf::Color::Red);
        healthBar.setPosition(position);

        window.draw(healthBar);
        window.draw(healthText);
    }

    int getCurrentHealth() const { return currentHealth; }
};

// Clase Personaje
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
    Vida healthBar;
    int score = 0;

public:
    bool atacando = false;
    bool puedeAtacar = true; // Nuevo flag para controlar el ataque

    sf::Sprite sprite;

    Personaje(sf::Vector2f position, std::string imagen, Control control, sf::Vector2f healthBarPosition)
        : control(control), healthBar(100, healthBarPosition)
    {
        if (!texture.loadFromFile("assets/images/" + imagen))
        {
            throw "No se encontró imagen";
        }
        sprite = sf::Sprite(texture);
        sprite.setPosition(position);
    }

    void Mover(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
    }

    void Dibujar(sf::RenderWindow &window)
    {
        window.draw(sprite);
        healthBar.draw(window);
    }

    void Actualizar()
    {
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            cuadroActual = (cuadroActual + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect((cuadroActual * 64) + 17, 133, 64, 36));
            clock.restart();
        }
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            cuadroActual = (cuadroActual + 1) % numFrames; // Cambia al siguiente cuadro
            int left = cuadroActual * frameWidth;          // Coordenada x del cuadro actual
            int top = 0;                                   // Coordenada y (fila 0)
            sprite.setTextureRect(sf::IntRect(left, top, frameWidth, frameHeight));
            clock.restart();
        }
    }

    void LeerTeclado(sf::Keyboard::Key teclaAtaque)
    {
        if (sf::Keyboard::isKeyPressed(control.MoverIzquierda()))
        {
            Mover(-velocidad, 0);
            sprite.setScale(-1.f, 1.f); // Voltear el sprite horizontalmente
        }
        else if (sf::Keyboard::isKeyPressed(control.MoverDerecha()))
        {
            Mover(velocidad, 0);
            sprite.setScale(1.f, 1.f); // Restaurar el sprite a su orientación original
        }

        if (sf::Keyboard::isKeyPressed(control.MoverArriba()))
            Mover(0, -velocidad);
        if (sf::Keyboard::isKeyPressed(control.MoverAbajo()))
            Mover(0, velocidad);

        // Solo atacar si la tecla de ataque está presionada y el personaje puede atacar
        if (sf::Keyboard::isKeyPressed(teclaAtaque) && puedeAtacar)
        {
            atacando = true;
            puedeAtacar = false; // Desactivar ataque hasta que se suelte la tecla
        }

        // Permitir que el personaje pueda atacar de nuevo cuando se suelta la tecla
        if (!sf::Keyboard::isKeyPressed(teclaAtaque))
        {
            puedeAtacar = true; // Permitir el siguiente ataque
        }
    }

    void takeDamage(int damage)
    {
        healthBar.takeDamage(damage);
    }

    int getHealth() const
    {
        return healthBar.getCurrentHealth();
    }

    sf::FloatRect getBounds() const
    {
        return sprite.getGlobalBounds();
    }
};

// Clase Colision
class Colision
{
public:
    static bool detectar(Personaje &p1, Personaje &p2)
    {
        return p1.getBounds().intersects(p2.getBounds());
    }

    static void manejar(Personaje &p1, Personaje &p2)
    {
        if (detectar(p1, p2))
        {
            sf::FloatRect interseccion;
            p1.getBounds().intersects(p2.getBounds(), interseccion);

            if (interseccion.width < interseccion.height)
            {
                if (p1.sprite.getPosition().x < p2.sprite.getPosition().x)
                {
                    p1.Mover(-interseccion.width / 2, 0);
                    p2.Mover(interseccion.width / 2, 0);
                }
                else
                {
                    p1.Mover(interseccion.width / 2, 0);
                    p2.Mover(-interseccion.width / 2, 0);
                }
            }
            else
            {
                if (p1.sprite.getPosition().y < p2.sprite.getPosition().y)
                {
                    p1.Mover(0, -interseccion.height / 2);
                    p2.Mover(0, interseccion.height / 2);
                }
                else
                {
                    p1.Mover(0, interseccion.height / 2);
                    p2.Mover(0, -interseccion.height / 2);
                }
            }

            if (p1.atacando)
                p2.takeDamage(1);
            if (p2.atacando)
                p1.takeDamage(1);
        }
    }
};

// Clase Campo
class Campo
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Campo(std::string imagen)
    {
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

// Main
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 435), "ST");

    // Crear una lista de imágenes que se mostrarán en el menú
    std::vector<std::string> imagenes = {"9.png", "25.png", "14.png", "2.png", "26.png", "10.png", "3.png"};

    Menu menu(imagenes); // Crear el menú con las imágenes
    Campo campo("25.png");

    // Controladores y personajes como antes
    Control control1;
    Control control2(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::A);

    Personaje Ken(sf::Vector2f(440, 240), "pikachu.png", control1, {381, 55});
    Personaje Pika(sf::Vector2f(130, 240), "pikachu.png", control2, {8, 55});

    // Crear el texto de victoria
    sf::Text winText;
    winText.setFont(menu.getFont());        // Usamos el método público para acceder a la fuente
    winText.setCharacterSize(30);           // Tamaño del texto
    winText.setFillColor(sf::Color::White); // Color blanco para el texto

    bool gameOver = false;   // Para controlar si el juego terminó
    std::string winner = ""; // Para almacenar quién ganó

    // Ciclo para mostrar el menú
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar el menú (para cambiar las imágenes)
        menu.Actualizar();

        // Si se presiona Enter, iniciar el juego
        if (menu.IniciarJuego())
        {
            break; // Salir del ciclo de menú y comenzar el juego
        }

        window.clear();
        menu.Dibujar(window); // Dibujar el menú (que incluye la imagen y el texto)
        window.display();
    }

    // Aquí ya comenzaría el juego con los personajes
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Ken.LeerTeclado(sf::Keyboard::K);
        Pika.LeerTeclado(sf::Keyboard::F);

        Ken.Actualizar();
        Pika.Actualizar();

        Colision::manejar(Ken, Pika);

        // Comprobar si alguien ha ganado
        if (Ken.getHealth() == 0)
        {
            winner = "¡Gano Pika!";
            gameOver = true;
        }
        else if (Pika.getHealth() == 0)
        {
            winner = "¡Gano Ken!";
            gameOver = true;
        }

        window.clear();

        // Si el juego ha terminado, mostrar el mensaje de victoria
        if (gameOver)
        {
            winText.setString(winner);                                                                                                                      // Establecer el texto del ganador
            winText.setPosition(window.getSize().x / 2 - winText.getLocalBounds().width / 2, window.getSize().y / 2 - winText.getLocalBounds().height / 2); // Centrar el texto
            window.draw(winText);                                                                                                                           // Dibujar el texto de victoria
            window.display();                                                                                                                               // Mostrar el mensaje de victoria

            // Esperar un momento antes de cerrar el juego
            sf::sleep(sf::seconds(2)); // Esperar 2 segundos para que el jugador vea el mensaje de victoria

            break; // Salir del ciclo para cerrar el juego después de la victoria
        }
        else
        {
            // Si el juego no ha terminado, se sigue actualizando y dibujando los personajes
            campo.Dibujar(window);
            Ken.Dibujar(window);
            Pika.Dibujar(window);
        }

        window.display();
    }

    return 0;
}
