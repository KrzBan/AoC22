#include "d8.h"

#include "common.h"

namespace aoc {

	using Trees = std::vector<std::vector<uint8_t>>;

	uint32_t ScenicRight(const Trees& trees, size_t rowId, size_t colId) {
		const auto& row = trees[rowId];
		const auto val = row[colId];
		++colId;
		uint32_t treeCounter{};
		while (colId < row.size()) {
			++treeCounter;
			if (trees[rowId][colId] >= val) break;
			++colId;
		}
		return treeCounter;
	}
	uint32_t ScenicDown(const Trees& trees, size_t rowId, size_t colId) {
		const auto& row = trees[rowId];
		const auto val = row[colId];

		++rowId;
		uint32_t treeCounter{};
		while (rowId < trees.size()) {
			++treeCounter;
			if (trees[rowId][colId] >= val) break;
			++rowId;
		}
		return treeCounter;
	}
	uint32_t ScenicLeft(const Trees& trees, size_t rowId, size_t colId) {
		const auto& row = trees[rowId];
		const auto val = row[colId];

		uint32_t treeCounter{};
		while (colId > 0) {
			++treeCounter;
			--colId;
			if (trees[rowId][colId] >= val) break;
		}
		return treeCounter;
	}
	uint32_t ScenicUp(const Trees& trees, size_t rowId, size_t colId) {
		const auto& row = trees[rowId];
		const auto val = row[colId];

		uint32_t treeCounter{};
		while (rowId > 0) {
			++treeCounter;
			--rowId;
			if (trees[rowId][colId] >= val) break;
		}
		return treeCounter;
	}

	uint32_t Scenic(const Trees& trees, size_t rowId, size_t colId) {
		return 
			ScenicUp(trees, rowId, colId) *
			ScenicDown(trees, rowId, colId) *
			ScenicLeft(trees, rowId, colId) *
			ScenicRight(trees, rowId, colId);
	}

	void d8() {
		std::ifstream input(aoc::GetInputPath("input08.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		Trees trees{};

		std::string line{};
		while (input >> line) {
			std::vector<uint8_t> data( line.size() );
			std::ranges::transform(line, data.begin(), [](char c) {return c - '0'; });

			trees.push_back(std::move(data));
		}

		size_t maxScenic{};
		for (size_t rowId = 0; rowId < trees.size(); ++rowId) {
			const auto& row = trees.at(rowId);
			for (size_t colId = 0; colId < row.size(); ++colId) {
				auto scenic = Scenic(trees, rowId, colId);
				if (scenic > maxScenic) maxScenic = scenic;
			}
		}

		std::cout << "Max scenic score is: " << maxScenic << '\n';
	}
}