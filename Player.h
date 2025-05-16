#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"
#include <map>
#include <SFML/Graphics.hpp> // Asegúrate de incluir esto

enum class Direction {
    Down,
    Left,
    Right,
    Up
};

class Player {
public:
    Player(
        const sf::Texture& textureDown,
        const sf::Texture& textureLeft,
        const sf::Texture& textureRight,
        const sf::Texture& textureUp,
        int frameWidth, int frameHeight, int framesPerDirection, float fps);

    void update(float deltaTime);
    void move(const sf::Vector2f& direction);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void draw(sf::RenderWindow& window);

private:
    std::map<Direction, AnimatedSprite> animations;
    Direction currentDirection;
};

#endif //PLAYER_H