#Submission from basher666

###Algorithm

This code utilizes the gradient based method mentioned in this [link](http://stackoverflow.com/questions/23506105/extracting-text-opencv) . This technique basically does a morphological gradient operation on the image (difference between dilation and erosion of an image) and then does a morphological closing operation (dilation followed by erosion) on the resultant image. After these operations , the text region become a solid white block. After finding the contours of the image , a bounding rectangle is used to cover the contours. The origin of the image is found by finding all points of intersection of every pair of lines, and then chosing the point which is at a minimum distance from the lower left corner of the image. The centre is marked with a red circle in the final image. The output images are kept in 'output_images' folder.

###Running the code

The code is in c++ and I used cmake to build the project. The code is run by ./(executable_name) (path_to_image) .
