//
// Copyright (c) 2026 cppfx.tiv.cc
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <tuple>
#include <concepts>
#include <memory>
#include <initializer_list>

namespace ugpp
{
	template <typename ...>
	class first_type_impl
	{
	public:
		using type = void;
	};

	template <typename t_first_type, typename ... t_list>
	class first_type_impl<t_first_type, t_list ...>
	{
	public:
		using type = t_first_type;
	};

	template <typename t_first_type, typename ... t_list>
	class first_type_impl<std::tuple<t_first_type, t_list ...>>
	{
	public:
		using type = t_first_type;
	};

	template <typename ... t_list>
	using first_type = ugpp::first_type_impl<t_list ...>::type;

	template <typename t_type>
	concept non_cvref_k =
		std::same_as<
			std::remove_cvref_t<t_type>,
			t_type
		>
	;
}	// namespace ugpp

namespace ugpp
{
	template <
		template <typename, typename> typename t_range_type,
		typename t_allocator_type,
		typename ... t_element_type_list
	>
		requires
				// Requires a key-type and at least one value-type
			((sizeof ... (t_element_type_list)) > 1u)
			&&
				// The key type must be a non-const and non-reference type.
			ugpp::non_cvref_k<ugpp::first_type<t_element_type_list ...>>
	class basic_tuple_map
	{
	private:
		using self_type = ugpp::basic_tuple_map<
			t_range_type,
			t_allocator_type,
			t_element_type_list ...
		>;

	public:
		using key_type = ugpp::first_type<t_element_type_list ...>;
		using item_type = std::tuple<t_element_type_list ...>;
		using range_type = t_range_type<self_type::item_type, t_allocator_type>;
		using const_iterator = self_type::range_type::const_iterator;
		using size_type = self_type::range_type::size_type;

	private:
		self_type::range_type __data;

	public:
		constexpr virtual ~basic_tuple_map() noexcept
		{
			this->clear();
		}

/////////////////////////////////////////////////////////////////////////
// constructors

	public:
		constexpr basic_tuple_map() noexcept:
			__data{}
		{
		}

	public:
		constexpr basic_tuple_map(
			const std::initializer_list<self_type::item_type> & init_list__
		) noexcept:
			__data{}
		{
			for (const auto & [... list]: init_list__)
			{
				this->set(list ...);
			}
		}

	public:
		constexpr basic_tuple_map(
			const auto & ... any
		) noexcept
		{
			static_assert(false, "ERROR: ugpp::basic_tuple_map: constructors match failed!");
		}

/////////////////////////////////////////////////////////////////////////

	public:
		constexpr void clear() noexcept
		{
			__data.clear();
			__data = {};
			contract_assert(__data.empty());
			contract_assert(__data.size() == 0);
		}

	public:
		constexpr self_type::size_type size() const noexcept
		{
			return __data.size();
		}

		constexpr bool empty() const noexcept
		{
			return __data.empty();
		}

		constexpr bool contains(const self_type::key_type & key) const noexcept
		{
			for (const auto & [k, ... _]: __data)
			{
				if (k == key)
					return true;
			}
			// Other cases:
			return false;
		}

	public:
		// For new key: only allow to push at the end.
		// For old key: update values.
		constexpr void set(
			const t_element_type_list & ... element_list
		) noexcept
		{
			const auto tuple = self_type::item_type{element_list ...};
			for (auto & vv: __data)
			{
				if (std::get<0>(vv) == std::get<0>(tuple))
				{
					vv = tuple;
					return;
				}
			}
			// Otherwise:
			__data.push_back(tuple);
		}

	public:
		// Only get by key, no get by pos.
		constexpr self_type::const_iterator find(const self_type::key_type & key) const noexcept
		{
			for (self_type::const_iterator itr=__data.begin(); itr!=__data.end(); ++itr)
			{
				if (key == std::get<0>(*itr))
					return itr;
			}
			return __data.end();
		}

	public:
		// Extract a node, its type is a tuple.
		//	If not found: return an empty node.
		constexpr self_type::item_type extract(const self_type::key_type & key) const noexcept
		{
			auto itr = this->find(key);
			if (itr != this->end())
				return *itr;
			return {};
		}

	public:
		constexpr self_type::const_iterator begin() const noexcept
		{
			return __data.begin();
		}

	public:
		constexpr self_type::const_iterator end() const noexcept
		{
			return __data.end();
		}

	public:
		// Collect all keys in one range.
		constexpr auto keys() const noexcept
		{
			using result_type = t_range_type<self_type::key_type, std::allocator<self_type::key_type>>;
			result_type tmp{};
			for (const auto & [k, ... _]: __data)
			{
				tmp.push_back(k);
			}
			return tmp;
		}
	public:
		constexpr void erase(const self_type::key_type & key) noexcept
		{
			auto itr = this->find(key);
			if (itr == this->end())
				return;
			__data.erase(itr);
		}
	};	// class basic_tuple_map
}	// namespace ugpp

