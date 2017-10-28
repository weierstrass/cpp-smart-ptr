#include "test.hpp"

#include "unique_ptr.hpp"

#include <iostream>

static int destruct_count(0);

struct Dummy {
    int val;
    ~Dummy(){destruct_count++;}
};

TEST(test, unique_ptr_basic) {
    {
        ab::unique_ptr<Dummy> ptr(new Dummy);
    }

    EXPECT_EQ(1, destruct_count);
}

TEST(test, unique_ptr_operator_bool) {
    ab::unique_ptr<int>  ptr1;
    if(ptr1) FAIL();

    ab::unique_ptr<int> ptr2(new int);
    if (!ptr2) FAIL(); 
}

