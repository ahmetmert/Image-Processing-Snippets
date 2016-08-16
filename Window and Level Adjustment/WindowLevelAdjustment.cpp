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
	int histogram[256];
	int cumulatiHistogram[256];
	double cumulativePossibilityHist[256];
	//cout<<image.r*image.cols;
	//////////////////Fills with 0s 
	double window=100;
	double level=200;
	cout<<((double)image.at<uchar>(0,0)-(level-window/2.0))*((double)255/(window/2));
	// The formula is (pixelValue- lowerLimit) * 255/2*window
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			if(((double)image.at<uchar>(i,j)-(level-window))*((double)255/(2*window))<0)
			{
				image.at<uchar>(i,j)=0;			
			}
			else if(((double)image.at<uchar>(i,j)-(level-window))*((double)255/(2*window))>255)
			{
				image.at<uchar>(i,j)=255;
			}
			else
			{
				image.at<uchar>(i,j)=(uchar)(((double)image.at<uchar>(i,j)-(level-window))*((double)255/(2*window)));
			}
		}
	}
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }  

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image);                   // Show our image inside it.

    waitKey(0);											 // Wait for a keystroke in the window
    return 0;
}