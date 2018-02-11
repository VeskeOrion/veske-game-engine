#include "Player.h"
#include "Game.h"

Player::Player() {

}


Player::~Player() {

}

void Player::tick() {
	Entity::tick();


	acc.set(0.0f, 0.0f);
	if (Game::input->getKeyDown(Key::A)) {
		acc.setX(-0.5f);
	}
	if (Game::input->getKeyDown(Key::D)) {
		acc.setX(0.5f);
	}
	if (Game::input->getKeyDown(Key::W)) {
		acc.setY(-0.5f);
	}
	if (Game::input->getKeyDown(Key::S)) {
		acc.setY(0.5f);
	}
}