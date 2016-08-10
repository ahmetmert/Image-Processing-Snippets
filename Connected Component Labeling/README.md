##Connected Component Labeling

This primitive code snippet detects connected components in a Picture. 

Project is implemented in cpp and opencv library is used for matrix calculations. 

Input image:
 ![alt tag](Inputs/guide_8bits.bmp "Original Image")


Step 1) Picture is converted to gray image with the formula of "Gray pixel Value = Red * 0.289 + Green * 0.58 + Blue * 0.11"

```C++
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
```


Step 2) K_Mean clustering is used in order to determine a threshold value

Step 3) Perform threshold with the following method so only foreground pixels can be seen 

```C++
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
```

Step 4) Find region method is called. Following youtube video explains the logic behind the algorithm.

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/rVtFyefbJio/0.jpg)](http://www.youtube.com/watch?v=rVtFyefbJio)
