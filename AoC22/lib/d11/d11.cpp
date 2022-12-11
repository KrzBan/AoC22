#include "d11.h"

#include "common.h"

namespace aoc {

	enum class Op {
		Add,
		Mult
	};

	enum class Rhs {
		Arg,
		Self
	};

	class Monkey {
		std::vector<uint64_t> m_Items;

		uint64_t m_InspectCount{};
		uint32_t m_Arg{};
		uint32_t m_Div{};
		size_t m_TestTrue{};
		size_t m_TestFalse{};

		Op m_Op{};
		Rhs m_Rhs{};
	public:
		void Insert(uint64_t value) { m_Items.push_back(value); }
		void SetArg(Op op, Rhs rhs, uint32_t newArg) { m_Op = op; m_Rhs = rhs; m_Arg = newArg; }
		void SetTest(uint32_t div, size_t ifTrue, size_t ifFalse) { m_Div = div; m_TestTrue = ifTrue; m_TestFalse = ifFalse; }
		uint64_t GetInspectionCount() const { return m_InspectCount; }
		void PlayRound(std::vector<Monkey>& monkeys, uint32_t mod) {

			for (const auto& item : m_Items) {
				const auto rhs = m_Rhs == Rhs::Arg ? m_Arg : item;
				auto newVal = m_Op == Op::Add ? item + rhs : item * rhs;

				if (newVal < item) throw std::runtime_error("Overflow!");

				// newVal /= 3; // Boredom

				auto id = (newVal % m_Div) == 0 ? m_TestTrue : m_TestFalse;
				newVal = newVal % mod;
				monkeys.at(id).Insert(newVal);

				++m_InspectCount;
			}

			m_Items.clear();
		}
	};

	uint32_t GetFirstNum(const std::string& str) {
		std::string numberStr = str.substr(str.find_first_of("0123456789"));
		uint32_t number{};
		std::from_chars(numberStr.data(), numberStr.data() + numberStr.size(), number);
		return number;
	}

	void d11() {
		std::ifstream input(aoc::GetInputPath("input11.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		uint32_t mod{1};
		std::vector<Monkey> monkeys{};

		std::string line{};
		while (std::getline(input, line)) {
			
			if (line == "") {
				continue;
			}
			else if (line.starts_with("Monkey")){
				Monkey monkey{};
				// Starting items
				std::getline(input, line);

				std::string numbers = line.substr(line.find_first_of("0123456789"));
				auto split = std::views::split(numbers, std::string_view{ ", " });
				for (const auto str : split) {
					uint32_t value{};
					std::string_view sv{ str.begin(), str.end()};
					std::from_chars(sv.data(), sv.data() + sv.size(), value);
					monkey.Insert(value);
				}

				// Operation
				std::getline(input, line);

				auto operStr = line.substr(line.find_first_of("+*"));
				Op op = operStr[0] == '+' ? Op::Add : operStr[0] == '*' ? Op::Mult : throw std::runtime_error("Unknown operation!");

				auto rhsStr = operStr.substr(2);
				Rhs rhs = rhsStr == "old" ? Rhs::Self : Rhs::Arg;

				uint32_t arg{};
				if (rhs == Rhs::Arg) {
					std::from_chars(rhsStr.data(), rhsStr.data() + rhsStr.size(), arg);
				}
				monkey.SetArg(op, rhs, arg);

				// Div
				std::getline(input, line);
				auto div = GetFirstNum(line);

				// If true
				std::getline(input, line);
				auto ifTrue = GetFirstNum(line);

				// If false
				std::getline(input, line);
				auto ifFalse = GetFirstNum(line);

				monkey.SetTest(div, ifTrue, ifFalse);
				mod *= div;

				monkeys.push_back(std::move(monkey));
			}
			else {
				throw std::runtime_error("Unknown line!");
			}
		}

		constexpr size_t rounds = 10000;
		for (size_t i = 0; i < rounds; ++i) {
			for (auto& monkey : monkeys) {
				monkey.PlayRound(monkeys, mod);
			}
		}

		std::ranges::sort(monkeys, [](const Monkey& lhs, const Monkey& rhs) { return lhs.GetInspectionCount() > rhs.GetInspectionCount(); });

		uint64_t mult = monkeys[0].GetInspectionCount() * monkeys[1].GetInspectionCount();
		std::cout << "Most inspection: " << monkeys[0].GetInspectionCount() << '\n';
		std::cout << "Second most inspection: " << monkeys[1].GetInspectionCount() << '\n';
		std::cout << "Monkey business: " << mult << '\n';
	}
}