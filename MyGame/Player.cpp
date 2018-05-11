#include "Player.h"
#include "Game.h"

Player::Player() {

}


Player::~Player() {

}

void Player::tick() {
	Entity::tick();

	// TODO this should be done in a INIT not TICK
	Game::renderer->camera.target = Game::world->findEntity(this);
	Game::renderer->camera.follow = true;

	//acc.set(0.0f, 0.0f);
	if (Game::input->getMovementAxes().xf() != 0)
		vel.setX(moveTo(vel.xf(), Game::input->getMovementAxes().xf() * 4, 2.0f));
	if (Game::input->getMovementAxes().yf() != 0)
		vel.setY(moveTo(vel.yf(), Game::input->getMovementAxes().yf() * 4, 2.0f));
	//if (Game::input->getRawKey(Input::RawKey::A)) {
	//	acc.setX(-2.0f);
	//}
	//if (Game::input->getRawKey(Input::RawKey::D)) {
	//	acc.setX(2.0f);
	//}
	//if (Game::input->getRawKey(Input::RawKey::W)) {
	//	acc.setY(-2.0f);
	//}
	//if (Game::input->getRawKey(Input::RawKey::S)) {
	//	acc.setY(2.0f);
	//}
}