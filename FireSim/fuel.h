#ifndef FUEL_H
#define FUEL_H
#endif // !FUEL_H

class Fuel {
	// === Member Variables === 
private:
	char *fuel_class;
	float fuel_igni_thresh;
	float fuel_reserve;

	// === Member Variables Access ===
public:
	char *Classification() { return fuel_class; }
	float IgnitionThreshold() { return fuel_igni_thresh; }
	float Reserve() { return fuel_reserve; }

	// === Constructor ===
public:
	Fuel(char *_class, float _igni, float _res) {
		fuel_class = _class;
		fuel_igni_thresh = _igni;
		fuel_reserve = _res;
	}

	Fuel() { fuel_class = "None", fuel_igni_thresh = -1, fuel_reserve = -1; }
};

// === Default Fuel Types ===
class DefaultFuels {
public:
	static Fuel grass() { return Fuel("Grass", 7.0, 9.0); }
	static Fuel non_burnable() { return Fuel("Non-Burnable", 0.0, 0.0); }
};