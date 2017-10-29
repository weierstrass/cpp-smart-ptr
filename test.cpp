#include "test.hpp"

#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

#include <iostream>

static int destruct_count(0);

struct Dummy {
    Dummy(int val) : val(val) {destruct_count = 0;}
    Dummy() : val(0) {destruct_count = 0;}
    int val;
    ~Dummy(){destruct_count++;}
};

TEST(test, unique_ptr_destruction) {
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

TEST(test, unique_ptr_get) {
    ab::unique_ptr<int> ptr(new int(5));
    EXPECT_EQ(5, *ptr.get());
}

TEST(test, unique_ptr_operator_star) {
    ab::unique_ptr<int> ptr(new int(5));
    EXPECT_EQ(5, *ptr);
}

TEST(test, unique_ptr_operator_arrow) {
    ab::unique_ptr<Dummy> ptr(new Dummy(5));
    EXPECT_EQ(5, ptr->val);
}

TEST(test, unique_ptr_move) {
    ab::unique_ptr<int> ptr(new int(5));
    ab::unique_ptr<int> ptr2(std::move(ptr));

    EXPECT_EQ(5, *ptr2);
    if (ptr) FAIL();
}

TEST(test, shared_ptr_creation) {
    ab::shared_ptr<int> ptr(new int(5));
    EXPECT_EQ(1, ptr.count());
    EXPECT_EQ(5, *ptr);
}

TEST(test, shared_ptr_destruction) {
    {
        ab::shared_ptr<Dummy> ptr2;
        {
            ab::shared_ptr<Dummy> ptr1(new Dummy);
            ab::shared_ptr<Dummy> ptr3(ptr1);
            EXPECT_EQ(2, ptr1.count());
            EXPECT_EQ(2, ptr3.count());

            ptr2 = ptr1;
            EXPECT_EQ(3, ptr1.count());
        }
        EXPECT_EQ(1, ptr2.count());
    }
    EXPECT_EQ(1, destruct_count);
}
