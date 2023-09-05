#ifndef CLASSES_H
#define CLASSES_H

#include"CImg.h"
using namespace cimg_library;


extern double pi;

extern const  int width ;
extern const  int height ;
extern const unsigned int center_x ;
extern const unsigned int center_y ;

extern const unsigned char black[] ;  // RGB colors
extern const unsigned char red[];
extern const unsigned char white[] ;
extern const unsigned char green[] ;
extern const unsigned char blue[] ;
extern const unsigned char orange[] ;


class PolyGon;
class Segment;

class Vector
{
public:
	Vector(double x  , double y ) ;


	Vector operator+(const Vector b);

	Vector operator-(const Vector b);

	double getX() const ;
	double getY() const ;

	friend class Segment;
	friend class PolyGon;

	friend std::ostream& operator<<(std::ostream& out, Vector a);

	friend bool IsInside(const Vector& a, const Vector& v0, const Vector& v1, const Vector& v2);


	friend double operator*(const Vector& a, const  Vector& b);

	friend Vector operator*(const Vector& a, double k);

	friend Vector operator*(double k, const Vector& a);

	bool operator == (const Vector& a);

	bool operator != (const Vector& a);

	friend double cross(const Vector& a, const Vector& b);

	friend Vector perpendicular(const Vector& a);


	double magnitude();

	friend Vector& leftPoint(std::vector<Vector>& points);

	friend void dispVecPoint(const Vector& a, CImg<unsigned char>& image, const unsigned char color[3]);
	friend void dispVecPoint(const Vector& a, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym);
	friend void dispVecArrow(const Vector& a, CImg<unsigned char>& image, const unsigned char color[3]);
	friend void dispVecArrow(const Vector& a, const Vector& start, CImg<unsigned char>& image, const unsigned char color[3]);



	friend bool IsInside(const Vector& a, const PolyGon& pol);

	Vector normal();

	void mirrorY();

private:
	double m_x{};
	double m_y{};


};

class Segment
{
public:
	Segment(Vector a, Vector b);
	Vector const vec();



	friend void dispSegm(const Segment& ab, CImg<unsigned char>& image, const unsigned char color[3]);
	friend void dispSegm(const Segment& ab, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym);

private:
	Vector m_a{0,0};
	Vector m_b{0,0};


};


class PolyGon
{
public:
	PolyGon(std::vector<Vector> vertex);

	PolyGon(const Vector& v0, const Vector& v1, const Vector& v2);
	friend void dispPol(const PolyGon& pol, CImg<unsigned char>& image, const unsigned char color[3]);

	friend void dispPol(const PolyGon& pol, CImg<unsigned char>& image, const unsigned char color[3], int xm, int ym);

	friend bool IsInside(const Vector& a, const PolyGon& pol);

	friend void MakeEqual(std::vector<Vector>& vertex_triag, const PolyGon& pol);

	int size() const;

	Vector getVec(int i) const;

	Segment getSeg(int i) const;

	void update(int xm, int ym);


	friend PolyGon operator+(const PolyGon& pol, const Vector b);


private:
	std::vector<Vector> m_vertex;
	std::vector<Segment> m_segment;

};

double cross(const Vector& a, const Vector& b);
double angle(Vector a, Vector b);
Vector proj(const Vector& a, const Vector& b);
Vector& rightPoint(std::vector<Vector>& points);
Vector& downPoint(std::vector<Vector>& points);
Vector& upperPoint(std::vector<Vector>& points);
Vector proj(const Vector& a, Segment& seg);
Vector perpendicular(Segment& seg);
bool collisionDetection(const  PolyGon& Pol1, const PolyGon& Pol2);
bool collisionDetection(std::vector<Vector>& pol1, const PolyGon& Pol2);


void earclippingDisp(const PolyGon& pol);
void convexHullDisp(std::vector<Vector> points);
void SATdisp(std::vector<Vector> pol1, std::vector<Vector> pol2);

#endif // !CLASSES_H

