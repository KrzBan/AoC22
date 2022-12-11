#include "d10.h"

#include "common.h"

namespace aoc {

	class NoOp {
	public:
		uint32_t counter{ 1 };
	};

	class AddOp {
	private:
		int64_t value{};
	public:
		uint32_t counter{ 2 };
	public:
		AddOp(int64_t value) : value{ value } {}
		int64_t GetValue() const { return value; }
	};

	template<typename Op>
	bool Finished(Op& op) {
		return op.counter == 0;
	}

	using CpuOp = std::variant<NoOp, AddOp>;

	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

	class Cpu {
	private:
		int64_t reg{ 1 };
		std::vector<CpuOp> ops{};

	public:
		bool Empty() const { return ops.empty(); }
		int64_t GetRegistry() { return reg; }
		void Insert(const CpuOp& op) { ops.push_back(op); }

		void Resolve() {
			for (auto& op : ops) {
				bool reachedZero = false;
				std::visit([&](auto& op) { --op.counter; if (op.counter == 0) reachedZero = true; }, op);

				if (reachedZero == false) continue;

				std::visit(overloaded{
					[this](const NoOp& op) {},
					[this](const AddOp& op) { reg += op.GetValue(); }
					}, op);
			}

			std::erase_if(ops, [](const CpuOp& op) {
				bool reachedZero = false;
			std::visit([&](auto& op) { if (op.counter == 0) reachedZero = true; }, op);
			return reachedZero;
				});
		}
	};

	void d10() {
		std::ifstream input(aoc::GetInputPath("input10.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		Cpu cpu;

		int32_t cycle{};
		std::vector<char> line{};

		std::string cmdStr{};
		while (input >> cmdStr) {
			if (cmdStr == "noop") {
				cpu.Insert(NoOp());
			}
			else if (cmdStr == "addx") {
				int64_t val;
				input >> val;

				cpu.Insert(AddOp(val));
			}

			// Get Val
			while (cpu.Empty() == false) {

				auto pos = cpu.GetRegistry();
				char c = std::abs(pos - (cycle % 40)) <= 1 ? '#' : '.';
				line.push_back(c);

				if ((cycle + 1) % 40 == 0) {
					for (const auto& c : line) {
						std::cout << c;
					}
					std::cout << '\n';
					line.clear();
				}

				cpu.Resolve();
				++cycle;
			}
		}
	}
}