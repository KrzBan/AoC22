#include "d12.h"

#include "common.h"

namespace aoc {

	struct Point {
		int32_t x{};
		int32_t y{};

		bool operator==(const Point& other) const
		{
			if (x == other.x && y == other.y) return true;
			else return false;
		}

		struct Hash
		{
			size_t operator()(const Point& point) const
			{
				size_t xHash = std::hash<int32_t>()(point.x);
				size_t yHash = std::hash<int32_t>()(point.y);
				return xHash ^ yHash;
			}
		};
	};

	void d12() {
		std::ifstream input(aoc::GetInputPath("input12.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		Point start{}, end{};
		std::vector<std::vector<uint8_t>> map;

		std::string line{};
		while (std::getline(input, line)) {
			std::vector<uint8_t> row(line.size());

			std::transform(line.begin(), line.end(), row.begin(), [id=0,&start,&end,&map](char c) mutable { 
				if (c == 'S') {
					start = { id, static_cast<int32_t>(map.size()) };
					c = 'a' - 'a';
				}
				else if (c == 'E') {
					end = { id, static_cast<int32_t>(map.size()) };
					c = 'z' - 'a';
				}
				else {
					c = c - 'a';
				}
				++id;
				return c;
				});
			map.push_back(std::move(row));
		}

		// A* algorithm
		std::swap(start, end);
		auto pointVal = [&](const Point& p) -> int32_t { return map.at(p.y).at(p.x); };

		auto steepness = [&](Point lhs, Point rhs) -> int32_t {
			return pointVal(lhs) - pointVal(rhs);
		};

		auto h = [&](Point p, Point l) -> int32_t {
			return	/*(p.x - l.x) * (p.x - l.x) +
					(p.y - l.y)* (p.y - l.y) +
					(pointVal(p) - pointVal(l)) * (pointVal(p) - pointVal(l));*/
				pointVal(l); };

		std::unordered_set<Point, Point::Hash> openSet{ start };
		std::unordered_map<Point, Point, Point::Hash> cameFrom{};

		std::unordered_map<Point, int32_t, Point::Hash> gScore{ {start, 0} };
		std::unordered_map<Point, int32_t, Point::Hash> fScore{ {start, h(start, end)}};

		auto lowestFFromOpenSet = [&]() -> Point {
			Point minP{};
			int32_t minScore = std::numeric_limits<int32_t>::max();
			for (const auto& point : openSet) {
				if (fScore.contains(point)) {
					auto score = fScore.at(point);
					if (score < minScore) {
						minScore = score;
						minP = point;
					}
				}
			}
			return minP;
		};

		auto getValOrDefault = [](const std::unordered_map<Point, int32_t, Point::Hash>& map, Point p) -> int32_t {
			if (map.contains(p)) {
				return map.at(p);
			}
			return std::numeric_limits<int32_t>::max();
		};

		auto getNeighbours = [&](Point p) {
			std::vector<Point> n;
			if (p.x > 0) n.push_back({ p.x - 1, p.y });
			if (p.y > 0) n.push_back({ p.x, p.y - 1 });
			if (p.x < map[0].size() - 2) n.push_back({p.x + 1, p.y});
			if (p.y < map.size() - 2) n.push_back({ p.x, p.y + 1 });
			return n;
		};

		while (openSet.size() > 0) {
			auto current = lowestFFromOpenSet();

			if (pointVal(current) == 0) {
				// Found!
				std::cout << "Found path!\n";
				std::cout << "CameFrom length: " << cameFrom.size() << '\n';
				auto c = current;
				std::unordered_set<Point, Point::Hash> path{ c };
				while (cameFrom.contains(c)) {
					c = cameFrom.at(c);
					path.insert(c);
				}
				std::cout << "Path length: " << path.size() << '\n';
				std::cout << "Steps: " << path.size() - 1 << '\n';

				for (int i = 0; i < map.size(); ++i) {
					const auto& row = map[i];
					for (int j = 0; j < row.size(); ++j) {
						Point p{ j,i };
						if (path.contains(p))
							std::cout << "#";
						else
							std::cout << static_cast<char>(row[j] + 'a');
					}
					std::cout << '\n';
				}
			}

			openSet.erase(current);
			auto neighbours = getNeighbours(current);
			for (const auto& neighbour : neighbours) {
				auto steepLevel = steepness(current, neighbour);
				if ( steepLevel > 1) continue;

				auto tentative_gScore = gScore.at(current) + h(current, neighbour);
				if (tentative_gScore < getValOrDefault(gScore, neighbour)) {
					cameFrom[neighbour] = current;
					gScore[neighbour] = tentative_gScore;
					fScore[neighbour] = tentative_gScore + h(neighbour, end);

					openSet.insert(neighbour);
				}
			}
		}
	}
}