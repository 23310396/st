#pragma once
#include <SFML/Graphics.hpp>

class Vida
{
public:
  Vida(int maxHealth, sf::Vector2f size, sf::Vector2f position);
  void takeDamage(int damage);
  void heal(int amount);
  void draw(sf::RenderWindow &window) const;
  int getCurrentHealth() const; // Nuevo método para obtener la salud actual

private:
  int maxHealth;
  int currentHealth;
  sf::RectangleShape backgroundBar;
  sf::RectangleShape healthBar;
};

Vida::Vida(int maxHealth, sf::Vector2f size, sf::Vector2f position)
    : maxHealth(maxHealth), currentHealth(maxHealth),
      backgroundBar(size), healthBar(size)
{

  backgroundBar.setPosition(position);
  backgroundBar.setFillColor(sf::Color(50, 50, 50));

  healthBar.setPosition(position);
  healthBar.setFillColor(sf::Color(100, 250, 50));
}

void Vida::takeDamage(int damage)
{
  currentHealth -= damage;
  if (currentHealth < 0)
    currentHealth = 0;

  float healthPercentage = static_cast<float>(currentHealth) / maxHealth;
  healthBar.setSize({backgroundBar.getSize().x * healthPercentage, healthBar.getSize().y});
}

void Vida::heal(int amount)
{
  currentHealth += amount;
  if (currentHealth > maxHealth)
    currentHealth = maxHealth;

  float healthPercentage = static_cast<float>(currentHealth) / maxHealth;
  healthBar.setSize({healthBar.getSize().x * healthPercentage, healthBar.getSize().y});
}

void Vida::draw(sf::RenderWindow &window) const
{
  window.draw(backgroundBar);
  window.draw(healthBar);
}

int Vida::getCurrentHealth() const
{
  return currentHealth; // Devuelve la salud actual
}