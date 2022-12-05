#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <map>
#include <charconv>
#include <cassert>
#include <deque>

namespace aoc {

	const std::string inputPath = "lib/inputs/";

	inline std::string GetInputPath(const std::string& inputFile) {
		return inputPath + inputFile;
	}
}