#include <bullet/bullet.hpp>
#include <bulletHitbox/bulletHitbox.hpp>
#include <bulletsCollider/bulletsCollider.hpp>
#include <short_names/short_names.hpp>

Bullet::Bullet(Shooter* owner_) : owner(owner_) {
    angle = owner->GetAngle() + 90;

    velocity.x = owner->GetSpeed() * SDL_cos(angle * (3.14 / 180));
    velocity.y = owner->GetSpeed() * SDL_sin(angle * (3.14 / 180));
#ifdef LOGS
    std::cout << angle << '\n';
#endif
#ifdef LOGS
    std::cout << SDL_sin(angle * (3.14 / 180)) << '\n';
#endif
#ifdef LOGS
    std::cout << SDL_cos(angle * (3.14 / 180)) << '\n';
#endif
    texture = owner->GetTex();
    destFRect = owner->destFRect;
    srcFRect = owner->srcFRect;

    accuratePos.x = destFRect.x;
    accuratePos.y = destFRect.y;

    BulletHitbox* hitBox = new BulletHitbox(this, 1);
    BulletHitbox* backHitBox = new BulletHitbox(this, 0);
    if (!(owner->owner->HasComponent<BulletsCollider>())) {
        owner->owner->AddComponent<BulletsCollider>();
    }
    owner->owner->GetComponent<BulletsCollider>().AddBox(hitBox);
    owner->owner->GetComponent<BulletsCollider>().AddBox(backHitBox);
    hitbox = hitBox;
    backHitbox = backHitBox;
}
Bullet::~Bullet() {
    owner->owner->GetComponent<BulletsCollider>().DeleteBox(hitbox);
    owner->owner->GetComponent<BulletsCollider>().DeleteBox(backHitbox);
    delete hitbox;
    delete backHitbox;
#ifdef LOGS
    std::cout << "Bullet Destroyed" << '\n';
#endif
}

void Bullet::Update() {
    accuratePos.x -= velocity.x;
    accuratePos.y -= velocity.y;

    destFRect.x = std::round(accuratePos.x);
    destFRect.y = std::round(accuratePos.y);

    if (std::abs(destFRect.x) > 2000 || std::abs(destFRect.y) > 2000) {
        owner->AddBulletToDest(this);
    }

    // if (acceleration.Mod() != 0) {
    //     velocity.x += acceleration.x;
    //     velocity.y += acceleration.y;
    // }
}

void Bullet::Draw() {
    TextureManager::Draw(texture, &srcFRect, &destFRect, angle - 90, owner->GetCenter(), SDL_FLIP_NONE);
}
