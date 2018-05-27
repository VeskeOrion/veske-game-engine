#include "Collision.h"


Terrain::Terrain() {
	init();
}


Terrain::~Terrain() {

}


void Terrain::init() {
	resolution = 1;
	heightMap.clear();

	startPos.reset();
	orientation = Orientation::ORIENTATION_UP;
}


void Terrain::readFromFile() {
	heightMap.clear();
	resolution = 1;
}


void Terrain::generateRandomSmoothTerrain(int len, int res) {
	resolution = res;
	heightMap.clear();
	heightMap.reserve(len);

	int currentHeight = 0;
	for (int i = 0; i < len; ++i) {
		heightMap.push_back(currentHeight);

		if (random() < 1.0f/3.0f)
			++currentHeight;
		if (random() < 1.0f/3.0f)
			--currentHeight;
	}
}



Collision::Collision() {

}


Collision::~Collision() {

}
