#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;
void convertPictureToGrayScale(Mat& image,Mat& im);
int performK_Mean(Mat& im);
void tresholdImage(Mat& im,int t);
void findRegions(Mat& im);
const int CON_ARRAY_SIZE= 5000;
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
	cout<<"treshold value is :"<<treshold<<endl;
	tresholdImage(im,treshold);

	findRegions(im);

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
				 im.at<uchar>(i,j)=1;
			 }
		 }
	}
}
//The method that detect regions in a matrix
//array of im holds area information with demonstrating them with different shade of gray.
void findRegions(Mat& im)
{
	int regionCounter=0;  

	Mat label(im.rows,im.cols,CV_32S);
	int connectivityArray[CON_ARRAY_SIZE];
	for(int i=0;i<CON_ARRAY_SIZE;i++)
	{
		connectivityArray[i]=-1;
	}
	//first pass
	for(int i=0;i<im.rows;i++)
	{
		for(int j=0;j<im.cols;j++)
		{
			if(im.at<uchar>(i,j)==0)// If the pixel does not belong to object
			{
				label.at<int>(i,j)=-1;
				continue;
			}
			else
			{
				if(i-1<0&& j-1<0)// upper left
				{
					//corner case
					label.at<int>(0,0)=regionCounter;
					connectivityArray[regionCounter]=regionCounter;
					regionCounter++;
				}
				else if(i-1<0)//upper line
				{
					if(im.at<uchar>(i,j-1)==1)
					{
						label.at<int>(i,j)=label.at<int>(i,j-1);
					}
					else
					{
						label.at<int>(i,j)=regionCounter;
						connectivityArray[regionCounter]=regionCounter;
						regionCounter++;
					}
				}
				else if(j-1<0) // leftmost column
				{
					if(im.at<uchar>(i-1,j)==1)
					{
						label.at<int>(i,j)=label.at<int>(i-1,j);
					}
					else
					{
						label.at<int>(i,j)=regionCounter;
						connectivityArray[regionCounter]=regionCounter;
						regionCounter++;
					}
				}
				else//not corner case
				{
					if(im.at<uchar>(i-1,j)==1&&im.at<uchar>(i,j-1)==1)//both neightboor are part of the object (binary=1)
					{
						if(label.at<int>(i-1,j)<label.at<int>(i,j-1))
						{
							label.at<int>(i,j)=label.at<int>(i-1,j);
							connectivityArray[label.at<int>(i,j-1)]=label.at<int>(i-1,j);
						}
						else if(label.at<int>(i-1,j)>label.at<int>(i,j-1))
						{
							label.at<int>(i,j)=label.at<int>(i,j-1);
							connectivityArray[label.at<int>(i-1,j)]=label.at<int>(i,j-1);
						}
						else
						{
							label.at<int>(i,j)=label.at<int>(i-1,j);
						}
					}

					else if(im.at<uchar>(i-1,j)==1&&im.at<uchar>(i,j-1)==0)// only upper neightboor is part of the object
					{
						label.at<int>(i,j)=label.at<int>(i-1,j);
					}

					else if(im.at<uchar>(i-1,j)==0&&im.at<uchar>(i,j-1)==1)// only left neightboor is part of the object
					{
						label.at<int>(i,j)=label.at<int>(i,j-1);
					}
					else// unconnected pixel
					{
						label.at<int>(i,j)=regionCounter;
						connectivityArray[regionCounter]=regionCounter;
						regionCounter++;
					}

				}
			}
		}
	}
	int counter=0;
	for(int i=0;i<CON_ARRAY_SIZE;i++)
	{
		if(connectivityArray[i]==i)
		{
			counter++;
		}
	}
	for(int i=0;connectivityArray[i]!=-1;i++)
	{
		connectivityArray[i]=connectivityArray[connectivityArray[i]];
	}

	//second iteration
	for(int i=0;i<im.rows;i++)
	{
		for(int j=0;j<im.cols;j++)
		{
			if(label.at<int>(i,j)!=-1)
			{
				label.at<int>(i,j)=connectivityArray[label.at<int>(i,j)];
			}
		}
	}

	for(int i=0;i<im.rows;i++)
	{
		for(int j=0;j<im.cols;j++)
		{
			im.at<uchar>(i,j)=10*(uchar)label.at<int>(i,j);

		}
	}


}