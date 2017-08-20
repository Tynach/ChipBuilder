#include <builder/layers.h>
#include <iostream>
using std::cout;

const uint8_t COLOR = 0b00001000;
const uint8_t TRANSISTOR = 0b00010000;

void print_layer(const layer& silicon_layer);
void print_square(const square& s);

int main()
{
	unsigned int width = 2;
	unsigned int height = 3;
	layer silicon_layer(width, height);
	square red, yellow, transistor, bottom;

	red.exists = true;
	red.con_down = true;
	red.raw &= ~COLOR;

	yellow.exists = true;
	yellow.con_right = true;
	yellow.raw |= COLOR;

	transistor = red;
	transistor.raw |= TRANSISTOR;

	bottom = red;
	bottom.con_down = false;

	silicon_layer.add_square(1, 0, red);
	silicon_layer.add_square(1, 1, red);
	silicon_layer.add_square(1, 2, red);

	silicon_layer.add_square(0, 1, yellow);

	silicon_layer.add_square(1, 1, transistor);
	silicon_layer.add_square(1, 2, bottom);

	print_layer(silicon_layer);

	silicon_layer.del_squares(0, 0, width, 1);

	print_layer(silicon_layer);

	return 0;
}


void print_layer(const layer& silicon_layer)
{
	for (int i = 0; i < silicon_layer.height; ++i) {
		for (int j = 0; j < silicon_layer.width; ++j) {
			print_square(silicon_layer(j, i));
		}

		cout << "\n";

		for (int j = 0; j < silicon_layer.width; ++j) {
			if (silicon_layer(j, i).exists && silicon_layer(j, i).con_down) {
				cout << " | ";
			} else {
				cout << "   ";
			}
		}

		cout << "\n";
	}
}

void print_square(const square& s)
{
	if (s.exists) {
		if (s.raw & TRANSISTOR) {
			cout << "T";
		} else {
			cout << " ";
		}

		if (s.raw & COLOR) {
			cout << "Y";
		} else {
			cout << "R";
		}

		if (s.con_right) {
			cout << "-";
		}
	} else {
		cout << "   ";
	}
}