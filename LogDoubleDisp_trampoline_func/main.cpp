#include<cstdio>
#include<map>
#include<iostream>
#include "shape.h"
#include "typeinfo.h"

/* Logarithmic Double Dispatcher with trampoline function
 *
 * Improved version from 'Logarithmic Double Dispatcher'.
 * 1. HatchRectanglePoly now accepts concrete types.
 * 2. As a result, symmetry can be easily implemented.
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


/* FnDispatcher is tuned for dispatch to functions only.
 * It uses BasicDispatcher as its back end.
 */
template <class BaseLhs,
		class BaseRhs = BaseLhs,
		typename ResultType = void>
class FnDispatcher {
private:
	BasicDispatcher<BaseLhs, BaseRhs, ResultType> backEnd_;

public:
	template <class ConcreteLhs,
			class ConcreteRhs,
			ResultType (*callback)(ConcreteLhs&, ConcreteRhs&),
			bool symmetric=false>
	void Add() {
		struct Local {
			static ResultType Trampoline(BaseLhs& lhs, BaseRhs& rhs) {
				return callback(
						dynamic_cast<ConcreteLhs&>(lhs),
						dynamic_cast<ConcreteRhs&>(rhs));
			}
			// symmetry support
			static ResultType TrampolineR(BaseRhs& rhs, BaseLhs& lhs) {
				return Trampoline(lhs,rhs);
			}
		};

		backEnd_.template Add<ConcreteLhs, ConcreteRhs>(&Local::Trampoline);
		
		if (symmetric) {
			// symmetry support
			backEnd_.template Add<ConcreteRhs, ConcreteLhs>(&Local::TrampolineR);
		}
	}

	ResultType Go(BaseLhs& lhs, BaseRhs& rhs) {
		return backEnd_.Go(lhs,rhs);
	}
};


/* Hatches the intersection between a rectangle and a polygon */
void HatchRectanglePoly(Rectangle& lhs, Polygon& rhs) {
	printf("Hatching Rectangle and Polygon\n");
}


/* main */
int main (int argc, char** argv) {
	FnDispatcher<Shape> Mydisp;
	Rectangle MyRect;
	Polygon MyPoly;
	Mydisp.Add<Rectangle, Polygon, HatchRectanglePoly>();
	Mydisp.Go(MyRect,MyPoly);
}
