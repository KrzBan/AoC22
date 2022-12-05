#include "d5.h"

#include "common.h"

namespace aoc {

	bool IsCrate(char c) {
		return c >= 'A' and c <= 'Z';
	}

	bool IsDigit(char c) {
		return c >= '0' and c <= '9';
	}

	using CraneOp = std::tuple<uint32_t, uint32_t, uint32_t>;

	CraneOp ParseLine(const std::string& line) {
		
		const auto* begin	= line.data();
		const auto* end		= line.data() + line.size();

		auto numIt = std::find_if(begin, end, IsDigit);
		uint32_t moveCount{};
		auto lastFind = std::from_chars(numIt, end, moveCount);

		numIt = std::find_if(lastFind.ptr, end, IsDigit);
		uint32_t craneSrc{};
		lastFind = std::from_chars(numIt, end, craneSrc);

		numIt = std::find_if(lastFind.ptr, end, IsDigit);
		uint32_t craneDst{};
		lastFind = std::from_chars(numIt, end, craneDst);

		return { moveCount, craneSrc - 1, craneDst - 1 };	// To 0-Indexed
	}

	void d5() {
		std::ifstream input(aoc::GetInputPath("input05.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		std::vector<std::deque<char>> cranes{};

		std::string line{};
		// Read cranes
		while (std::getline(input, line)) {
			if (line == "") break;

			uint32_t counter{};
			for (const auto& c : line) {
				if (aoc::IsCrate(c)) {
					uint32_t craneId = counter / 4;

					if (craneId >= cranes.size()) {
						cranes.resize(craneId + 1);
					}
					cranes.at(craneId).push_front(c);
				}

				++counter;
			}
		}

		// Read crane movements
		while (std::getline(input, line)) {

			const auto [ count, craneSrc, craneDst ] = ParseLine(line);

			std::deque<char> moveCrane{};
			for (size_t i = 0; i < count; ++i) {
				if (cranes.at(craneSrc).empty()) break;

				auto crate = cranes.at(craneSrc).back();
				cranes.at(craneSrc).pop_back();

				moveCrane.push_front(crate);
			}

			for (const auto& crate : moveCrane) {
				cranes.at(craneDst).push_back(crate);
			}
		}

		std::cout << "Top crates are:";
		for (const auto& crane : cranes) {
			std::string val = crane.empty() ? "[]" : std::string{ crane.back() };
			std::cout << val;
		}
		std::cout << '\n';
	}
}