The homework we are asked to do is classifiying colors in a Picture. This Picture is taken by me and it only contains the same color. This make classifiying easy for the program
Project is implemented in cpp and opencv library is used for matrix calculations. No function is used but pow() for exponential calculation.
Step 1) The method that I used classifies colors wih their RGB values. Each Red gree and blue value of every pixels are sum up and they are divided the total number of pixel. Doing that, I find average pixel value o all pixel values in a picture. Code snipped below is showing the method.
![alt tag]({{site.baseurl}}/http://radio.feld.cvut.cz/matlab/toolbox/images/colorcube.jpg)
Step 2) RGB is considered as 3 dimensional space showing below. Each color is represented as a point. Here are points represents colors;
BGR
RED =(0,0,255);
YELLOW =(0,255,255);
ORANGE =(0,165,255);
VIOLET =(238,130,238);
GREEN =(0,128,0);
BLUE =(255,0,0);
WHITE =(255,255,255);

Calculated pixel value is also represent a point in this 3D space. It is assumed that if cacculated point is closest to a color as euclidean distance, the image is that color. For instance average RGB value of a image is (10,120,5), It can be easly seen that this point is closest to Green color. And the image is classified as green.

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






