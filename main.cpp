#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego con Hormiga Animada");
    window.setFramerateLimit(60);
    sf::Clock clock;

    // Cargar texturas
    sf::Texture textureDown;
    if (!textureDown.loadFromFile("Ray_caminadoFrente.png")) {
        std::cout << "Error al cargar textura hacia abajo." << std::endl;
        return -1;
    }

    sf::Texture textureLeft;
    if (!textureLeft.loadFromFile("Ray_caminadoIzq.png")) {
        std::cout << "Error al cargar textura izquierda." << std::endl;
        return -1;
    }

    sf::Texture textureRight;
    if (!textureRight.loadFromFile("Ray_caminadoDer.png")) {
        std::cout << "Error al cargar textura derecha." << std::endl;
        return -1;
    }

    sf::Texture textureUp;
    if (!textureUp.loadFromFile("Ray_caminadoAtras.png")) {
        std::cout << "Error al cargar textura arriba." << std::endl;
        return -1;
    }

    // Crear jugador
    Player* player = new Player(textureDown, textureLeft, textureRight, textureUp, 32, 32, 7, 8);
    player->setPosition({400.0f, 300.0f});

    // Configurar bordes del mapa
    float playerSpeed = 2.0f;
    sf::RectangleShape mapBorders[4];

    // Bordes superiores e inferiores
    mapBorders[0].setSize({800.0f, 20.0f});
    mapBorders[0].setPosition(0.0f, 0.0f);
    mapBorders[0].setFillColor(sf::Color(100, 100, 100));

    mapBorders[1].setSize({800.0f, 20.0f});
    mapBorders[1].setPosition(0.0f, 580.0f);
    mapBorders[1].setFillColor(sf::Color(100, 100, 100));

    // Bordes laterales
    mapBorders[2].setSize({20.0f, 600.0f});
    mapBorders[2].setPosition(0.0f, 0.0f);
    mapBorders[2].setFillColor(sf::Color(100, 100, 100));

    mapBorders[3].setSize({20.0f, 600.0f});
    mapBorders[3].setPosition(780.0f, 0.0f);
    mapBorders[3].setFillColor(sf::Color(100, 100, 100));

    // Obstáculos
    const int numObstacles = 5;
    sf::RectangleShape obstacles[numObstacles];

    obstacles[0].setSize({100.0f, 100.0f});
    obstacles[0].setPosition(100.0f, 100.0f);
    obstacles[0].setFillColor(sf::Color(50, 150, 50));

    obstacles[1].setSize({200.0f, 50.0f});
    obstacles[1].setPosition(300.0f, 200.0f);
    obstacles[1].setFillColor(sf::Color(50, 150, 50));

    obstacles[2].setSize({50.0f, 150.0f});
    obstacles[2].setPosition(600.0f, 100.0f);
    obstacles[2].setFillColor(sf::Color(50, 150, 50));

    obstacles[3].setSize({150.0f, 50.0f});
    obstacles[3].setPosition(200.0f, 400.0f);
    obstacles[3].setFillColor(sf::Color(50, 150, 50));

    obstacles[4].setSize({100.0f, 100.0f});
    obstacles[4].setPosition(500.0f, 400.0f);
    obstacles[4].setFillColor(sf::Color(50, 150, 50));

    // Bucle principal
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento del jugador
        sf::Vector2f previousPosition = player->getPosition();
        sf::Vector2f movement(0.0f, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) movement.y -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) movement.y += playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) movement.x -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movement.x += playerSpeed;

        if (movement != sf::Vector2f(0.f, 0.f)) {
            player->move(movement);
        }
        player->update(deltaTime);

        // Detección de colisiones
        bool collision = false;
        for (int i = 0; i < 4; i++) {
            if (player->getGlobalBounds().intersects(mapBorders[i].getGlobalBounds())) {
                collision = true;
                break;
            }
        }

        for (int i = 0; i < numObstacles; i++) {
            if (player->getGlobalBounds().intersects(obstacles[i].getGlobalBounds())) {
                collision = true;
                break;
            }
        }

        if (collision) {
            player->setPosition(previousPosition);
        }

        // Renderizado
        window.clear(sf::Color(200, 200, 255));

        // Dibujar bordes
        for (int i = 0; i < 4; i++) {
            window.draw(mapBorders[i]);
        }

        // Dibujar obstáculos
        for (int i = 0; i < numObstacles; i++) {
            window.draw(obstacles[i]);
        }

        // Dibujar jugador
        player->draw(window);

        window.display();
    }

    delete player;
    return 0;
}