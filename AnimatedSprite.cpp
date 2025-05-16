#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
    : frameTime(0.f), currentTime(0.f), currentFrame(0), playing(false), looping(true) {}

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float framesPerSecond)
    : currentTime(0.0f), currentFrame(0), playing(true), looping(true) {

    frameTime = 1.0f / framesPerSecond;
    sprite.setTexture(texture);

    for (int i = 0; i < frameCount; i++) {
        frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }

    sprite.setTextureRect(frames[0]);
    sprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);
}

void AnimatedSprite::update(float deltaTime) {
    if (!playing) return;

    currentTime += deltaTime;

    if (currentTime >= frameTime) {
        currentTime -= frameTime;
        currentFrame++;

        if (currentFrame >= frames.size()) {
            if (looping) {
                currentFrame = 0;
            } else {
                currentFrame = frames.size() - 1;
                playing = false;
            }
        }

        sprite.setTextureRect(frames[currentFrame]);
    }
}

void AnimatedSprite::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void AnimatedSprite::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

sf::Vector2f AnimatedSprite::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void AnimatedSprite::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void AnimatedSprite::play() {
    playing = true;
}

void AnimatedSprite::pause() {
    playing = false;
}

void AnimatedSprite::stop() {
    playing = false;
    currentFrame = 0;
    if (!frames.empty()) {
        sprite.setTextureRect(frames[0]);
    }
}

void AnimatedSprite::setLooping(bool loop) {
    looping = loop;
}

void AnimatedSprite::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}