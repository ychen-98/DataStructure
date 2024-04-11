
Occlusion Angle Calculator

// Overview

This program generates N (user-defined) random non-overlapping circles and places tilted rectangles within them. 
The primary objective is to calculates the coverage angles from each rectangle to the origin and determines the 
sum of all occluded angles.


// Compilation and Execution

	1. Compile: 

	make 

	2. Run: 

	make run 

	3. Clean:

	make clean


// Inputs 

	N: This is the number of circles / rectangles you want to generate. The program prompts you to enter this 
	value at runtime.

// Outputs

	Data for random non-overlapping circles in R format (visualization).
		x-coordinates of circle centers
		y-coordinates of circle centers
		radii of the circles

	Data for random non-overlapping rectangles in R format (visualization). 
		x-coordinates of rectangle vertices
		y-coordinates of rectangle vertices

	The sum of all occluded angles in radians.


// Key Functions:
	isOverlapping: Determines if two circles overlap.
	overlapsWithOrigin: Determines if a circle overlaps with the origin.
	rectangleInCircle: Generates a tilted rectangle within a circle.
	angleToOrigin: Calculates the angle from a point to the origin.
	coverageAnglesFromRectangleToOrigin: Finds the range of angles covered by a rectangle when viewed from the origin.
	anglesOverlaps: Checks if two angle ranges overlap.

// Key Data Structures:
	Point: Represents a point in 2D space.
	Circle: Represents a circle with a center (a Point) and a radius.
	Rectangle: Represents a rectangle with four vertices (Points).
	coverage: 2D array representing the coverage of angles by rectangles.


// Limitations and Assumptions:

	The program assumes the resolution for angles to be 0.1 radians, which is set by the constant RESOLUTION. 
	Adjusting this value will influence the granularity of the occlusion calculation.

