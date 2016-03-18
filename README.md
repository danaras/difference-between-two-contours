I have been working on a code in OpenFrameworks to calculate the difference between two features. Assuming that I already have two images of features that I want to compare, this code will transform these images into greyscale version of them. Then apply a sobel filter and blur them. After all the filtering and adjusting the brightness, it will find the contours of the images and crop the images to their bounding boxes of the contours. Finally it calculates the euclidian difference of the pixels between these processed images and returns the result.

Here is the output that i get when I run the code:

![](https://github.com/danaras/difference-between-two-contours/blob/master/Screen%20Shot%202016-03-18%20at%204.32.07%20PM.png)

I used [ofxCv](https://github.com/kylemcdonald/ofxCv) in this example.
