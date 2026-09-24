Ugpp c++ library
======================================================================

Ugpp is a c++ library to provide some basic useful features.

## Build

b2 -q -j3

## Install

b2 install --prefix=/usr/local

## cleanall

b2 cleanall

## Example

```cpp
#include <ugpp/vector_tumap.hpp>
#include <iostream>

int main()
{
	ugpp::vector_tumap<std::string, std::string, std::string, std::string> map;
	map.set("url1", "127.0.0.1", "80", "http");
	map.set("url2", "192.168.1.2", "443", "https");
	map.set("url3", "192.168.1.2", "447", "https");
	map.set("url4", "192.168.1.3", "443", "https");
	contract_assert(map.contains("url3"));
	contract_assert(map.size() == 4u);
	map.erase("url3");
	contract_assert(! map.contains("url3"));
	contract_assert(map.size() == 3u);
	for (const auto & [key, host, port, schema]: map)
	{
		std::cout << key << " => " << host << " " << port << " " << schema
			<< std::endl;
	}
}
```

## Implemented:

### ugpp::vector_tumap, ugpp::list_tumap

A map that uses std::tuple as its item type,
and uses std::vector or std::list as its range type.

*Method List:*

bool .contains(key)

void .set(key, vlist ...)

const-iterator .find(key)

item-type .extract(key)

const-iterator .begin()

const-iterator .end()

size-type .size()

bool .empty()

range-type .keys()

void .clear()

void .erase(key)

