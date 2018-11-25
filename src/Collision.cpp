#include "Collision.h"


Collision::Collision() {
    init();
}


Collision::Collision(std::vector<std::shared_ptr<Entity>> & entities) {
    this->entities = entities;
}


Collision::~Collision() {
    destroy();
}


void Collision::init() {
    
}

void Collision::destroy() {

}