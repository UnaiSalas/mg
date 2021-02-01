#include <cassert>
#include <cstdio>
#include <cstdlib>
#include "line.h"
#include "constants.h"
#include "tools.h"

Line::Line() : m_O(Vector3::ZERO), m_d(Vector3::UNIT_Y) {}
Line::Line(const Vector3 & o, const Vector3 & d) : m_O(o), m_d(d) {}
Line::Line(const Line & line) : m_O(line.m_O), m_d(line.m_d) {}

Line & Line::operator=(const Line & line) {
	if (&line != this) {
		m_O = line.m_O;
		m_d = line.m_d;
	}
	return *this;
}

// @@ TODO: Set line to pass through two points A and B
//
// Note: Check than A and B are not too close!

void Line::setFromAtoB(const Vector3 & A, const Vector3 & B) {
	Vector3 v;
	m_O = A;
	float epsilon =10e-6;
	Vector3 C=B-A;
	if(C.length()<epsilon){
		v=B-A;
		m_d=v.normalize();
	}else{
		m_d=Vector3(0 ,0 ,0 );
		printf("Estas usando el mismo punto dos veces para hacer una recta");
	}
}

// @@ TODO: Give the point corresponding to parameter u

Vector3 Line::at(float u) const {
	return m_O +u*m_d;
}

// @@ TODO: Calculate the parameter 'u0' of the line point nearest to P
//
// u0 = m_d*(P-m_o) / m_d*m_d , where * == dot product

float Line::paramDistance(const Vector3 & P) const {
	float dv = m_d.dot(P-m_O);
	float db = m_d.dot(m_d);
	float res = dv/db;
	return res;
}

// @@ TODO: Calculate the minimum distance 'dist' from line to P
//
// dist = ||P - (m_o + u0*m_d)||
// Where u0 = paramDistance(P)

float Line::distance(const Vector3 & P) const {
	float u0= paramDistance(P);
	Vector3 dist;
	dist=P-(m_O + u0*m_d);
	float res = dist.length();

	return res;
}

void Line::print() const {
	printf("O:");
	m_O.print();
	printf(" d:");
	m_d.print();
	printf("\n");
}
