#include <cstdlib>
#include <cstdint>
#include <iostream>
using std::cout;

struct array2d_cont {
	const int width;
	const int height;

	int** arr;

	array2d_cont(const uint32_t w, const uint32_t h): width(w), height(h)
	{
		size_t ptrs_size = sizeof(int**) * h;
		size_t data_size = sizeof(int) * w * h;
		uint8_t* bytes = (uint8_t*)malloc(ptrs_size + data_size);

		arr = (int**)bytes;
		arr[0] = (int*)(&bytes[ptrs_size]);

		for (size_t i = 1; i < h; ++i) {
			arr[i] = arr[0] + (width * i);
		}
	}

	~array2d_cont()
	{
		free(arr);
	}
};

int main()
{
	int width = 2;
	int height = 3;
	array2d_cont test(width, height);

	for (int i = 0; i < width * height; ++i) {
		test.arr[0][i] = i;
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			cout << test.arr[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}