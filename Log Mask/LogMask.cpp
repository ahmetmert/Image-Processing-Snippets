#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <map>
#include <cmath>
#define M_PI           3.14159265358979323846 // from stackowerflow
#define E 2.71828 // euler's constant from wikipedia article
#define N 2.0 //Dimension
using namespace cv;
using namespace std;
void findLaplacianMask(Mat& mask,double sigma,int widthAndHeight,float constant);
void performMask(Mat& image,Mat& resultImage,Mat filterMat,int widthAndHeight);
int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
	 // Where the kernel value stored
	


	int widthAndHeight =7;
	double sigma =1.4;
	float constant =1000; //needs to be explained 
	Mat filterMat(widthAndHeight,widthAndHeight, CV_64F);

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);	// Read the file

	Mat resultImage(image.rows,image.cols,CV_8UC1);

	findLaplacianMask(filterMat,sigma,widthAndHeight,constant);
	performMask(image,resultImage,filterMat,widthAndHeight);

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", resultImage);                   // Show our image inside it.

    waitKey(0);											 // Wait for a keystroke in the window
    return 0;
}
void findLaplacianMask(Mat& mask,double sigma,int widthAndHeight,float constant)
{
	
	double x=0;
	double y=0;
//	double sigma = 1.4;
	double firstPart,secondPart,ePow =0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	double total=0;
	int start = -widthAndHeight/2;
	int end= (widthAndHeight/2)+1;
	//

	for(int x=start;x<end;x++)
	{
		for(int y=start;y<end;y++)
		{
			firstPart=-(1/(M_PI*sigma*sigma*sigma*sigma));
			secondPart=1-((x*x+y*y)/(2*sigma*sigma));
			ePow= exp(-((x*x+y*y)/(2*sigma*sigma)));
			//cout<<(int)(constant*(firstPart*secondPart*ePow));
			//cout<<" ";
			mask.at<double>(x+widthAndHeight/2,y+widthAndHeight/2)=(double)(constant*(firstPart*secondPart*ePow));
			total=total+(double)(constant*(firstPart*secondPart*(ePow)));
		}
		//cout<<endl;
	}
	//cout<<total;
	//cout<<"sth";
}
void performMask(Mat& image,Mat& resultImage,Mat filterMat,int widthAndHeight)
{
	int start = -widthAndHeight/2;
	int end= (widthAndHeight/2)+1;
	int total;
	for(int i=widthAndHeight/2;i<image.rows-(widthAndHeight/2);i++)
	{
		for(int j=widthAndHeight/2;j<image.cols-(widthAndHeight/2);j++)
		{
			total=0;
			for(int x=start;x<end;x++)
			{
				for(int y=start;y<end;y++)
				{
					total=total+image.at<uchar>(i+x,j+y)*filterMat.at<double>(x+widthAndHeight/2,y+widthAndHeight/2);
				}
			}
			total<0 ? total=0:true;
			total>255 ? total=255:true;
			resultImage.at<uchar>(i,j)=total;
		}
	}
	
}
