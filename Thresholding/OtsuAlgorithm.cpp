#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int NUMBER_OF_COLORS=256;//8 Bits
void getHistogramArray(Mat,int,vector<double>&);
//returns proper k which is treshold value between 0 to 255
int performOtsu(Mat& image,int channelNumber);
void findWs(vector<double>& prob,double& w0,double& w1,int k);
void findMeans(double& m0,double&m1,double w0,double w1,vector<double>& prob,int k);
Mat andOperation(int opt0,int opt1,int opt2,Mat& image);
int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);	// Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	
	int optimalTresholdforChannel0 =performOtsu(image,0);
	int optimalTresholdforChannel1 =performOtsu(image,1);
	int optimalTresholdforChannel2 =performOtsu(image,2);



	Mat gray(image.rows,image.cols,CV_8UC1);
	gray =andOperation(optimalTresholdforChannel0,optimalTresholdforChannel1,optimalTresholdforChannel2,image);

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", gray );                   // Show our image inside it.

    waitKey(0);											 // Wait for a keystroke in the window
    return 0;
}

int performOtsu(Mat& image,int channelNumber)
{
		vector<double> prob(NUMBER_OF_COLORS);
		getHistogramArray(image,channelNumber,prob);
		//vect is probability vector of histogram
		double varience=0,varienceMax=0;
		//check for ever k from 0 to NUMBER_OF_COLOR
		int treshold=0;
		for(int k=0;k<NUMBER_OF_COLORS;k++)
		{
			double w0=0,w1=0,m0=0,m1=0;

			findWs(prob,w0,w1,k);

			findMeans(m0,m1,w0,w1,prob,k);

			varience =w0*w1*(m0-m1)*(m0-m1);// needs to be maximum value
			if(varience>varienceMax)
			{
				varienceMax=varience;
				treshold=k;
			}
		}
		//end for

		return treshold;


}
//Does and operation to each pixel of matrixes
Mat andOperation(int opt0,int opt1,int opt2,Mat& image)
{
		Mat oneChannel(image.rows,image.cols,CV_8UC1);
	for (int i = 0; i < image.rows; i++)
		{
			 for (int j = 0; j < image.cols; j++)
			{
				 if(image.at<cv::Vec3b>(i,j)[0]>opt0&&image.at<cv::Vec3b>(i,j)[1]>opt1&&image.at<cv::Vec3b>(i,j)[2]>opt2)
				 {
					oneChannel.at<uchar>(i,j)=255;
				 }
				 else
				 {
					 oneChannel.at<uchar>(i,j)=0;
				 }
		 }
	}
	return oneChannel;
}
//find overall probability 
void findWs(vector<double>& prob,double& w0,double& w1,int k)
{
	for(int i=0;i<k;i++)
	{
		w0=w0+prob[i];
	}
	w1=1-w0;
}
//find expectation of probability values of histogram
void findMeans(double& m0,double&m1,double w0,double w1,vector<double>& prob,int k)
{
	for(int i=0;i<k;i++)
	{
		m0=m0+i*prob[i];
	}
	
	for(int i=k; i<NUMBER_OF_COLORS;i++)
	{
		m1=m1+i*prob[i];
	}

	m0=m0/w0;
	m1=m1/w1;


}
void fillWithZeros(vector<double> histogram)
{
	for(int i=0;i<NUMBER_OF_COLORS;i++)
	{
		histogram[i]=0;
	}
}
//get histogram vales as array
void getHistogramArray(Mat image,int channelNumber,vector<double> &histogram)
{
	fillWithZeros(histogram);
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			histogram[image.at<cv::Vec3b>(i,j)[channelNumber]]++;
		}
	}
	for(int i=0;i<NUMBER_OF_COLORS;i++)
	{
		histogram[i]=histogram[i]/(image.rows*image.cols);
	}
}

