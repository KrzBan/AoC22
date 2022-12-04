#include "d4.h"

#include "common.h"

namespace aoc {

	void d4() {
		std::ifstream input(aoc::GetInputPath("input04.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		uint32_t sum = 0;

		std::string line{};
		while (std::getline(input, line)) {
			
			std::vector<uint32_t> ranges{};
			for (const auto& pair : line | std::views::split(',')) {
				for (const auto& elem : pair | std::views::split('-')) {
					const std::string_view sv(elem.begin(), elem.end());

					uint32_t result{};
					std::from_chars(sv.data(), sv.data() + sv.size(), result);
					ranges.push_back(result);
				}
			}

			assert(ranges.size() == 4);

			if ( (ranges[0] <= ranges[2] and ranges[1] >= ranges[2]) or 
				 (ranges[2] <= ranges[0] and ranges[3] >= ranges[0])) {
				++sum;
			}
		}

		std::cout << "Sum of redundant ranges is: " << sum << '\n';
	}
}