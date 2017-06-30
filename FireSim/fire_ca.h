#include "dem.h"
#include "fuel.h"
#include "vector"

#ifndef FIRE_CA_H
#define FIRE_CA_H
#endif // !FIRE_CA_H

enum class States { UNBURNED, BURNING, BURNED };

class FireCA {
	// === Member Variables ===
private:
	DEM *dem;
	std::vector<States> cell_state;
	std::vector<Fuel> cell_fuels;
	std::vector<float> cell_energy;
	std::vector<float> cell_reserves;

	// === Constructor ===
public:
	FireCA(DEM *_dem) {
		dem = _dem;
		cell_state.resize(dem->Size());
		cell_fuels.resize(dem->Size());
		cell_energy.resize(dem->Size());
		cell_reserves.resize(dem->Size());
		ClearSate();
		SetAllFuelsTo(DefaultFuels::grass());
	}

	// === Public Methods ===
public:
	void ClearSate();
	void SetAllFuelsTo(Fuel f);
	void FireCA::StartSimulation();
	void UpdateState(int x, int y, float t);
	void UpdateRateOfSpread(int x, int y, float t);
};