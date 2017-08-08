#include <builder/layers.h>
#include <cstdint>

/**********************************
 * Methods for the `layer` struct *
 **********************************/

const square& layer::operator()(uint16_t x, uint16_t y) const
{
	return (*this)(x, y);
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

void layer::del_square(uint16_t x, uint16_t y)
{
	(*this)(x, y).raw = 0;
}


// Private

square& layer::operator()(uint16_t x, uint16_t y)
{
	return grid[width*y + x];
}