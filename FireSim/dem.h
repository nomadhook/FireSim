#include "vector"

#ifndef DEM_H
#define DEM_H
#endif // !DEM_H

class DEM {
	// === Member Variables === 
private:
	int dem_size[2];
	int dem_max, dem_min;
	std::vector<float> dem_data;


	// === Member Variables Access ===
public:
	int Size();
	int Size(int dimension);
	int MaxElevation();
	int MinElevation();
	std::vector<float> Data();
	float DataAt(int index);
	float DataAt(int x, int y);

	// === Public Methods ===
	void LoadFromHeightmap(const char *filename, int min, int max, int scale);
	void SaveDEM(const char *filename);
	void ShowDEM();
};