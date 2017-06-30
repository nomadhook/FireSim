#include "fire_ca.h"

// === Public Methods ===
void FireCA::ClearSate() {
	for (int i = 0; i < dem->Size(); i++) {
		cell_state[i] = States::UNBURNED;
		cell_energy[i] = 0;
		cell_reserves[i] = cell_fuels[i].Reserve();
	}
}

void FireCA::SetAllFuelsTo(Fuel f) {
	for (int i = 0; i < dem->Size(); i++)
		cell_fuels[i] = f;
}

void FireCA::StartSimulation() {
	cell_state[cell_state.size() / 2] = States::BURNING;
}

void FireCA::UpdateState(int x, int y, float t) {
	int index = y * dem->Size(0) + x;
	switch (cell_state[index]) {
	case States::UNBURNED:
		if (cell_energy[index] > cell_fuels[index].IgnitionThreshold() &&
			cell_reserves[index] > 0)
			cell_state[index] = States::BURNING;
		break;
	case States::BURNING:
		if (cell_reserves[index] > 0)
	default:
		break;
	}
}

void FireCA::UpdateRateOfSpread(int x, int y, float t) {
	// In the equation R0 = (Ir * xi) / (Pb * eta * Qig)
	// and R0 is the rate of spread.

	// Reaction Intensity measures the energy release per
	// unit area of the fire-front (KJ m^-2 min^-1)
	float react_intensity = -1;
	// Xi is the Propagating heat flux ratio, which measures the
	// proportion of the react_intensity heating adjacent fuel
	// particles to ignition (has no dimension)
	float prop_flux_ratio = -1;
	// Pb is the fuel bulk intensity (kg m^-3)
	float fuel_bulk_intensity = -1;
	// Eta is the effective heating number, which measures
	// the proportion of a fuel particle that is heated to 
	// ignition at combustion time (has no dimenstion)
	float effective_heat_num = -1;
	// Qig is the heat of pre-ignition, which measures the quantity of
	// heat required to ignite 1kg of fuel (kJ kg^-1)
	float pre_igni_heat = -1;
	// Rate of spread is in (m min^-1)
	float rate_of_spread = (react_intensity * prop_flux_ratio) /
		(fuel_bulk_intensity * effective_heat_num * pre_igni_heat);
}
