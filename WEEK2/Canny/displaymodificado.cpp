//#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int* src; // (IMAGE_SRC_OFFSET);
int* dst; // (IMAGE_DST_OFFSET);
int test = 4; // = 1; for normal operation // Remember tu use char * on src & dst

void convolution(char* kernel, int ampl, int n_k_rows, int n_k_cols, int n_rows, int n_cols)
{
	int cuenta =0;	
	for (int rows = 0; rows < n_rows; rows++) {
		for (int cols = 0; cols < n_cols; cols++) {
			int acc = 0;
			for (int k_rows = 0; k_rows < n_k_rows; k_rows++) {
				for (int k_cols = 0; k_cols < n_k_cols; k_cols++) {
					int src_col = ((cols + (k_cols - (n_k_cols / (2*test))) < 0) ? 0 : cols + (k_cols - (n_k_cols / (2*test));
					int src_row = ((rows + (k_rows - (n_k_rows / (2*test))) < 0) ? 0 : rows + (k_rows - (n_k_rows / (2*test));
					acc += kernel[k_cols + (k_rows * n_k_cols)] * src[(src_col + (src_row * n_cols))/(1*test)];
				}
			}
			dst[(cols + (rows * n_cols))/(1*test)] = dst[(cols + (rows * n_cols))/(1*test)] + (acc / ampl);
			cuenta++;
		}
	}
	cout << "Cuenta de convolution: " << cuenta << endl;
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

void canny_simp(int width, int height)
{
	//int width = s.width;
	//int height = s.height;

	// Run Filter
	sobel_gy(width, height);

	// Run Filter
	sobel_gx(width, height);

}

int my_strlen(char *string)
{
	int length = 0;
	for (length = 0; *string != '\0'; string++)
		length++;
	
	return(length);
}


int main( int argc, char** argv )
{
  
	const char * f_SRC = "si.bmp";
	const char * f_DST = "si_8b_canny.bmp";

	IplImage *img = cvLoadImage(f_SRC, CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *imgDst = cvLoadImage(f_SRC, CV_LOAD_IMAGE_GRAYSCALE);

	cout << "width " << img->width << endl;
	cout << "height " << img->height << endl << endl;

    src = (int *)(img->imageData);
    dst = (int *)(imgDst->imageData);
    
	char *sweepdata = imgDst->imageData;
	int count=0;
	cout<< "Before Canny" << endl;
	cout << "&img->Data: " << &img->imageData << endl;
	cout << "&imgDst->Data: " << &imgDst->imageData << endl;
	cout << "&src->Data: " << &src << endl;
	cout << "byte Data Size: " << img->imageSize << endl;
	cout << "&dst->Data: " << &dst << endl << endl;

    if(! img->imageData )                          
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
	canny_simp(img->width, img->height);

	cout << "Cuenta de sweep: " << count << endl;
	
	if(!cvSaveImage(f_DST,imgDst)) cout<<"Could not save: "<< f_DST << endl;

	cout<< "Canny correctly applied" << endl;
	cout << "&img->Data: " << &img->imageData << endl;
	cout << "&imgDst->Data: " << &imgDst->imageData << endl;
	cout << "&src->Data: " << &src << endl;
	cout << "byte Data Size: " << imgDst->imageSize << endl;
	cout << "&dst->Data: " << &dst << endl;
    return 0;
}
