#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

namespace aoc {

	const std::string inputPath = "lib/inputs/";

	inline std::string GetInputPath(const std::string& inputFile) {
		return inputPath + inputFile;
	}
}