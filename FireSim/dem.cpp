#include "dem.h"
#include <fstream>
#include <string>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

// === Member Variables Access ===
int DEM::Size() { return dem_size[0] * dem_size[1]; }
int DEM::Size(int dimension) { return dem_size[dimension]; }
int DEM::MaxElevation() { return dem_max; }
int DEM::MinElevation() { return dem_min; }
std::vector<float> DEM::Data() { return dem_data; }
float DEM::DataAt(int index) { return dem_data[index]; }
float DEM::DataAt(int x, int y) { return dem_data[y * dem_size[0] + x]; }

// === Private Methods ===

// === Public Methods ===
void DEM::LoadFromHeightmap(const char *filename, int min, int max, int scale) {
	dem_min = min;
	dem_max = max;
	std::ifstream file(filename);
	std::string line;
	unsigned short max_val = 0;
	unsigned int count = 0;
	bool color_image = false;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			if (line[0] == '#') continue;
			if (count == 0 && line == "P3") color_image = true;
			else if (count == 1) {
				dem_size[0] = stoi(line.substr(0, line.find(' ')));
				dem_size[1] = stoi(line.substr(line.find(' ') + 1));
				dem_data.resize(dem_size[0] * dem_size[1]);
			}
			else if (count == 2) max_val = stoi(line);
			else if (count > 2 && count < (dem_size[0] * dem_size[1]) + 2) {
				int val = stoi(line);
				if (color_image) {
					std::getline(file, line);
					std::getline(file, line);
				}
				float weighted_val = dem_min +
					(float)((float)val / max_val * (dem_max - dem_min));
				dem_data[count - 3] = weighted_val;
			}
			count++;
		}
	}
}

void DEM::SaveDEM(const char *filename) {
	std::ofstream file;
	file.open(filename);
	file << "P1\n";
	file << dem_size[0] << " " << dem_size[1] << "\n";
	file << dem_max << "\n";
	for (int col = 0; col < dem_size[1]; col++) {
		for (int row = 0; row < dem_size[0]; row++) {
			file << dem_data[col * dem_size[0] + row] << "\n";
		}
	}
	file.close();
}

void DEM::ShowDEM() {
#ifdef _WIN32
	std::cout << "Displaying DEM\n";
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	for (int col = 0; col < dem_size[1]; col++) {
		for (int row = 0; row < dem_size[0]; row++) {
			int val = (dem_data[col * dem_size[0] + row] - dem_min) /
				(dem_max - dem_min) * 255;
			val = (val < 0) ? 0 : (val > 255) ? 255 : val;
			SetPixel(mydc, row, col + 32, RGB(val, val, val));
		}
	}
#else
	std::cout << "Error Not Implemented for your current OS" << std::endl;
#endif // _WIN32
}