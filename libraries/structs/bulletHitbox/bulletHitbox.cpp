#include <bulletHitbox/bulletHitbox.hpp>
#include <reusedTextures/reusedTextures.hpp>

BulletHitbox::BulletHitbox(Bullet* bul, bool front) : owner(bul), box({0,0,0,0}) {
    float len = owner->owner->GetCenter()->y;
    box.w = owner->GetDest().w;
    box.h = box.w;
    float angle = owner->GetAngle() * (3.14f / 180);

    if (front) {
        difX = (len - box.w / 2) * SDL_cos(angle);
        difY = len * (1.0f - SDL_sin(angle)) + box.w * SDL_sin(angle) / 2;
    }
    else {
        difX = (len - 1.5 * box.w) * SDL_cos(angle);
        difY = len * (1.0f - SDL_sin(angle)) + 1.5 * box.w * SDL_sin(angle);
    }

    tex = ReusedTextures::hitboxTex;
}

void BulletHitbox::Draw() {
    TextureManager::Draw(tex, &src, &box, SDL_FLIP_NONE);
}

void BulletHitbox::Update() {
    box.x = owner->GetDest().x - difX;
    box.y = owner->GetDest().y + difY - box.w / 2;
}

void BulletHitbox::DestroyOwner() { 
#ifdef LOGS
    std::cout << "Hit" << '\n';
#endif
    owner->owner->AddBulletToDest(owner);
}
