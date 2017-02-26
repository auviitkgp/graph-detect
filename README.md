# PROBLEM STATEMENT

### Sample Input 

Such an image of a graph, having X and Y axes. Find the images to be tested at the `input_images/` directory of the repository.

![alt tag](sample_input.jpg)

### Sample Output 

Input image + rectangular boxes drawn around the markings on the axes.

![alt tag](sample_output.jpg)

### Languages 

C++ / Python

### Useful tips

- Browse through the OpenCV library documentation and find functions that would be helpful to implement this.

- The basic idea of solution, is to find contours (regions, maybe `rectangular` ones) that have atleast a certain level of text density and are on the left side of Y-axis or below the X-axis.

- Text can be recognised by the sudden change in intensity level with respect to the background.

- The trick lies in differentiating the X & Y axes from the graph's curve - use Google, StackOverflow and OpenCV tutorials to the maximum extent.

It may be tough to get all the readings accurately. Keep trying, submit your best attempt. Good luck!

### Important Note

- Coordinates of the origin of the graph should not be hard-coded specific to a particular image. The same script should work on as many images as given in the `input_images/` directory.

- Variables like cutoff text density can be hard-coded. Bonus points for deciding the cutoff intensity dynamically.

### Submission Guidelines

1. Fork this repository on GitHub.

2. Clone your fork with `git clone` statement.

3. Make your local changes, in the sub-directory: `graph-detect/<username>/` (Here, `username` is your Github username)

4. Push these changes to your fork with `git add`, `git commit` and `git push` statements.

5. Create a Pull Request to this repository by comparing across forks with your fork.
