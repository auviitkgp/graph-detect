# PROBLEM STATEMENT

### Input 

An image of a graph,having X and Y axes.

![alt tag](input.jpg)

### Output 

Input image + rectangular boxes drawn around the markings on the axes.

![alt tag](output.jpg)

### Useful tips

Browse through the OpenCV library documentation and find functions that would be helpful to implement this.

The basic idea of solution, is to find contours (regions, maybe `rectangular` ones) that have a minimum text density and are on the left side of Y-axis or below the X-axis.

Text can be recognised by their sudden change in intensity level with respect to their background.

But the trick lies in differentiating the X & Y axes from the graph's curve - use Google, StackOverflow and OpenCV tutorials to the maximum extent.

It may be tough to get all the readings accurately. but it's fine.

Good luck!

### Languages 

C++ / Python

### Submission Guidelines

(1) Fork this repository on GitHub.

(2) Clone your fork with `git clone` statement.

(3) Make your local changes, in a sub-directory (say, `graph-detect/<username>/`).

(4) Push these changes to your fork with `git add`, `git commit` and `git push` statements.

(5) Create a Pull Request to this repository by comparing across forks with your fork.