#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;
// This program classify the color of averaged pixel values of a picture.
int NUMBER_OF_COLOR=7;// specifies total number of color to contrast
const int RED[3]={0,0,255};
const int YELLOW[3]={0,255,255};
const int ORANGE[3]={0,165,255};
const int VIOLET[3]={238,130,238};
const int GREEN[3]={0,128,0};
const int BLUE[3]={255,0,0};
const int WHITE[3]={255,255,255};
const int* COLORS[7]={RED,YELLOW,ORANGE,VIOLET,GREEN,BLUE,WHITE};
const string COLOR_NAMES[7]={"RED","YELLOW","ORANGE","VIOLET","GREEN","BLUE","WHITE"};


// all parameters are taken from DuckDuckGo answer facility


int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
	int temp_val=cubeRoot(27);
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);	// Read the file
	Mat gray(image.rows,image.cols,CV_8UC1);
	long long first=0;//=184; //image.at<cv::Vec3b>(0,0)[0];
	long long second=0;// =181;//image.at<cv::Vec3b>(0,0)[1];
	long long third=0;// =176;//image.at<cv::Vec3b>(0,0)[2];
	//int diff = pow(third-238,2)+pow(second-130,2)+pow(first-238,2);
	//diff= sqrt(diff);
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			first=first+image.at<cv::Vec3b>(i,j)[0];
			second =second+image.at<cv::Vec3b>(i,j)[1];
			third =third+image.at<cv::Vec3b>(i,j)[2];
		}
	}
	int total=0;
	int oldTotal=58;
	int finalColor=0;
	first=first/(image.rows*image.cols);
	second=second/(image.rows*image.cols);
	third=third/(image.rows*image.cols);
	for(int i=0;i<NUMBER_OF_COLOR;i++)
	{
		total=cubeRoot(pow(first-COLORS[i][0],2)+pow(second-COLORS[i][1],2)+pow(third-COLORS[i][2],2));
		if(total<oldTotal)
		{
			finalColor=i;
			oldTotal=total;
		}
		
	}
	string color=COLOR_NAMES[finalColor];	


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
