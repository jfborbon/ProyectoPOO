#include "Player.h"

Player::Player(
    const sf::Texture& textureDown,
    const sf::Texture& textureLeft,
    const sf::Texture& textureRight,
    const sf::Texture& textureUp,
    int frameWidth, int frameHeight, int framesPerDirection, float fps) {

    animations[Direction::Down] = AnimatedSprite(textureDown, frameWidth, frameHeight, framesPerDirection, fps);
    animations[Direction::Left] = AnimatedSprite(textureLeft, frameWidth, frameHeight, framesPerDirection, fps);
    animations[Direction::Right] = AnimatedSprite(textureRight, frameWidth, frameHeight, framesPerDirection, fps);
    animations[Direction::Up] = AnimatedSprite(textureUp, frameWidth, frameHeight, framesPerDirection, fps);

    for (auto& pair : animations) {
        pair.second.setLooping(true);
        pair.second.play();
        pair.second.setPosition(0, 0); // posición inicial
    }

    currentDirection = Direction::Down;
}

void Player::update(float deltaTime) {
    animations[currentDirection].update(deltaTime);
}

void Player::move(const sf::Vector2f& direction) {
    Direction newDirection = currentDirection;
    if (direction.y < 0) newDirection = Direction::Up;
    else if (direction.y > 0) newDirection = Direction::Down;
    else if (direction.x < 0) newDirection = Direction::Left;
    else if (direction.x > 0) newDirection = Direction::Right;

    if (newDirection != currentDirection) {
        currentDirection = newDirection;
    }

    sf::Vector2f newPosition = getPosition() + direction;
    setPosition(newPosition); // Update position for all animations
    animations[currentDirection].play();
}


void Player::setPosition(const sf::Vector2f& position) {
    for (auto& pair : animations) {
        pair.second.setPosition(position);
    }
}

sf::Vector2f Player::getPosition() const {
    return animations.at(currentDirection).getPosition();
}

sf::FloatRect Player::getGlobalBounds() const {
    return animations.at(currentDirection).getGlobalBounds();
}

void Player::draw(sf::RenderWindow& window) {
    animations[currentDirection].draw(window);
}