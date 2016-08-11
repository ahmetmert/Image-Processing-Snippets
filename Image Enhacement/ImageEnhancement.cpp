#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;

    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);	// Read the file
	Mat gray(image.rows,image.cols,CV_8UC1);
	int histogram[256];
	int cumulativeHistogram[256];
	double cumulativePossibilityHist[256];
	
	//////////////////Fills with 0s 
	for(int i=0;i<256;i++)
	{
		histogram[i]=0;
		cumulativeHistogram[i]=0;
	}
	///////// get histogram
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			histogram[image.at<uchar>(i,j)]++;

		}
	}

	////// get cumulative histogram
	
	cumulativeHistogram[0]=histogram[0];
	for(int i=1;i<256;i++)
	{
		cumulativeHistogram[i]=histogram[i]+cumulativeHistogram[i-1];
		
	}
	
	/// cumulative Possible histogram

	for(int i=0;i<256;i++)
	{
		cumulativePossibilityHist[i]=(double)cumulativeHistogram[i]/(image.rows*image.cols);
	}

	uchar min;
	uchar max;
	min = image.at<uchar>(0,0);
	max = image.at<uchar>(0,0);
	//find min and max gray value in picture matrix
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			if(image.at<uchar>(i,j)>max)
			{
				max= image.at<uchar>(i,j);
			}
			else if(image.at<uchar>(i,j)<min)
			{
				min=image.at<uchar>(i,j);
			}

		}
	}
	uchar window=30;

	cout<<(int)min<<endl;
	cout<<(int)max<<endl;
	//calculate and set new gray value 
	//this loop is simply extends the window
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			gray.at<uchar>(i,j)=cumulativePossibilityHist[image.at<uchar>(i,j)]*(max-min)+min;
		}
	}

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }  
	namedWindow( "Original", WINDOW_AUTOSIZE );// Create a window for display.
	imshow("Original",image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", gray);                   // Show our image inside it.

    waitKey(0);											 // Wait for a keystroke in the window
    return 0;
}