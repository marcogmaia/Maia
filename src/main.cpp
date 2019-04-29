#include "Player.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <fmt/format.h>
#include <mutex>
#include <thread>

#define WINDOW_NAME "Maia"

void gamePollEvents(sf::RenderWindow *window) {
    sf::Event event;
    sf::FloatRect visibleArea;
    while(window->pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape) {
                window->close();
            }
            break;
        case sf::Event::Resized:
            visibleArea
                = sf::FloatRect(0, 0, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
            break;
        default:
            break;
        }
    }
}

void threadRender(sf::RenderWindow *window) {
    window->setActive();
    window->setFramerateLimit(220);
    sf::Vector2f pos = sf::Vector2f(window->getSize());

    Player *player = Player::getInstance();
    player->animSprite.setPosition(pos / 2.f);

    sf::Clock frameClock;

    while(window->isOpen()) {
        gamePollEvents(window);

        sf::Time frameTime = frameClock.restart();
        player->walk();
        player->animSprite.update(frameTime);

        window->clear();
        window->draw(player->animSprite);
        window->display();
    }
}

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(
        sf::VideoMode(640, 480), WINDOW_NAME, sf::Style::Default);
    window.setActive(false);

    std::vector<std::thread> vectorThread;
    vectorThread.push_back((std::thread(threadRender, &window)));

    std::for_each(std::begin(vectorThread), std::end(vectorThread),
        [](std::thread &i) { i.join(); });

    return 0;
}
