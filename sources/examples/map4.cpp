//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ugpp/vt_map.hpp>
#include <ugpp/lt_map.hpp>
#include <iostream>

int main()
{
	{
		ugpp::vt_map map{
			std::tuple{"Aa", true, 2.5, 3},
			{"Bb", false, 3.5, 4},
			{"Cc", true, 4.5, 5},
			{"Dd", false, 5.5, 6},
		};
		std::cout << "=>\n";
		for (const auto & [k, v1, v2, v3]: map)
			std::cout << k << " " << v1 << " " << v2 << " " << v3 << std::endl;
		for (auto & [k, v1, v2, v3]: map)
		{
			v1 = true;
			v2 = 9.8;
			v3 = 12;
		}
		std::cout << "=>\n";
		for (const auto & [k, v1, v2, v3]: map)
			std::cout << k << " " << v1 << " " << v2 << " " << v3 << std::endl;
		auto & tx = * map.find("Dd");
		std::get<1>(tx) = false;
		std::get<2>(tx) = -11.3;
		std::get<3>(tx) = -10;
		std::cout << "=>\n";
		for (const auto & [k, v1, v2, v3]: map)
			std::cout << k << " " << v1 << " " << v2 << " " << v3 << std::endl;
	}
}

