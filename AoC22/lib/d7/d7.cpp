#include "d7.h"

#include "common.h"

namespace aoc {

	class Directory;
	using Tree = std::unordered_map<std::string, Directory>;

	class Directory {
		Tree m_Nodes{};
		size_t m_Size{};
		Directory* parentDir{ nullptr };

	public:
		Directory() : parentDir{ nullptr } {}
		Directory(Directory* parent) : parentDir{ parent } {}

		void Insert(const std::string& name) {
			m_Nodes.try_emplace(name, this);
		}
		bool Contains(const std::string& name) const {
			return m_Nodes.contains(name);
		}
		void Inflate(size_t size) {
			m_Size += size;
			auto* parent = GetParentDir();
			if (parent != this) {
				parent->Inflate(size);
			}
		}
		size_t GetElfSize() const{
			size_t size = m_Size <= 100000 ? m_Size : 0;

			for (const auto& [key, dir] : m_Nodes) {
				size += dir.GetElfSize();
			}

			return size;
		}
		size_t FindSmallest(size_t toDel) const {
			size_t minSize = m_Size < toDel ? std::numeric_limits<size_t>::max() : m_Size;

			for (const auto& [key, dir] : m_Nodes) {
				auto size = dir.FindSmallest(toDel);
				if (size >= toDel and size < minSize) {
					minSize = size;
				}
			}
			return minSize;
		}
		size_t GetSize() const {
			return m_Size;
		}
		Directory* Move(const std::string& name) {
			return &m_Nodes[name];
		}
		Directory* GetParentDir() {
			return parentDir ? parentDir : this;
		}
	};	

	void d7() {
		std::ifstream input(aoc::GetInputPath("input07.txt"));
		if (input.is_open() == false) {
			throw std::runtime_error("Couldn't open file!");
		}

		Directory root{nullptr};
		Directory* current = &root;

		std::string op{};
		while (input >> op) {
			
			size_t size{};
			auto [ptr, ec] = std::from_chars(op.data(), op.data() + op.size(), size);
			
			if (ec == std::errc{}) {
				std::string filename{};
				input >> filename;

				current->Inflate(size);
			}
			else if (op == "dir") {
				std::string dirname{};
				input >> dirname;

				current->Insert(dirname);
			}
			else if(op == "$") {
				std::string option{};
				input >> option;
				if (option == "ls") {
					// Nothing
				}
				else if (option == "cd") {
					std::string location{};
					input >> location;
					
					if (location == "/") {
						current = &root;
					}
					else if (location == "..") {
						current = current->GetParentDir();
					}
					else if (current->Contains(location)) {
						current = current->Move(location);
					}
					else {
						throw std::runtime_error("Location does not exist!");
					}
				}
				else {
					throw std::runtime_error("Unexpected option found!");
				}
			}
			else {
				throw std::runtime_error("Unexpected op found!");
			}
		}

		auto dirCount = root.GetElfSize();
		std::cout << "Sum of directories <= 100000: " << dirCount << '\n';

		constexpr size_t maxSize = 70000000;
		constexpr size_t reqSize = 30000000;
		const size_t freeSize = maxSize - root.GetSize();
		const size_t toDel = reqSize - freeSize;

		size_t smallestDir = root.FindSmallest(toDel);
		std::cout << "Smallest dir to del is: " << smallestDir << '\n';
	}
}