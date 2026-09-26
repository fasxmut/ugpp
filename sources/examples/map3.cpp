//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ugpp/vt_map.hpp>
#include <ugpp/lt_map.hpp>
#include <iostream>

using std::string_literals::operator""s;

class printer
{
public:
	void print(const auto & map)
	{
		for (const auto & [... elements]: map)
		{
			((std::cout << elements << " "), ...) << std::endl;
		}
	}
};

int main()
{
	{
		// OK
		ugpp::vt_map<std::string, int, bool> map{
			{"Aa", 3, true},
			{"Bb", 4, false},
			{"Dd", 5, true},
			{"Bb", 6, true}
		};
		map.set("Ee", 7, false);
		map.set("Dd", 1, true);
		printer{}.print(map);
		std::cout << "----\n";
	}
	{
		// OK
		ugpp::vt_map map{
			std::tuple{"Aa", 3, true},
			{"Bb", 4, false},
			{"Dd", 5, true},
			{"Bb", 6, true}
		};
		map.set("Ee", 7, false);
		map.set("Dd", 1, true);
		printer{}.print(map);
		std::cout << "----\n";
	}
	{
		// Error: Deducing failed.
		/*
		ugpp::vt_map map{
			{"Aa", 3, true},
			{"Bb", 4, false},
			{"Dd", 5, true},
			{"Bb", 6, true}
		};
		*/
	}
	{
		// Error: Deducing failed.
		/*
		ugpp::vt_map map{
			"Aa", 3, true, 7
		};
		*/
	}
	{
		// Error: matched a constructor inserted with static_assert(false, ...
		/*
		ugpp::vt_map<std::string, int, bool> map{
			"Aa"s, 3, true
		};
		*/
	}
	{
		// Error: matched a constructor inserted with static_assert(false, ...
		/*
		ugpp::vt_map<std::string, int, bool> map{
			"Aa", 3, true, "oh"
		};
		*/
	}
}

