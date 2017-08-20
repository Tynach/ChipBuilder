#include <builder/layers.h>
#include <cstdint>

/**********************************
 * Methods for the `layer` struct *
 **********************************/

square& layer::operator()(uint16_t x, uint16_t y)
{
	return grid[width*y + x];
}

const square& layer::operator()(uint16_t x, uint16_t y) const
{
	return grid[width*y + x];
}

layer::layer(uint16_t w, uint16_t h):
	width(w), height(h), grid(new square[w * h]())
{}

layer::~layer()
{
	delete[] grid;
}

void layer::add_square(uint16_t x, uint16_t y, const square& s)
{
	(*this)(x, y) = s;
}

void layer::connect(uint16_t x, uint16_t y, uint8_t direction)
{
	if (x >= this->width || y >= this->height) {
		return;
	}

	// Up
	if (direction == 0) {
		if (y == 0) {
			return;
		} else {
			(*this)(x, y - 1).con_down = true;
		}
	}

	// Right
	if (direction == 1) {
		if (x == this->width - 1) {
			return;
		} else {
			(*this)(x, y).con_right = true;
		}
	}

	// Down
	if (direction == 2) {
		if (y == this->height - 1) {
			return;
		} else {
			(*this)(x, y).con_down = true;
		}
	}

	// Left
	if (direction == 3) {
		if (x == 0) {
			return;
		} else {
			(*this)(x - 1, y).con_right = true;
		}
	}
}

void layer::del_square(uint16_t x, uint16_t y)
{
	if (x > 0) {
		(*this)(x - 1, y).con_right = false;
	}

	if (y > 0) {
		(*this)(x, y - 1).con_down = false;
	}

	(*this)(x, y).raw = 0;
}

void layer::del_squares(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	if (x + w > this->width) {
		w = this->width - x;
	}

	if (y + h > this->height) {
		h = this->height - y;
	}

	// Disconnect squares above the block to delete
	if (y > 0) {
		for (int i = 0; i < w; ++i) {
			(*this)(x + i, y - 1).con_down = false;
		}
	}

	// Disconnect squares to the left of the block to delete
	if (x > 0) {
		for (int i = 0; i < h; ++i) {
			(*this)(x - 1, y + i).con_right = false;
		}
	}

	// Delete the entire block of squares
	// Not using del_square since surrounding squares already disconnected
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			(*this)(x + j, y + i).raw = 0;
		}
	}
}