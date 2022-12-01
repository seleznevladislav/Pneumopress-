#pragma once
#include "BuildParams.h"

struct SceneParams {
	bool doubleSided = true;
	bool edges = false;
	int lightType = 1;
	bool section = false;
	int frameTransp = 60;
	std::vector<std::uint32_t> hideIndexes = std::vector<std::uint32_t>{ CASE_ITEMNAME };
};