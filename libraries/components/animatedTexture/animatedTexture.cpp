#include <animatedTexture/animatedTexture.hpp>
#include <texture_manager/texture_manager.hpp>
#include <position/position.hpp>

AnimatedTexture::AnimatedTexture(std::string texName) {
    tex = TextureManager::LoadTexture(texName.data());
}
AnimatedTexture::AnimatedTexture(SDL_Texture* texName) {
    tex = texName;
    texIsShared = 1;
}


void AnimatedTexture::AddAnimation(std::string name, int idx, int frames, int speed) {
    animations.insert({name, Animation(idx, frames, speed)});
}

void AnimatedTexture::Update() {
    destFRect.x = (int)owner->GetComponent<PositionComponent>().X();
    destFRect.y = (int)owner->GetComponent<PositionComponent>().Y();
    if (speed == 0) {
#ifdef LOGS
        std::cerr << "Animation is not set!" << '\n';
#endif
        return;
    }
    srcFRect.x = srcFRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

    srcFRect.y = animIndex * srcFRect.h;
}

void AnimatedTexture::Play(std::string animName) {
    frames = animations[animName].frames;
    speed = animations[animName].speed;
    animIndex = animations[animName].index;
}
