//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ugpp/lt_map.hpp>
#include <ugpp/vt_map.hpp>
#include <iostream>

namespace hwt
{
	template <
		template <
			typename ...
		>
		typename t_map,
		typename ... t_list
	>
	class world
	{
	private:
		using self_type = hwt::world<t_map, t_list ...>;
		using map_type = t_map<t_list ...>;
		using item_type = self_type::map_type::item_type;
	private:
		self_type::map_type __map;
	public:
		world(
		):
			__map{}
		{
		}
		world(
			const std::initializer_list<self_type::item_type> & list__
		):
			__map{list__}
		{
			this->start();
		}
	private:
		void start()
		{
			this->print();
		}
	private:
		void print() const
		{
			for (const auto & [... el]: __map)
			{
				((std::cout << el << " "), ...) << std::endl;
			}
			std::cout << std::endl;
		}
	};
}

int main()
{
	{
		{
			using map_type = ugpp::vt_map<float, int, bool, std::string>;
			map_type map{
				{2.1, 3, true, "A"},
				{3.1, 4, false, "B"},
				{4.1, 5, false, "C"},

				// This will update 3.1's values, but do not change its position.
				{3.1, 6, true, "D"}
			};
			for (const auto & [k, v1, v2, v3]: map)
			{
				std::cout << k << " => " << v1 << " " << v2 << " " << v3 << std::endl;
			}
			std::cout << std::endl;
		}
		{
			using map_type = ugpp::lt_map<float, int, bool, std::string>;
			map_type map{
				{2.1, 3, true, "A"},
				{3.1, 4, false, "B"},
				{4.1, 5, false, "C"},

				// This will update 3.1's values, but do not change its position.
				{3.1, 6, true, "D"}
			};
			for (const auto & [k, v1, v2, v3]: map)
			{
				std::cout << k << " => " << v1 << " " << v2 << " " << v3 << std::endl;
			}
			std::cout << std::endl;
		}
	}

	{
		hwt::world<ugpp::vt_map, std::string, std::string, std::string, bool> map1{
			{"world 0", "280", "A", true},
			{"world 1", "240", "B", false},
			{"world 2", "230", "C", true},
			{"world 3", "210", "D", false},

			// This will update "world 2"'s values, but do not change its position.
			{"world 2", "270", "E", true}
		};
	}
	{
		hwt::world<ugpp::lt_map, std::string, std::string, std::string, bool> map1{
			{"world 0", "280", "A", true},
			{"world 1", "240", "B", false},
			{"world 2", "230", "C", true},
			{"world 3", "210", "D", false},

			// This will update "world 2"'s values, but do not change its position.
			{"world 2", "270", "E", true}
		};
	}
}

