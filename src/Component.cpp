#include "Component.h"
#include "Game.h" // TODO remove this

Component::Component() {
    executionOrder = 0;
    active = true;
    Game::logger << "Creating a component.\n";
}

Component::~Component() {
    Game::logger << "Destroying a component.\n";
}

void Component::init() {

}

void Component::destroy() {

}

void Component::pretick() {

}

void Component::tick() {

}

void Component::posttick() {

}