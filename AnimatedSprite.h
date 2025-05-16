#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class AnimatedSprite {
public:
    AnimatedSprite();
    AnimatedSprite(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float framesPerSecond);

    void update(float deltaTime);
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void draw(sf::RenderWindow& window);
    void play();
    void pause();
    void stop();
    void setLooping(bool loop);
    void setScale(float scaleX, float scaleY);

private:
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    float frameTime;
    float currentTime;
    int currentFrame;
    bool playing;
    bool looping;
};