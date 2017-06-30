#include "dem.h"

int main() {
	DEM *dem = new DEM();
	// Elevations taken from altitude range of Cape Town
	// 0m (0ft) - 1590.4m (5217.8ft)
	dem->LoadFromHeightmap("Heightmap.ppm", 0, 1590, 30);
	dem->ShowDEM();
	dem->SaveDEM("output.ppm");
}