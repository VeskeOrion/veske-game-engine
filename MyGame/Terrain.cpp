#include "Terrain.h"


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
	
	collisionType = KINEMATIC;
}


void Terrain::readFromFile() {
	heightMap.clear();
	resolution = 1;
}


void Terrain::generateRandomSmoothTerrain(unsigned int len, unsigned int res) {
	resolution = res;
	heightMap.clear();
	heightMap.reserve(len);

	unsigned int currentHeight = 1;
	unsigned int maxHeight = 1;
	float smoothener = 10.0f;
	for (unsigned int i = 0; i < len; ++i) {
		heightMap.push_back(currentHeight);


		if (random() < 1.0f / (10.0f + smoothener)) {
			++currentHeight;
			smoothener += 10.0f;
		}
		if (random() < 1.0f / (10.0f + smoothener) && currentHeight > 1) {
			--currentHeight;
			smoothener += 10.0f;
		}

		if (smoothener > 1.0f)
			--smoothener;

		if (currentHeight > maxHeight)
			maxHeight = currentHeight;
	}

	size.set((float) len * res, (float) maxHeight);
}


void Terrain::generateFlatTerrain(unsigned int len, unsigned int res) {
	resolution = res;
	heightMap.clear();
	heightMap.reserve(len);

	for (unsigned int i = 0; i < len; ++i) {
		heightMap.push_back(1);
	}

	size.set((float) len*res, (float) 1);
}