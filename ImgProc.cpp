//to compile: g++ Try.cpp -o try `pkg-config --cflags --libs opencv` -lgomp -lpthread -fopenmp



#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<string>
#include<omp.h>
#include<ctime>
 
using namespace std;
using namespace cv;
Mat src, dst;
double start, endd, elapsed;
double startomp, endomp, elapsedomp;
int num;
void insertionSort(int window[])
{
    int temp, i , j;
    for(i = 0; i < 9; i++){
        temp = window[i];
        for(j = i-1; j >= 0 && temp < window[j]; j--){
            window[j+1] = window[j];
        }
        window[j+1] = temp;
    }
}

void LowPass()
{
      float sum;
      // define the kernel
      float Kernel[3][3] = {
                            {1/9.0, 1/9.0, 1/9.0},
                            {1/9.0, 1/9.0, 1/9.0},
                            {1/9.0, 1/9.0, 1/9.0}
                           }; 
         dst = src.clone();
        for(int y = 0; y < src.rows; y++)
            for(int x = 0; x < src.cols; x++)
                dst.at<uchar>(y,x) = 0.0;
        //convolution operation
	start = omp_get_wtime();
	#pragma omp single
        for(int y = 1; y < src.rows - 1; y++){
            for(int x = 1; x < src.cols - 1; x++){
                sum = 0.0;
                for(int k = -1; k <= 1;k++){
                    for(int j = -1; j <=1; j++){
                        sum = sum + Kernel[j+1][k+1]*src.at<uchar>(y - j, x - k);
                    }
                }
                dst.at<uchar>(y,x) = sum;
            }
        }
	endd = omp_get_wtime();
}

void LowPassOmp()
{
      float sum;
      int x, y, k, j;
      // define the kernel
      float Kernel[3][3] = {
                            {1/9.0, 1/9.0, 1/9.0},
                            {1/9.0, 1/9.0, 1/9.0},
                            {1/9.0, 1/9.0, 1/9.0}
                           }; 
         dst = src.clone();
        	for( y = 0; y < src.rows; y++)
        	    for( x = 0; x < src.cols; x++)
	                dst.at<uchar>(y,x) = 0.0;
	        //convolution operation
		startomp = omp_get_wtime();
		#pragma omp parallel for private(x, y, k, j, sum)
	        for(y = 1; y < src.rows - 1; y++){
		num = omp_get_num_threads();
	            for( x = 1; x < src.cols - 1; x++){
	                sum = 0.0;
	                for( k = -1; k <= 1;k++){
	                    for( j = -1; j <=1; j++){
	                        sum = sum + Kernel[j+1][k+1]*src.at<uchar>(y - j, x - k);
	                    }
	                }
	                dst.at<uchar>(y,x) = sum;
	            }
	        }
	endomp = omp_get_wtime();

}

void MedianFilter()
{
      int window[9];
 
        dst = src.clone();
        for(int y = 0; y < src.rows; y++)
            for(int x = 0; x < src.cols; x++)
                dst.at<uchar>(y,x) = 0.0;
	start = omp_get_wtime();
	#pragma omp single
        for(int y = 1; y < src.rows - 1; y++){
            for(int x = 1; x < src.cols - 1; x++){
 
                // Pick up window element
 
                window[0] = src.at<uchar>(y - 1 ,x - 1);
                window[1] = src.at<uchar>(y, x - 1);
                window[2] = src.at<uchar>(y + 1, x - 1);
                window[3] = src.at<uchar>(y - 1, x);
                window[4] = src.at<uchar>(y, x);
                window[5] = src.at<uchar>(y + 1, x);
                window[6] = src.at<uchar>(y - 1, x + 1);
                window[7] = src.at<uchar>(y, x + 1);
                window[8] = src.at<uchar>(y + 1, x + 1);
 
                // sort the window to find median
                insertionSort(window);
 
                // assign the median to centered element of the matrix
                dst.at<uchar>(y,x) = window[4];
            }
        }
	endd = omp_get_wtime();
}
void MedianFilterOmp()
{
      int window[9];
      int y, x;
 
        dst = src.clone();
	        for( y = 0; y < src.rows; y++)
	            for( x = 0; x < src.cols; x++)
	                dst.at<uchar>(y,x) = 0.0;
		startomp = omp_get_wtime();
		#pragma omp parallel for private(x, y, window)
	        for( y = 1; y < src.rows - 1; y++){
		num = omp_get_num_threads();
	            for( x = 1; x < src.cols - 1; x++){
	 
	                // Pick up window element
	 
	                window[0] = src.at<uchar>(y - 1 ,x - 1);
	                window[1] = src.at<uchar>(y, x - 1);
	                window[2] = src.at<uchar>(y + 1, x - 1);
	                window[3] = src.at<uchar>(y - 1, x);
	                window[4] = src.at<uchar>(y, x);
	                window[5] = src.at<uchar>(y + 1, x);
	                window[6] = src.at<uchar>(y - 1, x + 1);
	                window[7] = src.at<uchar>(y, x + 1);
	                window[8] = src.at<uchar>(y + 1, x + 1);
	 
	                // sort the window to find median
	                insertionSort(window);
	 
	                // assign the median to centered element of the matrix
	                dst.at<uchar>(y,x) = window[4];
	            }
	        }
		endomp = omp_get_wtime();
}
int main()
{
      
      string str;
      int filter;
      cout << "Please enter the name of the image (sample.jpg): ";
      cin >> str;
      int t = omp_get_max_threads();
      omp_set_num_threads(t);
      /// Load an image
      src = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
 
      if( !src.data )
      { cout << "File not found!" << endl;return -1; }
      cout << "Choose which filter to use: [1] LowPass filter, [2] Median filter: ";
	
	do
	{
		cin >> filter;
		if(filter == 1)
		{
			cout << endl;
			cout << "Filter: Lowpass filter" << endl;
			LowPass();
			elapsed = endd - start;
			LowPassOmp();
			elapsedomp = endomp - startomp;
			cout << "Threads:	Time:" << endl;
			cout << "   1		" << elapsed << endl;
			cout << "   " <<num << "		" << elapsedomp << endl;
		}
		else if (filter == 2)
		{
			cout << endl;
			cout << "Filter: Median filter" << endl;
			MedianFilter();
			elapsed = endd - start;
			MedianFilterOmp();
			elapsedomp = endomp - startomp;
			cout << "Threads:	Time:" << endl;
			cout << "   1		" << elapsed << endl;
			cout << "   " <<num << "		" << elapsedomp << endl;
		}
		else
		{
			filter = 0;
			cout << "Invalid input! " << endl;
		}
	}while(filter <1);

	namedWindow("Final");
        imshow("Final", dst);
 
        namedWindow("initial");
        imshow("initial", src);
 
      waitKey();
 
 
    return 0;
}
