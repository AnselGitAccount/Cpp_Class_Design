#include<cstdio>
#include<map>
#include<iostream>
#include "shape.h"
#include "typeinfo.h"


/* Logarithmic Double Dispatcher
 * DISADVANTAGE #1: Does not work correctly with inheritance. So child class must be registered separately.
 * DISADVANTAGE #2: HatchRectanglePoly must accept Shape, and cast to concrete types.  <--- This can be solved with a trampoline function.
 */

template <class BaseLhs,
		class BaseRhs = BaseLhs,
		typename ResultType = void,
		typename CallbackType = ResultType (*)(BaseLhs&, BaseRhs&)>
class BasicDispatcher {
	typedef std::pair<TypeInfo,TypeInfo> KeyType;
	typedef CallbackType MappedType;
	typedef std::map<KeyType, MappedType> MapType;

public:
	/* Registration
	 * KEY is a particular combination of Shapes;
	 * VALUE is a pointer to the specific functor to dispatch; */
	template <class SomeLhs, class SomeRhs>
	void Add(CallbackType fun) {
		const KeyType key(typeid(SomeLhs), typeid(SomeRhs));
		callbackMap_[key] = fun;
	};

	/* Search and Invocation */
	ResultType Go(BaseLhs& lhs, BaseRhs& rhs) {
		const KeyType key(typeid(lhs), typeid(rhs));
		auto i = callbackMap_.find(KeyType(typeid(lhs), typeid(rhs)));
		if (i == callbackMap_.end()) {
			throw std::runtime_error("Function not found");
		}

		return (i->second)(lhs, rhs);
	}

private:
	MapType callbackMap_;
};



/* Action: Hatches the intersection between a rectangle and a polygon */
void HatchRectanglePoly(Shape& lhs, Shape& rhs) {
	Rectangle& rc = dynamic_cast<Rectangle&>(lhs);
	Polygon& pl = dynamic_cast<Polygon&>(rhs);
	printf("Action: Hatching Rectangle and Polygon\n");
}


/* main */
int main (int argc, char** argv) {
	BasicDispatcher<Shape> Mydisp;
	Rectangle MyRect;
	Polygon MyPoly;
	Mydisp.Add<Rectangle,Polygon>(HatchRectanglePoly);  // Registration
	Mydisp.Go(MyRect,MyPoly);							// Search and Invocation
}
