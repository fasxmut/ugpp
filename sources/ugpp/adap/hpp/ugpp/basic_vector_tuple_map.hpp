//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <vector>
#include <ugpp/basic_tuple_map.hpp>

namespace ugpp
{
	template <
		typename t_allocator_type,
		typename ... t_element_type_list
	>
		requires
			// Requires a key-type and at least one value-type
			((sizeof ... (t_element_type_list)) > 1u)
			&&
			ugpp::non_cvref_k<ugpp::first_type<t_element_type_list ...>>
	using basic_vector_tuple_map =
		ugpp::basic_tuple_map<
			std::vector,
			t_allocator_type,
			t_element_type_list ...
		>
	;
}	// namespace ugpp

