//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <tuple>
#include <concepts>
#include <ugpp/basic_vector_tuple_map.hpp>

namespace ugpp
{
	template <
		typename t_key_type,	// Requires a key-type and at least one vlaue-type
		typename t_value1_type,
		typename ... t_other_value_type_list
	>
		requires
			std::same_as<
				std::remove_cvref_t<t_key_type>,
				t_key_type
			>
	using vt_map_basis =	// basis is not base
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

namespace ugpp
{
	template <
		typename t_key_type,	// Requires a key-type and at least one vlaue-type
		typename t_value1_type,
		typename ... t_other_value_type_list
	>
		requires
			std::same_as<
				std::remove_cvref_t<t_key_type>,
				t_key_type
			>
	class vt_map:
		virtual public
			ugpp::vt_map_basis<
				t_key_type,
				t_value1_type,
				t_other_value_type_list ...
			>
	{
	private:
		using base_type = ugpp::vt_map_basis<t_key_type, t_value1_type, t_other_value_type_list ...>;
		using self_type = ugpp::vt_map_basis<t_key_type, t_value1_type, t_other_value_type_list ...>;
	public:
		// basic_tuple_map is the real constructor.
		using base_type::basic_tuple_map;
	};
}	// namespace ugpp

