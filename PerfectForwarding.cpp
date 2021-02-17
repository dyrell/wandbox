// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <memory>

typedef struct L_Or_R_Value
 {
    L_Or_R_Value(double&& x) {std::cout<<"R value overload: "<<x<<"\n"; }
    L_Or_R_Value(double& x) { std::cout<<"L value overload: "<<x<<"\n"; }    
  }LOrRValue;

class FRef //Class with forward ref
 {
    private:
        LOrRValue lrV1,lrV2,lrV3;
    public:
        template<class C1, class C2, class C3>
        FRef(C1&& c1, C2&& c2, C3&& c3):lrV1{std::forward<C1>(c1)},lrV2{std::forward<C2>(c2)},lrV3{std::forward<C3>(c3)} {}
 };
    

int main()
{
    std::cout << "Time to demonstrate L or R value refs" << std::endl;
    LOrRValue rVal(3.145678);
    double lclDbl = 46626.9109209;
    LOrRValue lVal(std::move(lclDbl));
    
    FRef lclRef(rVal, lclDbl, lVal);
}

