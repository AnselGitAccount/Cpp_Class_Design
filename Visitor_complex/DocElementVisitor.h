#ifndef GUARD_DOCELEMENTVISITOR_H
#define GUARD_DOCELEMENTVISITOR_H


// Forward Declaration
class DocElement;
class Paragraph;
class RasterBitmap;
class VectorGraphic;


// This class contains a list of places that it COULD visit.
class DocElementVisitor {
public:
	virtual void Visit(Paragraph&) = 0;
	virtual void Visit(RasterBitmap&) = 0;

	// This is the catch-all.
	// This will be called when Visit is not provided in DocElementVisitor
	virtual void Visit(DocElement&) = 0;

	// A seperate Visiting purpose.
	// For example, VisitGraphic deals with graphical aspect.
	virtual void VisitGraphic(VectorGraphic&) = 0;

	virtual ~DocElementVisitor() {};
};


#endif
