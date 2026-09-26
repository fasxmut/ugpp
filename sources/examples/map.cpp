//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ugpp/vector_tumap.hpp>
#include <ugpp/list_tumap.hpp>
#include <iostream>

int main()
{
	std::cout << std::boolalpha << "Hello, c++!" << std::endl;
	{
		std::cout << "========== vector tuple map\n";
		using map_type = ugpp::vector_tumap<std::string, int, bool>;
		map_type map;
		map.set("host", 9, true);
		map.set("port", 102, false);
		map.set("version", 334, true);
		map.set("variant", 222, false);
		map.set("port", 99999, true);
		for (const auto & [k, v1, v2]: map)
		{
			std::cout << k << ", " << v1 << ", " << v2 << std::endl;
		}
		{
			auto itr = map.find("version");
			if (itr != map.end())
			{
				std::cout << "found version: " << std::get<1>(*itr) << ", " << std::get<2>(*itr)
					<< std::endl;
			}
			else
			{
				std::cout << "version not found\n";
			}
		}
		std::cout << "List keys:\n\t";
		for (const auto & k: map.keys())
			std::cout << k << " ";
		std::cout << std::endl;
		contract_assert(map.contains("port"));
		map.erase("port");
		contract_assert(! map.contains("port"));
		std::cout << "List keys:\n\t";
		for (const auto & k: map.keys())
			std::cout << k << " ";
		std::cout << std::endl;
		for (const auto & [k, v1, v2]: map)
		{
			std::cout << k << ", " << v1 << ", " << v2 << std::endl;
		}
	}
	{
		std::cout << "========== list tuple map\n";
		using map_type = ugpp::list_tumap<std::string, int, bool>;
		map_type map;
		map.set("host", 9, true);
		map.set("port", 102, false);
		map.set("version", 334, true);
		map.set("variant", 222, false);
		map.set("port", 99999, true);
		for (const auto & [k, v1, v2]: map)
		{
			std::cout << k << ", " << v1 << ", " << v2 << std::endl;
		}
		{
			auto itr = map.find("version");
			if (itr != map.end())
			{
				std::cout << "found version: " << std::get<1>(*itr) << ", " << std::get<2>(*itr)
					<< std::endl;
			}
			else
			{
				std::cout << "version not found\n";
			}
		}
		std::cout << "List keys:\n\t";
		for (const auto & k: map.keys())
			std::cout << k << " ";
		std::cout << std::endl;
		contract_assert(map.contains("port"));
		map.erase("port");
		contract_assert(! map.contains("port"));
		std::cout << "List keys:\n\t";
		for (const auto & k: map.keys())
			std::cout << k << " ";
		std::cout << std::endl;
		for (const auto & [k, v1, v2]: map)
		{
			std::cout << k << ", " << v1 << ", " << v2 << std::endl;
		}
	}
}

