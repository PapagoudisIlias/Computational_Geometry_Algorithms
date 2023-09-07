#include<iostream>
#include<cmath>
#include<vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include "CImg.h"
#include"Classes_And_Functions.h"


using namespace cimg_library;


int main()
{
	std::cout << "\nYou have to close the CImg window in order to continue to the next one\n\n\n\n";

	CImg<unsigned char> bg(width, height, 1, 3, 0);

	bg.draw_line(0, center_y, width, center_y, white);
	bg.draw_line(center_x, 0, center_x, height, white);

	CImg<unsigned char> image(width, height, 1, 3, 0);

	image.draw_line(0, center_y, width, center_y, white);
	image.draw_line(center_x, 0, center_x, height, white);

	//Writing the points of polygon on counter clockwise order

	std::vector<Vector> vertex{ Vector{0,0},Vector{390,280},Vector{50,200},Vector{100,160},Vector{-90,100},Vector{-80,-200} };

	PolyGon pol{ vertex };

	//Displaying polygon
	dispPol(pol, image, green);

	image.mirror('y');
	image.display();
	image = bg;

	// End of polygon 
	// New drawing of ear clipping

	earclippingDisp(pol);


	int ub_x{ width / 2 - 100 };
	int lb_x{ (-width) / 2 + 100 };
	int ub_y{ height / 2 - 100 };
	int lb_y{ (-height / 2) + 100 };

	srand(time(0));

	std::vector<Vector> points{};

	int numpoints{ 25 };
	//Creating random points
	for (int i = 0; i < numpoints; ++i)
	{
		int x_rand{ (rand() % (ub_x - lb_x + 1)) + lb_x };
		int y_rand{ (rand() % (ub_y - lb_y + 1)) + lb_y };
		points.push_back(Vector{ (double)x_rand ,(double)y_rand });
	}
	//Displaying the convex hull
	convexHullDisp(points);

	//Creating 2 polygons

	std::vector<Vector> pol1{ Vector{0,0},Vector{-100,100},Vector{-180,0} };


	std::vector<Vector> pol2{ Vector{50,0},Vector{-50,130},Vector{-220,80},Vector{-100,-80} };

	//Live collision detection test 
	SATdisp(pol1, pol2);



	return 0;

}
