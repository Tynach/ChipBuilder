#include <builder/layers.h>
#include <iostream>
using cbuild::area;
using cbuild::square;
using std::cout;

int main()
{
	area build_area(2, 3);

	square red;
	red.silicon.exists = true;
	red.silicon.con_down = true;
	red.silicon.color = 0;

	build_area.grid[0][1] = red;
	build_area.grid[1][1] = red;
	build_area.grid[2][1] = red;

	build_area.grid[1][1].silicon.transistor = true;

	build_area.grid[1][0].silicon.exists = true;
	build_area.grid[1][0].silicon.con_right = true;
	build_area.grid[1][0].silicon.color = 1;

	return 0;
}