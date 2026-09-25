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

//	Method List:
//		bool .contains(key)
//		void .set(key, vlist ...)
//		const-iterator .find(key)
//		item-type .extract(key)
//		const-iterator .begin()
//		const-iterator .end()
//		size-type .size()
//		bool .empty()
//		range-type .keys()
//		void .clear()
//		void .erase()

namespace ugpp
{
	template <
		template <typename, typename> typename t_range_type,
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
	class basic_tuple_map
	{
	private:
		using self_type = ugpp::basic_tuple_map<
			t_range_type,
			t_allocator_type,
			t_key_type,
			t_value1_type,
			t_other_value_type_list ...
		>;
	public:
		using key_type = t_key_type;
		using item_type = std::tuple<t_key_type, t_value1_type, t_other_value_type_list ...>;
		using range_type = t_range_type<item_type, t_allocator_type>;
		using const_iterator_type = range_type::const_iterator;
		using size_type = range_type::size_type;
	private:
		self_type::range_type __data;
	public:
		constexpr virtual ~basic_tuple_map() noexcept
		{
			this->clear();
		}
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
		constexpr bool contains(const self_type::key_type & key) const noexcept
		{
			for (const auto & [k, ... values]: __data)
			{
				if (key == k)
					return true;
			}
			// other cases:
			return false;
		}
	public:
		// For new key: only allow to push at the end.
		// For old key: update values.
		constexpr void set(
			const key_type & key,
			const t_value1_type & value1,
			const t_other_value_type_list & ... value_list
		) noexcept
		{
			for (auto & vv: __data)
			{
				if (key == std::get<0>(vv))
				{
					vv = self_type::item_type{key, value1, value_list ...};
					return;
				}
			}

			// otherwise:

			__data.emplace_back(key, value1, value_list ...);
		}
	public:
		// Only get by key, no get by pos.
		constexpr const_iterator_type find(const self_type::key_type & key) const noexcept
		{
			for (const_iterator_type itr=__data.begin(); itr!=__data.end(); ++itr)
			{
				if (key == std::get<0>(*itr))
					return itr;
			}
			return __data.end();
		}
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
		constexpr const_iterator_type begin() const noexcept
		{
			return __data.begin();
		}
	public:
		constexpr const_iterator_type end() const noexcept
		{
			return __data.end();
		}
	public:
		constexpr self_type::size_type size() const noexcept
		{
			return __data.size();
		}
	public:
		constexpr bool empty() const noexcept
		{
			return __data.empty();
		}
	public:
		// Collect all keys in one range.
		constexpr auto keys() const noexcept
		{
			using result_type = t_range_type<self_type::key_type, std::allocator<self_type::key_type>>;
			result_type tmp{};
			for (const auto & [k, ... vlist]: __data)
			{
				tmp.push_back(k);
			}
			return tmp;
		}
	public:
		constexpr void clear() noexcept
		{
			__data.clear();
			__data = {};
			contract_assert(__data.empty());
			contract_assert(__data.size() == 0);
		}
	public:
		constexpr void erase(const self_type::key_type & key) noexcept
		{
			auto itr = this->find(key);
			if (itr == this->end())
				return;
			__data.erase(itr);
		}
	};	// class tuple_map
}	// namespace ugpp

