char* src = (char*)( 0x00002000); //0x0
char* dst = (char*)( 0x00004000);

void convolution(char* kernel, int ampl, int n_k_rows, int n_k_cols, int n_rows, int n_cols)
{
	for (int rows = 0; rows < n_rows; rows++) {
		for (int cols = 0; cols < n_cols; cols++) {
			int acc = 0;
			for (int k_rows = 0; k_rows < n_k_rows; k_rows++) {
				for (int k_cols = 0; k_cols < n_k_cols; k_cols++) {
					int src_col = ((cols + (k_cols - (n_k_cols / 2))) < 0) ? 0 : cols + (k_cols - (n_k_cols / 2));
					int src_row = ((rows + (k_rows - (n_k_rows / 2))) < 0) ? 0 : rows + (k_rows - (n_k_rows / 2));
					acc += kernel[k_cols + (k_rows * n_k_cols)] * src[src_col + (src_row * n_cols)];
				}
			}
			dst[cols + (rows * n_cols)] = dst[cols + (rows * n_cols)] + (acc / ampl);
		}
	}
}

void sobel_gx(int width, int height)
{
	char kernel[3 * 3] =
	{ -1, 0, +1,
	-2, 0, +2,
	-1, 0, +1 };

	convolution(&kernel[0], 1, 3, 3, height, width);
}

void sobel_gy(int width, int height)
{
	char kernel[3 * 3] =
	{ -1, -2, -1,
	0, 0, 0,
	+1, +2, +1 };

	convolution(&kernel[0], 1, 3, 3, height, width);
}

int main ()
{
	int width = 96;
	int height = 96;
	int i;

	// Run Filter
	sobel_gy(width, height);

	// Run Filter
	sobel_gx(width, height);

	// Config display
	__asm__ volatile("syscall");

	return 0;
}
