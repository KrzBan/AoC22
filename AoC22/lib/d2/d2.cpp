#include "d2.h"

#include "common.h"

namespace aoc {

	enum class Pick {
		Undefined = 0,
		Rock,
		Paper,
		Scissors
	};

	enum class Outcome {
		Lose,
		Draw,
		Win
	};

	std::map<char, Outcome> charToOutcome = {
		{'X', Outcome::Lose},
		{'Y', Outcome::Draw},
		{'Z', Outcome::Win},
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

	std::map<Pick, Pick> pickLose = {
		{Pick::Scissors, Pick::Rock},
		{Pick::Rock, Pick::Paper},
		{Pick::Paper, Pick::Scissors}
	};

	uint32_t GetBeatScore(Pick lhs, Pick rhs) {
		if (lhs == rhs) return 3;
		if (pickBeat.at(lhs) == rhs) return 6;
		return 0;
	}

	Pick GetDesiredPick(Pick enemy, Outcome oc) {
		switch (oc) {
		case Outcome::Draw: return enemy; break;
		case Outcome::Lose: return pickBeat.at(enemy); break;
		case Outcome::Win: return pickLose.at(enemy); break;
		}
		throw std::runtime_error("GetDesiredPick(): Unknown Outcome!");
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
			char outcomeChar{ 0 }, opponentChar{ 0 };
			ss >> opponentChar >> outcomeChar;

			Outcome desiredOutcome = charToOutcome.at(outcomeChar);
			Pick opponentPick = charToPick.at(opponentChar);

			Pick myPick = GetDesiredPick(opponentPick, desiredOutcome);
			myScore += pickToScore.at(myPick);
			myScore += GetBeatScore(myPick, opponentPick);
		}

		std::cout << "My score is: " << myScore << '\n';
	}

}