//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <tuple>
#include <memory>
#include <ugpp/basic_list_tuple_map.hpp>

namespace ugpp
{
	template <
		typename ... t_element_type_list
	>
		requires
			// Requires a key-type and at least one value-type
			((sizeof ... (t_element_type_list)) > 1u)
			&&
			ugpp::non_cvref_k<ugpp::first_type<t_element_type_list ...>>
	using lt_map_basis =	// basis is not base
		ugpp::basic_list_tuple_map<
			std::allocator<
				std::tuple<
					t_element_type_list ...
				>
			>,
			t_element_type_list ...
		>
	;
}	// namespace ugpp

namespace ugpp
{
	template <
		typename ... t_element_type_list
	>
		requires
			// Requires a key-type and at least one value-type
			((sizeof ... (t_element_type_list)) > 1u)
			&&
			ugpp::non_cvref_k<ugpp::first_type<t_element_type_list ...>>
	class lt_map:
		virtual public
			ugpp::lt_map_basis<
				t_element_type_list ...
			>
	{
	private:
		using base_type = ugpp::lt_map_basis<t_element_type_list ...>;
		using self_type = ugpp::lt_map_basis<t_element_type_list ...>;
	public:
		// basic_tuple_map is the real constructor.
		using base_type::basic_tuple_map;
	};
}	// namespace ugpp

