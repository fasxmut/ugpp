//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <vector>
#include <concepts>
#include <ugpp/basic_tuple_map.hpp>

namespace ugpp
{
	template <
		typename t_allocator_type,
		typename t_key_type,	// Requires a key-type and at least one vlaue-type
		typename t_value1_type,
		typename ... t_other_value_type_list
	>
		requires
			std::same_as<
				std::remove_cvref_t<t_key_type>,
				t_key_type
			>
	using basic_vector_tuple_map =
		ugpp::basic_tuple_map<
			std::vector,
			t_allocator_type,
			t_key_type,
			t_value1_type,
			t_other_value_type_list ...
		>
	;
}	// namespace ugpp

