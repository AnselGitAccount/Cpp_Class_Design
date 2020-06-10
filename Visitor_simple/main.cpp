/* This is the simplest implementation of visitor pattern.
 *
 * Ansel Blumers
 */

#include <cstdio>

struct VisiteeA;
struct VisiteeB;

struct Visitor {
public:
    void visit(VisiteeA& vtee) {std::puts("Visiting A.");}
    void visit(VisiteeB& vtee) {std::puts("Visiting B.");}
};

struct VisiteeBase {
    virtual ~VisiteeBase() {};
};

struct VisiteeA : public VisiteeBase {
    void accept(Visitor& vtor) {
        vtor.visit(*this);
    }
};

struct VisiteeB : public VisiteeBase {
    void accept(Visitor& vtor) {
        vtor.visit(*this);
    }
};

/* main */
int main (int argc, char** argv) {
    Visitor myVisitor;
    VisiteeA myVisiteeA;
    VisiteeB myVisiteeB;
    myVisiteeA.accept(myVisitor);
    myVisiteeB.accept(myVisitor);

    return 0;
}