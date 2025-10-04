#pragma once

template<typename U, typename V>
struct MyPair
{
	U first;
	V second;

	MyPair() = default;
	MyPair(const U& first, const V& second) : first(first), second(second)
	{}
};