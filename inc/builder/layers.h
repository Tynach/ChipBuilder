#pragma once

#include <vector>
#include <cstdint>
using std::vector;

namespace cbuild {
	// Layer structures
	struct square {
		union
		{
			struct
			{
				bool exists: 1;
				bool con_right: 1;
				bool con_down: 1;
				bool color: 1;
				bool transistor: 1;
			} silicon;

			struct
			{
				char: 5;
				bool exists: 1;
				bool con_right: 1;
				bool con_down: 1;
			} metal;

			uint8_t byte;
		};

		square(): byte(0)
		{}
	};

	// Grid
	struct area
	{
		const uint32_t width;
		const uint32_t height;

		vector<vector<square> > grid;

		area(uint32_t w, uint32_t h) :
			width(w),
			height(h),
			grid(h, vector<square>(w, square()))
		{}

		area() :
			area(36, 27)
		{}
	};
}