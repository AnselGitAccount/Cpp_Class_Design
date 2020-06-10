#ifndef GUARD_DOCELEMENT_H
#define GUARD_DOCELEMENT_H

// Forward Declaration
class DocElementVisitor;

class DocElement {
public:
	// This is the bouncing pure virtual function.
	virtual void Accept(DocElementVisitor&) = 0;
	virtual ~DocElement() {};
};

#endif
