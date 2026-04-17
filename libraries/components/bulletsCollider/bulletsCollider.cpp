#include <bulletsCollider/bulletsCollider.hpp>

void BulletsCollider::AddBox(BulletHitbox* box) {
    boxes.push_back(box);
}

BulletHitbox* BulletsCollider::DoesCollide(SDL_FRect* rect) {
    for (auto box = boxes.begin(); box != boxes.end(); ++box) {
        if (SDL_HasRectIntersectionFloat( (*box)->GetBox(), rect )) {
            auto ret = *box;
            boxes.erase(box);
            return ret;
        }
    }
    return nullptr;
}

void BulletsCollider::Update() {
    for (auto box : boxes) {
        box->Update();
    } 
}

void BulletsCollider::Draw() {
    if (Hitboxes::Active()) {
        for (auto box : boxes) {
            box->Draw();
        }    
    }
}

void BulletsCollider::DeleteBox(BulletHitbox* box) {
    for (auto iter = boxes.begin(); iter != boxes.end(); ++iter) {
        if (*iter == box) {
            boxes.erase(iter);
#ifdef LOGS
            std::cout << "Hitbox erased from collider" << '\n';
#endif
            return;
        }
    }
}

