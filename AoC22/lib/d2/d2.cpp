#include "d2.h"

#include "common.h"

namespace aoc {

	enum class Pick {
		Undefined = 0,
		Rock,
		Paper,
		Scissors
	};


	std::map<char, Pick> charToPick = {
		{'A', Pick::Rock}, {'X', Pick::Rock},
		{'B', Pick::Paper}, {'Y', Pick::Paper},
		{'C', Pick::Scissors}, {'Z', Pick::Scissors},
	};

	std::map<Pick, uint32_t> pickToScore = {
		{Pick::Rock, 1},
		{Pick::Paper, 2}, 
		{Pick::Scissors, 3}
	};

	std::map<Pick, Pick> pickBeat = {
		{Pick::Rock, Pick::Scissors},
		{Pick::Paper, Pick::Rock},
		{Pick::Scissors, Pick::Paper}
	};

	uint32_t GetBeatScore(Pick lhs, Pick rhs) {
		if (lhs == rhs) return 3;
		if (pickBeat.at(lhs) == rhs) return 6;
		return 0;
	}

	void d2() {
		std::ifstream input(aoc::GetInputPath("input02.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		uint32_t myScore = 0;

		std::string line;
		while (std::getline(input, line)) {

			std::stringstream ss{ line };

			char me, opponent;
			input >> opponent >> me;

			Pick myPick = charToPick.at(me);
			Pick opponentPick = charToPick.at(opponent);

			myScore += pickToScore.at(myPick);
			myScore += GetBeatScore(myPick, opponentPick);
		}

		std::cout << "My score is: " << myScore << '\n';
	}

}