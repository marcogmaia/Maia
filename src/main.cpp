#include "Player.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <mutex>
#include <thread>

#define WINDOW_NAME "Maia"

// void moveWASD(sf::Transformable &shape) {
//     float velocity = 1;
//     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
//         shape.move(0.0, -velocity);
//     }
//     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
//         shape.move(-velocity, 0.0);
//     }
//     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
//         shape.move(0.0, velocity);
//     }
//     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
//         shape.move(velocity, 0.0);
//     }
// }

void threadRender() {
    sf::RenderWindow window(sf::VideoMode(600, 600), WINDOW_NAME,
        sf::Style::Close | sf::Style::Default);
    window.setFramerateLimit(220);

    Player player;
    sf::Clock clock;

    while(window.isOpen()) {
        sf::Time frameTime = clock.restart();
        sf::Event event;
        sf::FloatRect visibleArea;
        while(window.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
            case sf::Event::Resized:
                visibleArea
                    = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                break;
            default:
                break;
            }
        }

        player.walk();
        player.animSprite.update(frameTime);


        window.clear();
        window.draw(player.animSprite);
        window.display();
    }
}

void threadPythonTest(int argc, char const *argv[]);

int main(int argc, char const *argv[]) {
    std::thread renderThread(threadRender);
    std::thread pythonThread(threadPythonTest, argc, argv);
    pythonThread.join();
    renderThread.join();
    return 0;
}
