Ugpp c++ library
======================================================================

Ugpp is a c++ library to provide some basic useful features.

## Build

b2 -q -j3

## Install

b2 install --prefix=/usr/local

## cleanall

b2 cleanall

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

void .erase()


