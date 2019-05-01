#include <Animation.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors.hpp>

static const int sprite_width  = 32;
static const int sprite_height = 32;

#define TEXTURE_PATH                                                           \
    "/home/marco/dev/cpp/games/maia/assets/Commissions/Paladin32x.png"


void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

Animation::Animation(sf::Sprite &sprite)
    : m_sprite(sprite)
    , m_pFrameBuffer(nullptr) {
    // m_image.loadFromFile(TEXTURE_PATH);
    // m_texutere.loadFromImage(m_image);
    // m_sprite.setTexture(m_texutere);
    m_sprite.setPosition(100, 100);
};

/**
 * @brief Adds a range of frames, assuming they are aligned as rectangles
 * in the texture
 *
 * @param animation Frame animation to modify
 * @param [xFirst, xLast]: bounds for columns indices
 * (if xLast < xFirst, add frames in reverse order)
 * @param y index of the texture rectangle
 * @param duration Relative duration of current frame (1 default)
 * */
void Animation::addFrames(int xFirst, int xLast, int y, float duration) {
    const int step = (xFirst < xLast) ? 1 : -1;
    xLast += step;

    // thor::FrameAnimation frames;
    if(m_pFrameBuffer == nullptr) {
        m_pFrameBuffer = new thor::FrameAnimation();
    }

    for(int x = xFirst; x != xLast; x += step) {
        sf::IntRect rect(
            sprite_width * x, sprite_height * y, sprite_width, sprite_height);
        fmt::print("Rect: p({:>2}, {:>2}), size: s({:>2}, {:>2})\n", rect.left,
            rect.top, rect.width, rect.height);
        m_pFrameBuffer->addFrame(duration, rect);
    }
}

void Animation::addToAnimator(enum_animId_t id, float duration) {
    animator.addAnimation(id, *m_pFrameBuffer, sf::seconds(duration));
    delete m_pFrameBuffer;
    m_pFrameBuffer = nullptr;
}

void Animation::playAnimation(enum_animId_t id, bool restart) {
    if(restart || !animator.isPlayingAnimation()) {
        animator.playAnimation(id);
    }
}

void Animation::animate() {
    animator.update(m_frameClock.restart());
    animator.animate(m_sprite);
}

bool Animation::isPlaying() {
    return animator.isPlayingAnimation();
}

void Animation::stop() {
    // animator.playAnimation(IDLE);
    animator.stopAnimation();
}