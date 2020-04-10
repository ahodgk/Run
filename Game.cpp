//
// Created by hodgk on 08/04/2020.
//
#include "Game.h"

void Game::reset() {
    obstacleDistance = 400;

    // Resets speed etc
    player = Player(190.f, 30.f);
    Obstacle::speed = 250.f;

    // loss/start text
    menuText.setFont(font);
    menuText.setString("Space to start");
    menuText.setCharacterSize(56);
    menuText.setFillColor(sf::Color::Magenta);
    menuText.setPosition(300, 100);

    score = 0;
    scoreText.setString(std::to_string(score));

    // Generate obstacles

    obstacles[0] = Obstacle(window.getSize().x, floor.getPosition().y);
    for (int i = 1; i < 20; ++i) {
        obstacles[i] = Obstacle(obstacles[i - 1].x + obstacleDistance, floor.getPosition().y);
    }
}

Game::Game() {
    player = Player(190.f, 30.f);

    // Creates main window
    window.create(sf::VideoMode(800, 250), "Window innit", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setActive(false);

    // Creates floor object
    floor.setSize(sf::Vector2f(window.getSize().x, window.getSize().y - (player.y + player.width)));
    floor.setPosition(0, player.y + player.width);
    floor.setFillColor(sf::Color::Green);


    if (!font.loadFromFile("assets/Premier.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    scoreText.setFont(font);

    scoreText.setCharacterSize(56);
    scoreText.setFillColor(sf::Color::Magenta);
    scoreText.setStyle(sf::Text::Bold);

    // initialises game
    reset();
    // Starts threads
    renderThread = std::thread(&Game::launchGameLoop, this);
    logicThread = std::thread(&Game::doLogic, this);

    // Event loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
                renderThread.join();
                logicThread.join();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                player.jump();
                if (!started) reset();
                started = true;


            }
        }
    }
}

void Game::doLogic() {
    std::chrono::high_resolution_clock::time_point then = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point now;

    while (window.isOpen()) {
        now = std::chrono::high_resolution_clock::now();
        double delta = std::chrono::duration_cast<std::chrono::duration<double>>(now - then).count();
        if (delta < 0.005) continue;
        then = now;
        if (!started) continue;


        // Stuff
        player.updateMovement(delta);
        if (player.y + player.width > floor.getPosition().y) {
            player.onFloor(floor);
        }
        // move obstacles
        for (int i = 0; i < 20; ++i) {
            obstacles[i].move(delta);
            if (obstacles[i].x + obstacles[i].width < 0) { // if off-screen
                score++;
                scoreText.setString(std::to_string(score));
                for (int j = 0; j < 19; ++j) { // shift them all down a place
                    obstacles[j] = obstacles[j + 1];
                }
                obstacles[19] = Obstacle(obstacles[18].x + obstacleDistance, floor.getPosition().y);
                obstacleDistance -= 2;
                Obstacle::speed += 3;
                player.levelUp();
                i--;
            }
        }
        for (int i = 0; i < 5; ++i) {
            if (player.collides(&obstacles[i].rect)) {
                std::cout << "LOSE";
                lose();
            }
        }
    }
}

void Game::lose() {
    started = false;
    menuText.setString("You lose\n ");

}

void Game::launchGameLoop() {
    window.setActive(true);
    while (window.isOpen()) {
        Sleep(1);
        //doLogic();
        window.clear(sf::Color::White);
        // draw game world

        window.draw(floor);
        player.draw(&window);
        for (int i = 0; i < 20; ++i) {
            obstacles[i].draw(&window);
        }
        window.draw(scoreText);
        if (!started) window.draw(menuText);
        window.display();
    }
    //.join();
}