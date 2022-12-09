#include "d9.h"

#include "common.h"

namespace aoc {

	enum class Direction {
		Up,
		Down,
		Left, 
		Right
	};

	Direction StrToDir(const std::string& str) {
		if (str == "U") return Direction::Up;
		if (str == "D") return Direction::Down;
		if (str == "L") return Direction::Left;
		if (str == "R") return Direction::Right;

		throw std::runtime_error("StrToDir(): Invalid string!");
	}

	struct Point {
		int32_t x{};
		int32_t y{};

		void Move(Direction dir) {
			switch (dir) {
			case Direction::Up: ++y; break;
			case Direction::Down: --y; break;
			case Direction::Left: --x; break;
			case Direction::Right: ++x; break;
			}
		}

		void Follow(const Point& head) {
			auto xDiff = head.x - x;
			auto yDiff = head.y - y;

			// If touching
			if (std::abs(xDiff) <= 1 and std::abs(yDiff) <= 1) return;

			if (xDiff > 0) Move(Direction::Right);
			else if(xDiff< 0) Move(Direction::Left);

			if (yDiff > 0) Move(Direction::Up);
			else if (yDiff < 0) Move(Direction::Down);
		}

		bool operator==(const Point& other) const
		{
			if (x == other.x && y == other.y) return true;
			else return false;
		}

		struct Hash
		{
			size_t operator()(const Point& point) const
			{
				size_t xHash = std::hash<int>()(point.x);
				size_t yHash = std::hash<int>()(point.y) << 1;
				return xHash ^ yHash;
			}
		};
	};

	void d9() {
		std::ifstream input(aoc::GetInputPath("input09.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		constexpr uint32_t knotCount = 10;
		std::array<Point, knotCount> knots{};
		std::unordered_set<Point, Point::Hash> history{ Point{} };

		std::string dirStr{};
		while (input >> dirStr) {
			auto dir = StrToDir(dirStr);

			uint32_t len{};
			input >> len;

			for (size_t i = 0; i < len; ++i) {
				knots.front().Move(dir);
				
				for (size_t j = 1; j < knots.size(); ++j) {
					knots[j].Follow(knots[j - 1]);
				}

				history.insert(knots.back());
			}
		}

		std::cout << "Number if unique tail positions is: " << history.size() << '\n';
	}
}