##Image Enhancement

calculate histogram array
```C++
for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			histogram[image.at<uchar>(i,j)]++;

		}
	}
```
Night Image

![alt text](Inputs/nightOriginal.png "Night Image")

Histogram Equalization applied Night Image

![alt text](Outputs/nightEnhanced.png "Enhanced Night Image")

Manhattan Image

![alt text](Inputs/NYOriginal.png "Night Image")

Histogram Equalization applied Manhattan Image

![alt text](Outputs/NYEnhanced.png "Enhanced Night Image")



