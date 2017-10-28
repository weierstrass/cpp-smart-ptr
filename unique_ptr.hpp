#ifndef _AB_UNIQUE_PTR_
#define _AB_UNIQUE_PTR_

namespace ab {

    template<typename T>
    class unique_ptr {
    public:
        unique_ptr(T* ptr) : ptr(ptr) {}
        unique_ptr() : ptr(0) {}

        ~unique_ptr() {
            delete ptr;
        }

        explicit operator bool() const {
            return ptr != 0;
        }

        T* get() const {
            return ptr;
        }

        T& operator*() const {
            assert(ptr);
            return *ptr;
        }

    private:
        T* ptr;
             
    };

}


#endif /* _AB_UNIQUE_PTR_ */
