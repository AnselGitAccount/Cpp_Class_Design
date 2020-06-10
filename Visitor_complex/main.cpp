/*
 * This is the "plain" cyclic version of Visitor Pattern.
 *
 * Three entities at play here:
 * 1. Visitee -- concrete classes of DocElement
 * 2. Visitor -- DocElementVisitor
 * 3. List of destinations -- user commands.
 */

/*
 * Classes are strategically placed in header files
 * to avoid Cyclic Name Dependency.
 */

#include<iostream>
#include<cstdio>
#include "DocElementVisitor.h"
#include "DocElement.h"

class DocStats;


// Visitee - 1
class Paragraph : public DocElement {
public:
	void Accept(DocElementVisitor& v) {v.Visit(*this);};
	int c = 1;
};

// Visitee - 2
class RasterBitmap : public DocElement {
public:
	void Accept(DocElementVisitor& v) {v.Visit(*this);};
	int b = 1;
};

// Visitee - 3
class VectorGraphic : public DocElement {
public:
	void Accept(DocElementVisitor& v) {v.VisitGraphic(*this);}
	int d = 1;
};


// This class specifies the 'purpose' for the visits.
// This class is derived from the Visitor.
class DocStats : public DocElementVisitor {
public:
	virtual void Visit(DocElement& catchall) {}
	virtual void Visit(Paragraph& par) {
		printf("Visiting Paragraph\n");
		c = par.c;
	};
	virtual void Visit(RasterBitmap& rasbit) {
		printf("Visiting RasterBitmap\n");
		b = rasbit.b;
	};
	virtual void VisitGraphic(VectorGraphic& vecgra) {
		printf("Visiting VectorGraphic\n");
		d = vecgra.d;
	};

	// Statistics
	int b = 0;
	int c = 0;
	int d = 0;
};


/* main */
int main (int argc, char** argv) {
	DocStats statistics;
	Paragraph mypara;
	RasterBitmap myrasbit;
	VectorGraphic myvecgra;

	// Issue visiting commands.
	mypara.Accept(statistics);
	myrasbit.Accept(statistics);
	myvecgra.Accept(statistics);
}
