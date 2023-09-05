#include"CImg.h"
#include<iostream>
#include<vector>
#include"Classes_And_Functions.h"


using namespace cimg_library;

double pi = 3.14159;

const  int width = 801;
const  int height = 601;
const unsigned int center_x = width / 2;
const unsigned int center_y = height / 2;

const unsigned char black[] = { 0, 0, 0 };  // RGB colors
const unsigned char red[] = { 255, 0, 0 };
const unsigned char white[] = { 255, 255, 255 };
const unsigned char green[] = { 0, 255, 0 };
const unsigned char blue[] = { 0, 0, 255 };
const unsigned char orange[] = { 255, 140, 0 };


	Vector::Vector(double x = 0.0, double y = 0.0) :m_x{ x }, m_y{ y } {};
	

	Vector Vector::operator+(const Vector b)
	{
		Vector v{ m_x + b.m_x, m_y + b.m_y };
		return v;

	}

	Vector Vector::operator-(const Vector b)
	{
		Vector v{ m_x - b.m_x, m_y - b.m_y };
		return v;

	}

	double Vector::getX() const { return m_x; };
	double Vector::getY() const { return m_y; };

	// bool IsInside(const Vector& a, const Vector& v0, const Vector& v1, const Vector& v2);


	 double operator*(const Vector& a, const  Vector& b)
	{
		return a.m_x * b.m_x + a.m_y * b.m_y;
	}

	 Vector operator*(const Vector& a, double k)
	{
		return Vector{ k * a.m_x,k * a.m_y };
	}

	 Vector operator*(double k, const Vector& a)
	{
		return Vector{ k * a.m_x,k * a.m_y };
	}

	bool Vector::operator == (const Vector& a) {
		if (m_x == a.m_x && m_y == a.m_y)
			return true;
		return false;
	}

	bool Vector::operator != (const Vector& a) {
		if (m_x != a.m_x || m_y != a.m_y)
			return true;
		return false;
	}

	 double cross(const Vector& a, const Vector& b)
	{
		return a.m_x * b.m_y - a.m_y * b.m_x;
	}


	double Vector::magnitude()
	{
		return sqrt(pow(this->m_x, 2) + pow(this->m_y, 2));
	}


	 Vector Vector::normal()
	{
		Vector norm{ 0,0 };

		if (m_x == 0 && m_y == 0) return norm;


		norm.m_x = -180 * m_y / (int)sqrt(m_x * m_x + m_y * m_y);
		norm.m_y = 180 * m_x / (int)sqrt(m_x * m_x + m_y * m_y);


		return norm;
	}

	void Vector::mirrorY()
	{
		m_y = -m_y;
	}

	double angle(Vector a, Vector b)
	{
		if (a.magnitude() == 0 || b.magnitude() == 0)
		{
			std::cout << "Not possible to measure the angle. We have the zero vector\n";
			return -1;
		}
		//std::cout << (a * b) << "\n" << (a.magnitude() * b.magnitude()) << "\n";

		return acos((a * b) / (a.magnitude() * b.magnitude()));
		//return 1;
	}

	std::ostream& operator<<(std::ostream& out, Vector a)
	{
		out << "(" << a.m_x << ", " << a.m_y << ")";
		return out;
	}

	void dispVecPoint(const Vector& a, CImg<unsigned char>& image, const unsigned char color[3])
	{
		image.draw_circle(center_x + (int)a.getX(), center_y + (int)a.getY(), 2, color, 1.0f);
	}

	void dispVecPoint(const Vector& a, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym)
	{

		image.draw_circle((int)a.getX() + xm, -(int)a.getY() + ym, 2, color, 1.0f);
	}

	void dispVecArrow(const Vector& a, CImg<unsigned char>& image, const unsigned char color[3])
	{
		image.draw_line(0, center_y, width, center_y, white);
		image.draw_line(center_x, 0, center_x, height, white);
		image.draw_arrow(center_x, center_y, center_x + (int)a.getX(), center_y + (int)a.getY(), color);
	}

	void dispVecArrow(const Vector& a, const Vector& start, CImg<unsigned char>& image, const unsigned char color[3])
	{
		image.draw_line(0, center_y, width, center_y, white);
		image.draw_line(center_x, 0, center_x, height, white);
		image.draw_arrow(center_x + (int)start.getX(), center_y + (int)start.getY(), center_x + (int)start.getX() + (int)a.getX(), center_y + (int)start.getY() + (int)a.getY(), color);
	}

	Vector perpendicular(const Vector& a)
	{
		return Vector{ a.m_y,-a.m_x };
	}

	Vector proj(const Vector& a, const Vector& b)
	{
		return ((a * b) / (b * b)) * b;
	}

	Vector& leftPoint(std::vector<Vector>& points)
	{
		double min{ width / 2 };
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getX() < min) min = points[i].getX();
		}
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getX() == min) return points[i];
		}

	}

	Vector& rightPoint(std::vector<Vector>& points)
	{
		double max{ -width / 2 };
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getX() > max) max = points[i].getX();
		}
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getX() == max) return points[i];
		}

	}

	Vector& downPoint(std::vector<Vector>& points)
	{
		double max{ -height / 2 };
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getY() > max) max = points[i].getY();
		}
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getY() == max) return points[i];
		}

	}

	Vector& upperPoint(std::vector<Vector>& points)
	{
		double min{ height / 2 };
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getY() < min) min = points[i].getY();
		}
		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].getY() == min) return points[i];
		}

	}

	
		Segment::Segment(Vector a, Vector b) :m_a{ a }, m_b{ b }
		{};
		Vector const Segment::vec()
		{
			return Vector{ m_b - m_a };

		}

		 void dispSegm(const Segment& ab, CImg<unsigned char>& image, const unsigned char color[3]);
		 void dispSegm(const Segment& ab, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym);

	void dispSegm(const Segment& ab, CImg<unsigned char>& image, const unsigned char color[3])
	{
		image.draw_line(center_x + (int)ab.m_a.getX(), center_y + (int)ab.m_a.getY(), center_x + (int)ab.m_b.getX(), center_y + (int)ab.m_b.getY(), color);
	}

	void dispSegm(const Segment& ab, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym)
	{
		image.draw_line((int)ab.m_a.getX() + xm, -(int)ab.m_a.getY() + ym, (int)ab.m_b.getX() + xm, -(int)ab.m_b.getY() + ym, color);
	}

	Vector proj(const Vector& a, Segment& seg)
	{
		return ((a * seg.vec()) / (seg.vec() * seg.vec())) * seg.vec();
	}

	Vector perpendicular(Segment& seg)
	{
		return perpendicular(seg.vec());
	}

	
		PolyGon::PolyGon(std::vector<Vector> vertex) {
			for (int i = 0; i < vertex.size(); ++i)
			{
				m_vertex.push_back(vertex[i]);
				m_segment.push_back(Segment{ vertex[i],vertex[(i + 1) % vertex.size()] });
			}
		};

		PolyGon::PolyGon(const Vector& v0, const Vector& v1, const Vector& v2) {

			m_vertex.push_back(v0);
			m_vertex.push_back(v1);
			m_vertex.push_back(v2);

		};

		/*
		 void dispPol(const PolyGon& pol, CImg<unsigned char>& image, const unsigned char color[3]);

		 void dispPol(const PolyGon& pol, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym);

		 bool IsInside(const Vector& a, const PolyGon& pol);

		 void MakeEqual(std::vector<Vector>& vertex_triag, const PolyGon& pol);
		 */
		int PolyGon::size() const { return m_vertex.size(); }

		Vector PolyGon::getVec(int i) const { return m_vertex[i]; }

		Segment PolyGon::getSeg(int i) const { return m_segment[i]; }

		void PolyGon::update(int xm, int ym)
		{
			for (int i = 0; i < m_vertex.size(); ++i)
			{
				m_vertex[i] = m_vertex[i] + Vector{ (double)xm,(double)ym };
			}
		}


		 PolyGon operator+(const PolyGon& pol, const Vector b)
		{
			PolyGon Pol{ pol };
			for (int i = 0; i < pol.m_vertex.size(); ++i)
			{
				Pol.m_vertex[i] = Pol.m_vertex[i] + b;
			}
			return Pol;

		}



		 void MakeEqual(std::vector<Vector>& vertex_triag, const PolyGon& pol)
		 {

			 for (int i = 0; i < pol.size(); ++i)
			 {
				 vertex_triag.push_back(pol.m_vertex[i]);
			 }
		 }

		 void dispPol(const PolyGon& pol, CImg<unsigned char>& image, const unsigned char color[3])
		 {
			 for (int i = 0; i < pol.m_vertex.size(); ++i)
			 {
				 dispSegm(Segment{ pol.m_vertex[i % pol.m_vertex.size()],pol.m_vertex[(i + 1) % pol.m_vertex.size()] }, image, color);
				 dispVecPoint(pol.m_vertex[i % pol.m_vertex.size()], image, red);
				 dispVecPoint(pol.m_vertex[(i + 1) % pol.m_vertex.size()], image, red);
			 }

		 }

		 void dispPol(const PolyGon& pol, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym)
		 {
			 for (int i = 0; i < pol.m_vertex.size(); ++i)
			 {
				 dispSegm(Segment{ pol.m_vertex[i % pol.m_vertex.size()],pol.m_vertex[(i + 1) % pol.m_vertex.size()] }, image, color, xm, ym);
				 dispVecPoint(pol.m_vertex[i % pol.m_vertex.size()], image, red, xm, ym);
				 dispVecPoint(pol.m_vertex[(i + 1) % pol.m_vertex.size()], image, red, xm, ym);
			 }

		 }

		 bool IsInside(const Vector& a, const PolyGon& pol)
		 {
			 if (pol.m_vertex.size() == 3) {

				 Vector AB{ pol.m_vertex[1].getX() - pol.m_vertex[0].getX(),pol.m_vertex[1].getY() - pol.m_vertex[0].getY() };
				 Vector AC{ pol.m_vertex[2].getX() - pol.m_vertex[0].getX(),pol.m_vertex[2].getY() - pol.m_vertex[0].getY() };

				 Vector AP{ a.getX() - pol.m_vertex[0].getX(),a.getY() - pol.m_vertex[0].getY() };

				 int det;
				 det = static_cast<int>(AB.getX() * AC.getY() - AC.getX() * AB.getY());

				 if (det == 0)
				 {
					 std::cout << "No triangle but collinear points\n";
					 return false;
				 }

				 double w1((1.0 / det) * (AC.getY() * AP.getX() - AC.getX() * AP.getY()));
				 double w2((1.0 / det) * (-AB.getY() * AP.getX() + AB.getX() * AP.getY()));



				 if (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1.000000001)
				 {
					 return true;
				 }

				 return false;

			 }



			 return false;
		 }


		 bool IsInside(const Vector& a, const Vector& v0, const Vector& v1, const Vector& v2)
		 {
			 Vector AB{ v1.m_x - v0.m_x,v1.m_y - v0.m_y };
			 Vector AC{ v2.m_x - v0.m_x,v2.m_y - v0.m_y };

			 Vector AP{ a.m_x - v0.m_x,a.m_y - v0.m_y };

			 int det((int)(AB.m_x * AC.m_y - AC.m_x * AB.m_y));

			 if (det == 0)
			 {
				 std::cout << "No triangle but collinear points\n";
				 return false;
			 }

			 double w1((1.0 / det) * (AC.m_y * AP.m_x - AC.m_x * AP.m_y));
			 double w2((1.0 / det) * (-AB.m_y * AP.m_x + AB.m_x * AP.m_y));

			 //std::cout << "w1 = " << w1 << " , w2 = " << w2 << "\n";

			 if (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1.000000001)
			 {
				 return true;
			 }

			 return false;
		 }

		 template <typename S>
		 std::ostream& operator<<(std::ostream& out, const std::vector<S>& vector)
		 {
			 // Printing all the elements
			 // using <<
			 for (auto element : vector) {
				 out << element << " ";
			 }
			 return out;
		 }

		 void earclippingDisp(const PolyGon& pol)
		 {
			 CImg<unsigned char> image(width, height, 1, 3, 0);
			 image.draw_line(0, center_y, width, center_y, white);
			 image.draw_line(center_x, 0, center_x, height, white);
			 dispPol(pol, image, green);

			 //If its already a traingle
			 if (pol.size() <= 3) {
				 image.mirror('y');
				 image.display();
				 return;
			 }

			 std::vector<Vector> vertex_triag{};
			 MakeEqual(vertex_triag, pol);

			 std::cout << "\nDisplaying the remaining vertices at each iteration\n " << vertex_triag << "\n";
			 
			 for (int i = 0; i < vertex_triag.size(); ++i)
			 {

				 Vector vs1 = vertex_triag[(i - 1 + vertex_triag.size()) % vertex_triag.size()] - vertex_triag[i];
				 Vector vs2 = vertex_triag[(i + 1) % vertex_triag.size()] - vertex_triag[i];

				 // Test to check if the angle is grater than 180
				 if (cross(vs2, vs1) < 0) { continue; }

				 std::vector<Vector> ver_tr{ vertex_triag[i],vs1 + vertex_triag[i],vs2 + vertex_triag[i] };

				 PolyGon ear{ ver_tr };

				 bool inside = false;

				 for (int j = i + 2; j <= vertex_triag.size() - 2 + i; ++j)
				 {
					 Vector v_test{ vertex_triag[j % vertex_triag.size()] };
					 if (IsInside(v_test, ear)) {
						 inside = true;
						 break;
					 }
				 }
				 // Test to check if there is a vertex inside the ear
				 if (inside) { continue; }

				 dispPol(ear, image, green);
				 //Now we begin from the first vertex after the update
				 vertex_triag.erase(vertex_triag.begin() + i);
				 i = -1;
				 std::cout << vertex_triag << "\n";

				 if (vertex_triag.size() == 3)
				 {
					 //dispPol(PolyGon{ vertex_triag }, image, green);
					 break;
				 }

			 }
			 std::cout << "\n\n\n";

			 image.mirror('y');

			 image.display();
		 }

		 void convexHullDisp(std::vector<Vector> points)
		 {
			 CImg<unsigned char> bg(width, height, 1, 3, 0);
			 bg.draw_line(0, center_y, width, center_y, white);
			 bg.draw_line(center_x, 0, center_x, height, white);
			 CImg<unsigned char> image(width, height, 1, 3, 0);
			 image.draw_line(0, center_y, width, center_y, white);
			 image.draw_line(center_x, 0, center_x, height, white);


			 std::vector<Vector> convexHull{};

			 for (int i = 0; i < points.size(); ++i)
			 {
				 dispVecPoint(points[i], bg, red);
				 dispVecPoint(points[i], image, red);
			 }
			 bg.mirror('y');
			 bg.display();

			 //Find the point that is more to the left
			 Vector leftpoint{ leftPoint(points) };

			 convexHull.push_back(leftpoint);

			 Vector initialVector{ leftpoint.getX(),leftpoint.getY() - 10 };

			 Vector nextVertex{ width,height };

			 Vector zero{ 0.0,0.0 };

			 while (true)
			 {
				 double minAngle{ pi };
				 //Finding the vector of the vertex with the minimum angle with the previous
				 for (int i = 0; i < points.size(); ++i) {

					 if (std::count(convexHull.begin(), convexHull.end(), points[i]))
					 {
						 if (points[i] != convexHull[0]) continue;
					 }
					 if ((points[i] - convexHull[convexHull.size() - 1]) == zero) continue;
					 double angleVec{ angle(initialVector, points[i] - convexHull[convexHull.size() - 1]) };
					 if (angleVec < minAngle)
					 {
						 minAngle = angleVec;
						 nextVertex = points[i];
					 };
				 }
				 if (nextVertex == convexHull[0]) break;
				 convexHull.push_back(nextVertex);
				 initialVector = convexHull[convexHull.size() - 1] - convexHull[convexHull.size() - 2];
			 }

			 PolyGon convHull{ convexHull };
			 dispPol(convHull, image, green);

			 std::cout << "\nThe points of the convec hull are\n" << convexHull << "\n\n";


			 image.mirror('y');
			 image.display();


		 }

		 bool collisionDetection(const  PolyGon& Pol1, const PolyGon& Pol2)
		 {
			 bool collision{ true };

			 for (int i = 0; i < (Pol1.size() + Pol2.size()); ++i)
			 {
				 std::vector<Vector> projectionsPol1;
				 std::vector<Vector> projectionsPol2;
				 Segment s0{ Vector{0,0},Vector{0,0} };
				 if (i < Pol1.size()) s0 = Pol1.getSeg(i);
				 else  s0 = Pol2.getSeg(i - Pol1.size());

				 for (int j = 0; j < Pol1.size(); ++j)
				 {
					 projectionsPol1.push_back(proj(Pol1.getVec(j), perpendicular(s0)));
				 }

				 for (int j = 0; j < Pol2.size(); ++j)
				 {
					 projectionsPol2.push_back(proj(Pol2.getVec(j), perpendicular(s0)));
				 }

				 int Pol1Xmin{ (int)leftPoint(projectionsPol1).getX() };
				 int Pol1Xmax{ (int)rightPoint(projectionsPol1).getX() };

				 int Pol2Xmin{ (int)leftPoint(projectionsPol2).getX() };
				 int Pol2Xmax{ (int)rightPoint(projectionsPol2).getX() };

				 if (Pol1Xmax < Pol2Xmin || Pol2Xmax < Pol1Xmin)
				 {
					 collision = false;
					 break;
				 }
			 }
			 return collision;
		 }

		 bool collisionDetection(std::vector<Vector>& pol1, const PolyGon& Pol2)
		 {
			 bool collision{ true };

			 //Now the SAT algorithm begins

			 for (int i = 0; i < (pol1.size() + Pol2.size()); ++i)
			 {
				 std::vector<Vector> projectionsPol1;
				 std::vector<Vector> projectionsPol2;
				 Segment s0{ Vector{0,0},Vector{0,0} };
				 if (i < pol1.size()) s0 = Segment{ pol1[i],pol1[(i + 1) % pol1.size()] };
				 else  s0 = Pol2.getSeg(i - pol1.size());
				 //We make lists of the projections of the points on the perpendicular of each segment
				 for (int j = 0; j < pol1.size(); ++j)
				 {
					 projectionsPol1.push_back(proj(pol1[j], perpendicular(s0)));
				 }

				 for (int j = 0; j < Pol2.size(); ++j)
				 {
					 projectionsPol2.push_back(proj(Pol2.getVec(j), perpendicular(s0)));
				 }

				 double Pol1Xmin{ leftPoint(projectionsPol1).getX() };
				 double Pol1Xmax{ rightPoint(projectionsPol1).getX() };

				 double Pol2Xmin{ leftPoint(projectionsPol2).getX() };
				 double Pol2Xmax{ rightPoint(projectionsPol2).getX() };

				 // If the projection axis is vertical

				 if (abs(Pol1Xmin - Pol1Xmax) < 0.000001)
				 {
					 double Pol1Ymin{ upperPoint(projectionsPol1).getY() };
					 double Pol1Ymax{ downPoint(projectionsPol1).getY() };

					 double Pol2Ymin{ upperPoint(projectionsPol2).getY() };
					 double Pol2Ymax{ downPoint(projectionsPol2).getY() };


					 if (Pol1Ymax < Pol2Ymin || Pol2Ymax < Pol1Ymin)
					 {
						 collision = false;
						 break;
					 }

				 }



				 if (Pol1Xmax < Pol2Xmin || Pol2Xmax < Pol1Xmin)
				 {
					 collision = false;
					 break;
				 }
			 }
			 return collision;
		 }

		 void SATdisp(std::vector<Vector> pol1, std::vector<Vector> pol2)
		 {
			 CImg<unsigned char> bg(width, height, 1, 3, 0);
			 CImg<unsigned char> image(width, height, 1, 3, 0);

			 bg.draw_line(0, center_y, width, center_y, white);
			 bg.draw_line(center_x, 0, center_x, height, white);
			 PolyGon Pol1{ pol1 };
			 PolyGon Pol2{ pol2 };

			 image = bg;
			 CImgDisplay dsp(width, height, "LiveDetection", 0);
			 dsp.display(bg);
			 int k = 0;
			 while (true)
			 {
				 //Inserting the coordinates of cursor
				 int xm = dsp.mouse_x();
				 int ym = dsp.mouse_y();

				 image = bg;
				 dispPol(Pol2, image, green, center_x, center_y);

				 dispPol(Pol1, image, green, xm, ym);

				 Vector update{ xm - (width / 2.0) , (ym - (height / 2.0)) * (-1) };
				 if (k == 0) { update = Vector{ 0,0 }; k++; }

				 for (auto& elem : pol1)
				 {
					 elem = elem + update;
				 }

				 //If there is a collision change the color of polygons
				 if (collisionDetection(pol1, Pol2))
				 {
					 dispPol(Pol1, image, orange, xm, ym);
					 dispPol(Pol2, image, orange, center_x, center_y);
					 std::cout << "Collision\n";
				 }
				 else std::cout << "NOT collision\n";

				 for (auto& elem : pol1)
				 {
					 elem = elem - update;
				 }

				 dsp.display(image);

				 dsp.wait();
			 }
		 }

	


