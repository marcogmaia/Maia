#include "Player.hpp"


#define ASSETS_PATH                                                            \
    "/home/marco/dev/cpp/games/maia/assets/Commissions/Paladin32x.png"
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32


Player::Player() {
    animSprite = AnimatedSprite();
    m_mapAnimation[DOWN] = Animation();
    m_mapAnimation[LEFT] = Animation();
    m_mapAnimation[RIGHT] = Animation();
    m_mapAnimation[UP] = Animation();

    m_texture.loadFromFile(ASSETS_PATH);
    /**
     * AnimatedSprite only takes care of the animation
     * of the Animation class
     *
     * We need a animation for each of the player animation
     * */
    for(auto &&i : m_mapAnimation) {
        i.second.setSpriteSheet(m_texture);
    }
    auto setFrames = [](Animation &anim, sf::Vector2i initialPos) {
        sf::IntRect rect;
        for(int i = 0; i < 4; ++i) {
            rect.left = initialPos.x + i * SPRITE_WIDTH;
            rect.top = initialPos.y;
            rect.width = SPRITE_WIDTH;
            rect.height = SPRITE_HEIGHT;
            anim.addFrame(rect);
        }
    };
    setFrames(m_mapAnimation[DOWN], sf::Vector2i(0, 0));
    setFrames(m_mapAnimation[LEFT], sf::Vector2i(0, SPRITE_HEIGHT * 1));
    setFrames(m_mapAnimation[RIGHT], sf::Vector2i(0, SPRITE_HEIGHT * 2));
    setFrames(m_mapAnimation[UP], sf::Vector2i(0, SPRITE_HEIGHT * 3));
    /**
     * once with all the animations set up
     * we can can use AnimatedSprite
     * this class only takes care of the animations
     */
}

Player::~Player() {}

void Player::walk() {
    float velocity = 1.f;
    static bool moved = false;
    direction_t direction = UP;
    sf::Vector2f movement(0.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        direction = UP;
        movement.y -= velocity;
        moved = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        direction = LEFT;
        movement.x -= velocity;
        moved = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        direction = DOWN;
        movement.y += velocity;
        moved = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        direction = RIGHT;
        movement.x += velocity;
        moved = true;
    }
    if(moved) {
        if(!animSprite.isPlaying()) {
            animSprite.setAnimation(m_mapAnimation[direction]);
            animSprite.play();
        }
        animSprite.move(movement);
        moved = false;
    }
    else if(animSprite.isPlaying()) {
        animSprite.stop();
    }

    // else if(moved) {
    //     animSprite.move(movement);
    // }
    // else {
    //     moved = false;
    //     animSprite.stop();
    // }
}
