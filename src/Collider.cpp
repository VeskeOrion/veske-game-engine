#include <list>

#include "Collider.h"
#include "Game.h" // TODO remove this

Collider::Collider() {
    
}

Collider::~Collider() {

}

void Collider::init() {

}

void Collider::destroy() {

}

void Collider::pretick() {

}

void Collider::tick() {

}

void Collider::posttick() {

}

bool Collider::broadIsColliding(Collider * col) {
    auto eLock = entity.lock();
    auto cLock = col->entity.lock();
    if (eLock && cLock) {
        bool xcontains = (eLock->pos.x() <= cLock->pos.x() && cLock->pos.x() < eLock->pos.x() + this->aabb.x()) ||
					     (cLock->pos.x() <= eLock->pos.x() && eLock->pos.x() < cLock->pos.x() + col->aabb.x());
        bool ycontains = (eLock->pos.y() <= cLock->pos.y() && cLock->pos.y() < eLock->pos.y() + this->aabb.y()) ||
					     (cLock->pos.y() <= eLock->pos.y() && eLock->pos.y() < cLock->pos.y() + col->aabb.y());

	    return xcontains && ycontains;
    }
    return false;
}

// std::list<Vector> Collider::getAxes(Collider * col) {
//     std::list<Vector> axes;

//     // generic AABB collider has x-axis and y-axis aligned axes
//     Vector x(1, 0);
//     Vector y(0, 1);
//     axes.push_back(x);
//     axes.push_back(y);

//     return axes;
// }