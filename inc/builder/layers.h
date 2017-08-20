#pragma once

#include <cstdint>

struct square {
	union {
		struct {
			bool exists: 1;
			bool con_right: 1;
			bool con_down: 1;
			int8_t: 4;
			bool active: 1;
		};

		uint8_t raw;
	};

	square(): raw(0)
	{}
};

struct layer {
	const uint16_t width;
	const uint16_t height;

	layer(uint16_t w, uint16_t h);

	~layer();

	// Get a constant referance to a specific square on the grid
	const square& operator()(uint16_t x, uint16_t) const;

	// Get a reference to a specific square on the grid
	square& operator()(uint16_t x, uint16_t y);

	// Add a square to the grid
	void add_square(uint16_t x, uint16_t y, const square& s);

	// Connect two contiguous squares; 'direction' follows CSS rules
	void connect(uint16_t x, uint16_t y, uint8_t direction);

	// Make a square on the grid empty
	void del_square(uint16_t x, uint16_t y);

	// Make a block of squares on the grid empty
	void del_squares(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

protected:
	square* grid;
};