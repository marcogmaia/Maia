#include "Player.hpp"
#include <Animation.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <fmt/format.h>
#include <mutex>
#include <thread>

#define WINDOW_NAME "Maia"

static const int sprite_width  = 32;
static const int sprite_height = 32;

void addFrames(thor::FrameAnimation &animation, int y, int xFirst, int xLast,
    float duration = 1.f) {
    const int step = (xFirst < xLast) ? 1 : -1;
    xLast += step;

    thor::FrameAnimation frames;
    for(int x = xFirst; x != xLast; x += step) {
        sf::IntRect rect(
            sprite_width * x, sprite_height * y, sprite_width, sprite_height);
        fmt::print("Rect: p({:>2}, {:>2}), size: s({:>2}, {:>2})\n", rect.left,
            rect.top, rect.width, rect.height);
        frames.addFrame(duration, rect);
    }
}

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
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(220);


    // Animation animation;
    // animation.addFrames(0, 3, 0);
    // animation.addToAnimator(UP, 2);
    // animation.playAnimation(UP);

    Player *player = Player::getInstance();

    sf::Clock frameTime;
    while(window->isOpen()) {
        gamePollEvents(window);

        // animator.update(frameTime.restart());
        // animator.animate(sprite);
        // animation.animate();
        player->walk();
        player->updateAnimation();

        window->clear(sf::Color(50, 50, 50));
        window->draw(*player);
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
