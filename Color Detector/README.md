##Color Detector

This primitive code snippet classifies colors in a Picture. Pictures to be tested are taken by me and it only contains the single color. This make classifiying easy for the program

Project is implemented in cpp and opencv library is used for matrix calculations. No function is used but pow() for exponential calculation.

Step 1) The method that I used classifies colors with respect to their RGB values. Each Red green and blue value of pixel are sum up and divided the total number of pixels. Doing that, average pixel value of all pixels are found in a picture. Code snipped below is showing the method.

```C++
Mat gray(image.rows,image.cols,CV_8UC1);
	long long first=0;
	long long second=0;
	long long third=0;
	
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			first=first+image.at<cv::Vec3b>(i,j)[0];
			second =second+image.at<cv::Vec3b>(i,j)[1];
			third =third+image.at<cv::Vec3b>(i,j)[2];
		}
	}
```

![alt text](http://radio.feld.cvut.cz/matlab/toolbox/images/colorcube.jpg "3D Representation of RGB color space")

Step 2) RGB is considered as 3 dimensional space showing below. Each color is represented as a point. Here are points represents colors;

BGR
RED =(0,0,255);
YELLOW =(0,255,255);
ORANGE =(0,165,255);
VIOLET =(238,130,238);
GREEN =(0,128,0);
BLUE =(255,0,0);
WHITE =(255,255,255);

Calculated pixel value is also represent as a point in this 3D space. It is assumed that if cacculated point is closest to a color with respect to euclidean distance, the image is classified as that color. For instance average RGB value of a image is (10,120,5), It can be easly seen that this point is closest to Green color. And the image is classified as green.

```C++

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
```

![alt text](https://www.cs.drexel.edu/~mcs171/Sp07/assignments/HW4/distance.JPG"Formula of distance between two points")

Here is the result of experiment.

| Name          | Original Color|Classified as | P/F |
| ------------- |:-------------:| -----:|----|
| Raket.jpg     | Red | Red |P|
| bomba_kitabi.jpg     | Green | Green |P|
| Kordon.jpg     | Red | Red |P|
| Masa.jpg    | White | White |P|
| Paper.jpg     | White | White |P|
| Hdd.jpg     | Red | Red |P|
| Sünger.jpg     | Yellow | Orange |F|
| Bayrak.jpg     | Red | Red |P|
| omer_seyfettin_kitabi.jpg    |Green | Green |P|
| Buyuk_gunes.jpg    | White | White |P|
| cicek.jpg    | ? | Orange |?|
| Mor_cicek.jpg    | Violet | Violet |P|
| Tepsi.jpg    | Green | Green |P|
|Peçetelik.jpg   | White | Violet |F|
| Car1.jpg   | Blue | Blue |P|
| Car2.jpg    | Blue | Green |F|
| Tabela.jpg   | Orange | Orange |P|
| Pantolon.jpg    | Blue | Blue |P|
| Mor.jpg    | Violet | Violet |P|
| Portakal.jpg   | Orange | Orange |P|






