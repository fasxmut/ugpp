Ugpp
=======================================================

Ugpp is a c++ library to make basic useful features.

## Some public APIs

* ugpp::vt_map

	Defined in vt_map.hpp

* ugpp::lt_map

	Defined in lt_map.hpp

* ugpp::first_type

	Defined in basic_tuple_map.hpp

* ugpp::non_cvref_k

	Defined in basic_tuple_map.hpp

## Constructing of ugpp::vt_map, ugpp::lt_map

```cpp
ugpp::vt_map<std::string, int, bool, float> m1{};	// OK
ugpp::lt_map<std::string, int, bool, float> m2{};	// OK

// OK
ugpp::vt_map<std::string, int, bool, float> m3{
	{"Hello", 3, true, 2.5f},
	{"World", 4, false, 2.5f}
};

m3.set("oh", 5, true, 1.7f);

// OK
ugpp::lt_map m4{
	std::tuple{"Hello", 3, true, 2.5f},
	{"World", 4, false, 2.5f}
};

m4.set("oh", 5, true, 1.7f);
```

```cpp
// Error: deducing failed.
ugpp::vt_map m5{
	{"Hello", 3, true, 2.5f},
	{"World", 4, false, 2.5f}
};

// Error: deducing failed.
ugpp::vt_map m6{
	"World", 4, false, 2.5f
};

// Error: matched a constructor inserted with static_assert(false, ...
ugpp::vt_map<std::string, int, bool, float> m7{
	"World"s, 4, false, 2.5f
};

// Error: matched a constructor inserted with static_assert(false, ...
ugpp::vt_map<std::string, int, bool, float> m8{
	"World", 4, false, 2.5f, "not", "is"
};
```
## Method list of ugpp::vt_map, ugpp::lt_map

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

