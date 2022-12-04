#include "d3.h"

#include "common.h"

namespace aoc {

	char FindConsecutive(std::span<char> data, uint32_t n) {

		if (n <= 1) throw std::runtime_error("FindConsecutive(): n must be larger than 1!");

		char last{};
		uint32_t counter{};
		for (const auto& elem : data) {
			if (elem == last) ++counter;
			else counter = 0;

			if (counter == n - 1) return elem;

			last = elem;
		}

		return '\0';
	}

	uint32_t CharToPrio(char c) {
		if (c >= 'a' and c <= 'z') {
			return static_cast<uint32_t>(c - 'a') + 1;
		}
		if (c >= 'A' and c <= 'Z') {
			return static_cast<uint32_t>(c - 'A') + 27;
		}

		throw std::runtime_error("CharToPrio(): Unknown character!");
	}

	void d3() {
		std::ifstream input(aoc::GetInputPath("input03.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		uint32_t prioSum = 0;

		std::string line{};
		std::vector<char> intersection{};
		uint32_t counter = 0;
		while (std::getline(input, line)) {
			
			std::ranges::sort(line);
			auto uniq = std::ranges::unique(line);
			std::copy( line.begin(), uniq.begin(), std::back_inserter(intersection));

			++counter;
			if (counter == 3) {
				// Dump
				std::ranges::sort(intersection);
				char result = FindConsecutive(intersection, 3);

				prioSum += CharToPrio(result);

				// Rest
				intersection.clear();
				counter = 0;
			}
		}

		std::cout << "Sum of priorities is: " << prioSum << '\n';
	}
}