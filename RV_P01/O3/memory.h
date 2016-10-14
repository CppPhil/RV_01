#ifndef O3LIB_MEMORY_H
#define O3LIB_MEMORY_H
#include "common.h"
#include "nullptr.h"
#include "except.h"
#include "noncopyable.h"
#include <new>
#include <memory>
#include <cstddef>

namespace o3 {
    namespace mem_free {
        //! frees memory allocated with plain new
        class simple_deleter {
        public:
    
            //! frees memory by calling delete on the pointer passed in
            template <typename Ty>
            static void free(Ty *p) O3_NOEXCEPT {
                delete p;
            }
        };
        
        //! frees memory allocated with new[]
        class array_deleter {
        public:
            
            //! frees memory by calling delete[] on the pointer passed in
            template <typename Ty>
            static void free(Ty *p) O3_NOEXCEPT {
                delete[] p;
            }
        };
    } // END of namespace mem_free
    
    //! http://www.boost.org/doc/libs/1_62_0/libs/smart_ptr/scoped_ptr.htm
    template <typename Ty>
    class scoped_ptr {
    public:
        typedef scoped_ptr this_type;
        typedef Ty element_type;
        typedef mem_free::simple_deleter deleter_type;
        
        explicit scoped_ptr(element_type *p = O3_NULLPTR)
            : p_(p) { }
        
        ~scoped_ptr() {
            deleter_type::free(p_);
            p_ = O3_NULLPTR;
        }
        
        void reset(element_type *p = O3_NULLPTR) {
            if (p != p_) {
                deleter_type::free(p_);
            }
            
            p_ = p;
        }
        
        element_type &operator*() const {
            if (p_ == O3_NULLPTR) {
                throw nullpointer_exception("attempted to dereference a nullpointer in o3::scoped_ptr::operator*");
            }
            return *p_;
        }
        
        element_type *operator->() const {
            if (p_ == O3_NULLPTR) {
                throw nullpointer_exception("attempted to derefenece a nullpointer in o3::scoped_ptr::operator->");
            }
            return p_;
        }
        
        element_type *get() const O3_NOEXCEPT {
            return p_;
        }
        
        //! gives up ownership of the pointer and returns it.
        element_type *release() O3_NOEXCEPT {
            element_type *p = p_;
            p_ = O3_NULLPTR;
            return p;
        }
        
        operator void *() const O3_NOEXCEPT {
            return p_;
        }
        
        void swap(this_type &other) O3_NOEXCEPT {
            element_type *t = other.p_;
            other.p_ = p_;
            p_ = t;
        }
        
        friend bool operator==(this_type const &ptr, nullptr_t const &) O3_NOEXCEPT {
            return ptr.get() == O3_NULLPTR;
        }
        
        friend bool operator==(nullptr_t const &, this_type const &ptr) O3_NOEXCEPT {
            return ptr.get() == O3_NULLPTR;
        }
        
        friend bool operator!=(this_type const &ptr, nullptr_t const &) O3_NOEXCEPT {
            return ptr.get() != O3_NULLPTR;
        }
        
        friend bool operator!=(nullptr_t const &, this_type const &ptr) O3_NOEXCEPT {
            return ptr.get() != O3_NULLPTR;
        }
        
        friend bool operator==(this_type const &arg1, this_type const &arg2) O3_NOEXCEPT {
            return arg1.get() == arg2.get();
        }
        
        friend bool operator!=(this_type const &arg1, this_type const &arg2) O3_NOEXCEPT {
            return !(arg1 == arg2);
        }
        
    private:
        element_type *p_;
        
        O3_DECLARE_NONCOPYABLE(scoped_ptr);
    }; // END of class scoped_ptr
    
    template <typename Ty>
    O3_FORCE_INLINE void swap(scoped_ptr<Ty> &arg1, scoped_ptr<Ty> &arg2) {
        arg1.swap(arg2);
    }
    
    //! http://www.boost.org/doc/libs/1_61_0/libs/smart_ptr/scoped_array.htm
    template <typename Ty>
    class scoped_array {
    public:
        typedef scoped_array this_type;
        typedef Ty element_type;
        typedef mem_free::array_deleter deleter_type;
    
        explicit scoped_array(element_type *p = O3_NULLPTR)
                : p_(p) { }
    
        ~scoped_array() {
            deleter_type::free(p_);
            p_ = O3_NULLPTR;
        }
    
        void reset(element_type *p = O3_NULLPTR) {
            if (p != p_) {
                deleter_type::free(p_);
            }
        
            p_ = p;
        }
    
        element_type &operator*() const {
            if (p_ == O3_NULLPTR) {
                throw nullpointer_exception("attempted to dereference a nullpointer in o3::scoped_array::operator*");
            }
            return *p_;
        }
    
        element_type *operator->() const {
            if (p_ == O3_NULLPTR) {
                throw nullpointer_exception("attempted to derefenece a nullpointer in o3::scoped_array::operator->");
            }
            return p_;
        }
    
        element_type *get() const O3_NOEXCEPT {
            return p_;
        }
        
        element_type &operator[](std::size_t pos) const {
            return p_[pos];
        }
    
        //! gives up ownership of the pointer and returns it.
        element_type *release() O3_NOEXCEPT {
            element_type *p = p_;
            p_ = O3_NULLPTR;
            return p;
        }
    
        operator void *() const O3_NOEXCEPT {
            return p_;
        }
    
        void swap(this_type &other) O3_NOEXCEPT {
            element_type *t = other.p_;
            other.p_ = p_;
            p_ = t;
        }
    
        friend bool operator==(this_type const &ptr, nullptr_t const &) O3_NOEXCEPT {
            return ptr.get() == O3_NULLPTR;
        }
    
        friend bool operator==(nullptr_t const &, this_type const &ptr) O3_NOEXCEPT {
            return ptr.get() == O3_NULLPTR;
        }
    
        friend bool operator!=(this_type const &ptr, nullptr_t const &) O3_NOEXCEPT {
            return ptr.get() != O3_NULLPTR;
        }
    
        friend bool operator!=(nullptr_t const &, this_type const &ptr) O3_NOEXCEPT {
            return ptr.get() != O3_NULLPTR;
        }
    
        friend bool operator==(this_type const &arg1, this_type const &arg2) O3_NOEXCEPT {
            return arg1.get() == arg2.get();
        }
    
        friend bool operator!=(this_type const &arg1, this_type const &arg2) O3_NOEXCEPT {
            return !(arg1 == arg2);
        }

    private:
        element_type *p_;
    
        O3_DECLARE_NONCOPYABLE(scoped_array);
    }; // END of class scoped_array

    template <typename Ty>
    O3_FORCE_INLINE void swap(scoped_array<Ty> &arg1, scoped_array<Ty> &arg2) {
        arg1.swap(arg2);
    }
        
    template <typename Ty>
    struct auto_ptr_ref {
        explicit auto_ptr_ref(Ty *p)
            : ref_(p) { }
        Ty *ref_;
    };
    
    //! http://en.cppreference.com/w/cpp/memory/auto_ptr
    template <typename Ty>
    class auto_ptr {
    public:
        typedef auto_ptr this_type;
        typedef Ty element_type;
        
        explicit auto_ptr(element_type *ptr = O3_NULLPTR) O3_NOEXCEPT
            : p_(ptr) { }
        
        auto_ptr(this_type &other) O3_NOEXCEPT
            : p_(other.release()) { }
        
        auto_ptr(auto_ptr_ref<element_type> other) O3_NOEXCEPT {
            element_type *ptr = other.ref_;
            other.ref_ = O3_NULLPTR;
            p_ = ptr;
        }
        
        template <typename Other>
        operator auto_ptr<Other>() O3_NOEXCEPT {
            return auto_ptr<Other>(*this);
        }
                
        template <typename Other>
        operator auto_ptr_ref<Other>() O3_NOEXCEPT {
            Other *cvtPtr = p_;
            auto_ptr_ref<Other> ans(cvtPtr);
            p_ = O3_NULLPTR;
            return ans;
        }
        
        template <typename Other>
        this_type &operator=(auto_ptr<Other> &other) O3_NOEXCEPT {
            reset(other.release());
            return *this;
        }
        
        template <typename Other>
        auto_ptr(auto_ptr<Other> &other) O3_NOEXCEPT
            : p_(other.release()) { }
        
        this_type &operator=(this_type &other) O3_NOEXCEPT {
            reset(other.release());
            return *this;
        }
        
        this_type &operator=(auto_ptr_ref<element_type> other) O3_NOEXCEPT {
            element_type *ptr = other.ref_;
            other.ref_ = O3_NULLPTR;
            reset(ptr);
            return *this;
        }
        
        ~auto_ptr() {
            delete p_;
        }
        
        element_type &operator*() const {
            if (p_ == O3_NULLPTR) {
                throw nullpointer_exception("attempted to dereference a nullpointer in o3::auto_ptr::operator*");
            }
            return *get();
        }
        
        element_type *operator->() const {
            if (p_ == O3_NULLPTR) {
                throw nullpointer_exception("attempted to dereference a nullpointer in o3::auto_ptr::operator->");
            }
            return get();
        }
        
        element_type *get() const O3_NOEXCEPT {
            return p_;
        }
        
        element_type *release() O3_NOEXCEPT {
            element_type *t = p_;
            p_ = O3_NULLPTR;
            return t;
        }
        
        void reset(element_type *ptr = O3_NULLPTR) {
            if (ptr != p_) {
                delete p_;
            }
            p_ = ptr;
        }
                
    private:
        element_type *p_;
    }; // END of class auto_ptr
    
} // END of namespace o3

#endif // O3LIB_MEMORY_H
