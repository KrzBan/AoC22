#include "d1.h"

#include "common.h"

namespace aoc {

	void d1() {
		std::ifstream input(aoc::GetInputPath("input01.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		std::vector<uint32_t> elfCalories;
		uint32_t currentCalories = 0;

		std::string line;
		while (std::getline(input, line)) {
			
			std::stringstream ss{ line };

			uint32_t calories = 0;
			if (ss >> calories) {
				currentCalories += calories;
			}
			else {
				elfCalories.push_back(currentCalories);
				currentCalories = 0;
			}
		}

		// Final dump
		elfCalories.push_back(currentCalories);

		std::ranges::sort(elfCalories, std::greater<>());

		if (elfCalories.size() < 3) {
			throw std::runtime_error("Too few elfs! At least 3 are required!");
		}

		std::cout << "First max value is: " << elfCalories[0] << '\n';
		std::cout << "Second max value is: " << elfCalories[1] << '\n';
		std::cout << "Third max value is: " << elfCalories[2] << '\n';

		auto range = std::ranges::views::take(elfCalories, 3);
		uint32_t sum = std::accumulate(range.begin(), range.end(), uint32_t{ 0 });
		std::cout << "3 most rich elfs collectively have: " << sum << " calories!\n";
	}

}