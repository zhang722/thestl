#include "unique_ptr_test.h"
#include "complex_test.h"
#include "vector_test.h"
#include "shared_ptr_test.h"
#include "string_test.h"

int main() {
    using namespace test;
    unique_ptr_test();
    complex_test();
    vector_test();
    shared_ptr_test();
    string_test(); 
}