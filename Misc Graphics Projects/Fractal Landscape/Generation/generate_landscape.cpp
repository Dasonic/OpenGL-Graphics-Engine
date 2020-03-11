#include <fstream>
#include <string>
#include "FastNoise.h"

using namespace std;


void generate_terrain(float heightMap[][97], int seed) {
	FastNoise myNoise; // Create a FastNoise object
	myNoise.SetNoiseType(FastNoise::Perlin); // Set the desired noise type
	myNoise.SetSeed(seed);
	myNoise.SetFrequency(0.065);
	// myNoise.SetInterp(FastNoise::Hermite);

	for (int x = 0; x < 129; x++) {
		for (int y = 0; y < 97; y++) {
			heightMap[x][y] = myNoise.GetNoise(x,y);
		}
	}

	return;
}

void write_to_file(string filename, float heightMap[][97]) {
	ofstream generation_file;
	generation_file.open (filename + ".txt");
	for (int x = 0; x < 129; x++) {
		for (int y = 0; y < 97; y++) {
			generation_file << heightMap[x][y] << " ";
		}
		generation_file << endl;
	}
	generation_file.close();
	return;
}

int main(int argc, char** argv) {
	float heightMap[129][97]; // 2D heightmap to create terrain
	int seed = argc == 1 ? 1337 : atoi(argv[1]);
	generate_terrain(heightMap, seed);
	write_to_file("../Landscape/test_landscape", heightMap);
	return 0;
}