#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <algorithm>

using std::function;
using std::vector;
using std::swap;
using std::cerr;
using line_segment = uint64_t;
using integer = int64_t;
using TEST_CASE = std::array<int, 3>;

line_segment gcm0(line_segment a, line_segment b)
{
	while (a != b) 
	{
		if (b < a)
			a = a - b;
		else
			b = b - a;
	}
	return a;
}

line_segment gcm00(line_segment a, line_segment b)
{
	while (a != b)
	{
		while (b < a)
			a = a - b;
		while (a < b)
			b = b - a; 
	}
	return a;
}

line_segment gcm1(line_segment a, line_segment b)
{
	while (a != b)
	{
		while (b < a)
			a = a - b;
		std::swap(a, b);
	}
	return a;
}

line_segment segment_remainder(line_segment a, line_segment b)
{
	while (b < a) a = a - b;
	return a;
}

line_segment gcm2(line_segment a, line_segment b)
{
	while (a != b)
	{
		a = segment_remainder(a, b);
		swap(a, b);
	}
	return a;
}

line_segment fast_segment_remainder(line_segment a, line_segment b)
{
	if (a <= b) return a;
	if (a - b <= b) return a - b;
	a = fast_segment_remainder(a, b + b);
	if (a <= b) return a;
	return a - b;
}

line_segment fast_segment_gcm(line_segment a, line_segment b)
{
	while (a != b)
	{
		a = fast_segment_remainder(a, b);
		swap(a, b);
	}
	return a;
}

line_segment half(line_segment a)
{
	return a / 2;
}

line_segment largest_doubling(line_segment a, line_segment b)
{
	while (b < half(a))
		b = b + b;
}

line_segment remainder(line_segment a, line_segment b)
{
	if (a < b) return a;
	while (a - b > b)
		b = b + b;
	line_segment c = largest_doubling(a, b);
	a = a - c;
	while (c != b)
	{
		c = half(c);
		if (c <= a) a = a - c;
	}
	return a;
}

line_segment fast_segment_remainder1(line_segment a, line_segment b)
{
	// precondition: b != 0
	if (a < b) return a;
	if (a - b < b) return a - b;
	a = fast_segment_remainder1(a, b + b);
	if (a < b) return a;
	return a - b;
}

integer quotient(line_segment a, line_segment b)
{
	// Precondition: b > 0
	if (a < b) return integer(0);
	line_segment c = largest_doubling(a, b);
	integer n(1);
	a = a - c;
	while (c != b) {
		c = half(c); n = n + n;
		if (c <= a) { a = a - c; n = n + 1;}
	}
	return n;

}

std::pair<integer, line_segment> quotient_remainder(line_segment a, line_segment b)
{
	if (a < b) return {integer(0), a};
	line_segment c = largest_doubling(a, b);
	integer n(1);
	a = a - c;
	while (c != b) {
		c = half(c); n = n + n;
		if (c <= a) { a = a - c; n = n + 1;}
	}
	return {a, n};
}

template<typename A, typename B>
int verify(A aval, B bval, const char *a, const char *b,
		   const char *file, int line)
{
	if (!(aval == bval))
		cerr << file << ":" << line << ": "
				  << a << " == " << b << "  --  "
				  << aval << " == " << bval << "\n";
	return !(aval == bval);
}

#define TEST_EQUAL(a, b) verify((a), (b), #a, #b, __FILE__, __LINE__)

int main()
{
	vector<TEST_CASE> test_cases = {
		{42, 56, 14},
		{461952, 116298, 18},
		{7966496, 314080416, 32},
		{24826148, 45296490, 526},
	};

	for (auto algorithm : {gcm0, gcm00, gcm1, gcm2, fast_segment_gcm})
	{
		for (const auto test_case : test_cases)
		{
			TEST_EQUAL(algorithm(test_case[0], test_case[1]), test_case[2]);
		}
	}
	

	return 0;
}