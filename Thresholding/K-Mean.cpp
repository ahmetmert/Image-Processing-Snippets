#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void convertPictureToGrayScale(Mat& image,Mat& im);
int performK_Mean(Mat& im);
void tresholdImage(Mat& im,int t);
int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);	// Read the file
	Mat im(image.rows,image.cols,CV_8UC1);
	convertPictureToGrayScale(image,im);
	int treshold=performK_Mean(im);
	tresholdImage(im,treshold);

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", im);                   // Show our image inside it.

    waitKey(0);											 // Wait for a keystroke in the window
    return 0;
}
//Performs K_Mean algorithm in order to cluster pixels into two groups foreground and background
//In initial state we manually give mean values of background and foreground pixels. 
//In each while loop iteration treshold value is calculated average of mean background and foregrounds.
//In each iteration background and foreground means are also calculated. Pixel values below the threshold counted as background above the threshold are counted as foreground.
//While iterates until T value remains unchanged.
int performK_Mean(Mat& im)
{
	int m_b=40;
	int m_f=200;
	double tPrev=0,t=0;
	int totalBack=0,totalForeground=0;
	int counterBack=0,counterFore=0;

	do
	{
	tPrev=t;
	t=(m_b+m_f)/2;
	counterFore=0,totalForeground=0;
	counterBack=0,totalBack=0;

	for (int i = 0; i < im.rows; i++)
		{
			 for (int j = 0; j < im.cols; j++)
				 if(im.at<uchar>(i,j)>t)
				 {
					 totalForeground=totalForeground+im.at<uchar>(i,j);
					 counterFore++;
				 }
				 else
				 {
					 totalBack=totalBack+im.at<uchar>(i,j);
					 counterBack++;
				 }
			 
		}
		m_f=(int)totalForeground/counterFore;
		m_b=totalBack/counterBack;
	}
	while((t-tPrev)>0.5||(t-tPrev)<-0.5);

	return (int)t;
}

void convertPictureToGrayScale(Mat& image,Mat& im)
{
	for (int i = 0; i < image.rows; i++)
	{
		 for (int j = 0; j < image.cols; j++)
		 {
				im.at<uchar>(i,j)=image.at<cv::Vec3b>(i,j)[0]*0.11+image.at<cv::Vec3b>(i,j)[1]*0.58+image.at<cv::Vec3b>(i,j)[2]*0.289;	
		 }
	}
}
//A function that allocate 0's as pixel value to cells which pixel values are below the treshold. 255 otherwise.
void tresholdImage(Mat& im, int t)
{
	for (int i = 0; i < im.rows; i++)
	{
		 for (int j = 0; j < im.cols; j++)
		 {
			 if(im.at<uchar>(i,j)<t)
			 {
				 im.at<uchar>(i,j)=0;
			 }
			 else
			 {
				 im.at<uchar>(i,j)=255;
			 }
		 }
	}
}