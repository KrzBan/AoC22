#include "d6.h"

#include "common.h"

namespace aoc {

	void d6() {
		std::ifstream input(aoc::GetInputPath("input06.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		constexpr uint32_t n = 14;

		char c;
		std::deque<char> window{};
		while (input >> c) {
			window.push_back(c);
			if (window.size() == n - 1) break;
		}

		uint32_t counter = n-1;
		while (input >> c) {
			++counter;
			window.push_back(c);

			std::set<char> key{window.begin(), window.end()};
			if (key.size() == n) {
				break;
			}

			window.pop_front();
		}

		std::cout << "Counter position is: " << counter << '\n';
	}
}