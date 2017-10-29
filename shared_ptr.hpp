#ifndef _AB_SHARED_PTR_
#define _AB_SHARED_PTR_

namespace ab {

    template<typename T>
    class shared_ptr {
    public:
        shared_ptr() : ptr(0), ref_count(new int(0)) {}
        explicit shared_ptr(T* ptr) : ptr(ptr), ref_count(new int(1)) {}

        shared_ptr(const shared_ptr<T>& other) :
            ptr(other.get()), ref_count(other.ref_count) {
            (*ref_count)++;
        }

        shared_ptr<T>& operator=(const shared_ptr<T>& other) {
            if(this != &other)
            {
                // If this already owns a resource and if it is
                // the last owner, release the resource before
                // the assignment.
                if (*ref_count == 1 && ptr) {
                    delete ptr;
                }

                // Delete the currect reference count.
                delete ref_count;

                // Do the assignment
                ptr = other.ptr;
                ref_count = other.ref_count;
                ++*ref_count;     
            }
            return *this;
        }

        ~shared_ptr() {
            if (!--*ref_count) {
                delete ptr;
                delete ref_count;
            }
        }

        T* get() const {
            return ptr;
        }

        int count() const {
            assert(ref_count);
            return *ref_count;
        }

        T& operator*() const {
            assert(ptr);
            return *ptr;
        }
        

    private:
        T* ptr;
        int* ref_count;
    };
}


#endif /* _AB_SHARED_PTR_ */
