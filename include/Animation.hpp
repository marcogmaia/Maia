#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include <fmt/format.h>
#include <map>
#include <vector>

enum enum_animId_t { IDLE, UP, DOWN, LEFT, RIGHT };

class Animation : public sf::Drawable {
private:
    // sf::Image m_image;
    // sf::Texture m_texutere;
    sf::Sprite &m_sprite;

    sf::Clock m_frameClock;

    thor::FrameAnimation *m_pFrameBuffer;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    thor::Animator<sf::Sprite, enum_animId_t> animator;
    /**
     * adds frame sequence to the animation map
     * */
    Animation(sf::Sprite &sprite);
    void addFrames(int xFirst, int xLast, int y, float duration = 1.f);
    /**
     * add the sequence of frames to the animator
     * then remove the m_pFrameBuffer allocated memory
     * */
    void addToAnimator(enum_animId_t id, float duration = 0.2f);
    void playAnimation(enum_animId_t id, bool restart = false);
    void animate();
    bool isPlaying();
    void stop();
    // void play(animation_enum_t id);
};  // Animation
