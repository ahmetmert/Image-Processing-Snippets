#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;
void convertPictureToGrayScale(Mat& image,Mat& im);
void blurTheImage(Mat& im,Mat& blurred);
void gradient(Mat& im,Mat& gradient,double derivative[3][3]);
void getMagnitude(Mat& gradientX,Mat& gradientY,Mat& magnitude);
int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
	
	//filitrelerin double degeri almasi
    Mat image;
	Mat image2;
	Mat grayImage;
	//must be initilized
    image = imread(argv[1], IMREAD_COLOR); // Read the file
	 imshow( "original", image ); // Show our image inside it.

	
	// generate 8 bit mat image
	Mat im(image.rows,image.cols,CV_8UC1);
	// Convert image to gray scatle
	convertPictureToGrayScale(image,im);
	//Blur the image
	Mat blurred(im.rows,im.cols,CV_8UC1);
	blurTheImage(im,blurred);
	
	/////////////////////////////////////
	////////////GRADIENT/////////////////
	///////////////X////////////////////
	Mat gradientX(image.rows,image.cols,CV_8UC1);
	Mat gradientY(image.rows,image.cols,CV_8UC1);
	double derivativeX[3][3]={{0.125,0,-0.125},{0.25,0,-0.25},{0.125,0,-0.125}};
	double derivativeY[3][3]={{-0.125,-0.25,-0.125},{0,0,0},{0.125,0.25,0.125}};

	gradient(im,gradientX,derivativeX);
	imshow( "gradientX", gradientX ); 

	gradient(im,gradientY,derivativeY);
		imshow( "gradientY", gradientY );

	/////////////////////////////////////////
	Mat magnitude(image.rows,image.cols,CV_8UC1);
	getMagnitude(gradientX,gradientY,magnitude);

	imshow( "magnitude", magnitude ); // Show our image inside it.




    if(! image.data ) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

   // namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
  //  imshow( "Display window3", gradientX ); // Show our image inside it.

    waitKey(0); // Wait for a keystroke in the window
    return 0;
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
	    imshow( "gray", im ); // Show our image inside it.
}
void blurTheImage(Mat& im,Mat& blurred)
{
	double total=0;
	double filitre[3][3]={{0.125,0.125,0.125},{0.125,0.125,0.125},{0.125,0.125,0.125}};

	for(int i=1;i<blurred.rows-1;i++)
	{
		for(int j=1;j<blurred.cols-1;j++)
		{
			total=0;
			for(int x=-1;x<2;x++)
			{
				for(int y=-1;y<2;y++)
				{
					total=total+im.at<uchar>(i+x,j+y)*filitre[x+1][y+1];
				}
			}
			blurred.at<uchar>(i-1,j-1)=total;
		}
	}
	imshow( "blurred", blurred ); // Show our image inside it.
}
void gradient(Mat& im,Mat& gradient,double derivative[3][3])
{
		
	double total=0;
	for(int i=1;i<im.rows-1;i++)
	{
		for(int j=1;j<im.cols-1;j++)
		{
			total=0;
			for(int x=-1;x<2;x++)
			{
				for(int y=-1;y<2;y++)
				{
					total=total+im.at<uchar>(i+x,j+y)*derivative[x+1][y+1];
				}
			}
			gradient.at<uchar>(i-1,j-1)=total;
		}
	}




	
}
void getMagnitude(Mat& gradientX,Mat& gradientY,Mat& magnitude)
{
	for(int i=0;i<gradientX.rows;i++)
	{
		for(int j=0;j<gradientX.cols;j++)
		{
			magnitude.at<uchar>(i,j)=sqrt(pow(gradientX.at<uchar>(i,j),2)+pow(gradientY.at<uchar>(i,j),2));

		}
	}


}