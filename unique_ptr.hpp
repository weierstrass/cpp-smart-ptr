#ifndef _AB_UNIQUE_PTR_
#define _AB_UNIQUE_PTR_

namespace ab {

    template<typename T>
    class unique_ptr {
    public:
        explicit unique_ptr(T* ptr) : ptr(ptr) {}
        
        unique_ptr() : ptr(0) {}

        unique_ptr(unique_ptr<T>&& ptr) : ptr(ptr.get()) {
            ptr.reset();
        }

        unique_ptr(const unique_ptr<T>& ptr) = delete;

        ~unique_ptr() {
            delete ptr;
        }

        T& operator*() const {
            assert(ptr);
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        explicit operator bool() const {
            return ptr != 0;
        }

        unique_ptr<T>& operator=(const unique_ptr<T>& ptr) = delete;

        T* get() const {
            return ptr;
        }

        void reset() {
            ptr = 0;
        }

    private:
        T* ptr;
             
    };

}


#endif /* _AB_UNIQUE_PTR_ */
