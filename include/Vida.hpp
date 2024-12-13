#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Vida
{
public:
  Vida(int maxHealth, sf::Vector2f position);
  void takeDamage(int damage);
  void heal(int amount);
  void draw(sf::RenderWindow &window) const;
  int getCurrentHealth() const;

private:
  int maxHealth;
  int currentHealth;
  sf::Font font;
  sf::Text healthText;
};

Vida::Vida(int maxHealth, sf::Vector2f position)
    : maxHealth(maxHealth), currentHealth(maxHealth)
{
  // Cargar la fuente para el texto de la vida
  if (!font.loadFromFile("./assets/fonts/Minecraft.ttf"))
  {
    // Manejar el error si no se puede cargar la fuente
    throw std::runtime_error("No se pudo cargar la fuente");
  }

  // Configurar el objeto de texto que mostrará la vida
  healthText.setFont(font);
  healthText.setCharacterSize(24);         // Tamaño del texto
  healthText.setFillColor(sf::Color::Red); // Color del texto
  healthText.setPosition(position);        // Posición en la ventana
  healthText.setString(std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
}

void Vida::takeDamage(int damage)
{
  currentHealth -= damage;
  if (currentHealth < 0)
    currentHealth = 0;
  healthText.setString(std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
}

void Vida::heal(int amount)
{
  currentHealth += amount;
  if (currentHealth > maxHealth)
    currentHealth = maxHealth;
  healthText.setString(std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
}

void Vida::draw(sf::RenderWindow &window) const
{
  window.draw(healthText);
}

int Vida::getCurrentHealth() const
{
  return currentHealth;
}