//Question: will the unary plus operator work with enum class types?
//Hypothesis: No, because they don't have an implicit conversion to int
//Result: Hypothesis correct

#include <iostream>

int main(){
    enum class Alpha {
        A,
        B,
        C
    };

    Alpha myValue{ Alpha::B };

    std::cout << +myValue;
}
