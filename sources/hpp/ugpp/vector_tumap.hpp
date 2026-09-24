//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <tuple>
#include <ugpp/basic_vector_tuple_map.hpp>

namespace ugpp
{
	template <
		typename t_key_type,	// Requires a key-type and at least one vlaue-type
		typename t_value1_type,
		typename ... t_other_value_type_list
	>
	using vector_tumap =
		ugpp::basic_vector_tuple_map<
			std::allocator<
				std::tuple<
					t_key_type,
					t_value1_type,
					t_other_value_type_list ...
				>
			>,
			t_key_type,
			t_value1_type,
			t_other_value_type_list ...
		>
	;
}	// namespace ugpp

