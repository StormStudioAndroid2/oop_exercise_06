
#ifndef D_LIST_H_
#define D_LIST_H_

#include <iostream>
#include <memory>
#include <functional>
#include <cassert>
#include <iterator>


namespace containers {

    template<class T,class Allocator = std::allocator<T>>
    struct list {
    private:
        struct node;

    public:
        list() = default;
        T End();
        T& operator[] (const size_t index);
        size_t Size();
        struct forward_iterator {
            using value_type = T;
            using reference = T &;
            using pointer = T *;
            using difference_type = ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            forward_iterator(node *ptr);

            T &operator*();

            forward_iterator &operator++();

            forward_iterator operator+(int r);

            bool operator==(const forward_iterator &o) const;

            bool operator!=(const forward_iterator &o) const;

        private:
        node *ptr_;
        friend list;

        };

        forward_iterator begin();

        forward_iterator end();

        void insert(const forward_iterator &it, const T &value);

        void erase(const forward_iterator &it);

        void popStart();
        void popEnd();

        void add(const T &value);

        T front();
        
    private:
        using allocator_type = typename Allocator::template rebind<node>::other;
        struct deleter {
            deleter(allocator_type* allocator): allocator_(allocator) {}
            void operator() (node* ptr) {
                if(ptr != nullptr){
                std::allocator_traits<allocator_type>::destroy(*allocator_, ptr);
                allocator_->deallocate(ptr, 1);
            }
        }

        private:
            allocator_type* allocator_;

        };

        using unique_ptr = std::unique_ptr<node, deleter>;
        node *end_node = nullptr;
        node *getTail(node *ptr);

        struct node {
            T value;
            unique_ptr next = {nullptr,deleter{&this->allocator_}};
            node *parent = nullptr;

            forward_iterator nextf();
            node(const T &value, unique_ptr next) : value(value), next(std::move(next)) {};

        };
        allocator_type allocator_{};
        unique_ptr root = {nullptr,deleter{&this->allocator_}};


    };


//
template<class T, class Allocator>
size_t list<T, Allocator>::Size() {
    auto it = begin();
    size_t size1 = 0;
    while(it!=0) {
        ++it;
        size1++;
    }
    return size1;
}
    template<class T, class Allocator>
    typename list<T,Allocator>::node *list<T, Allocator>::getTail(containers::list<T, Allocator>::node *ptr) {
        if ((ptr == nullptr) || (ptr->next == nullptr)) {
            return ptr;
        }
        return list<T, Allocator>::getTail(ptr->next.get());
    }


    template<class T, class Allocator>
    typename list<T, Allocator>::forward_iterator list<T, Allocator>::begin() {
        if (root == nullptr) {
            return nullptr;
        }
        forward_iterator it(root.get());
        return it;
    }

    template<class T, class Allocator>
    typename list<T, Allocator>::forward_iterator list<T, Allocator>::end() {
        return nullptr;
    }

    template<class T, class Allocator>
    void list<T, Allocator>::insert(const list<T, Allocator>::forward_iterator &it, const T &value) {
        node* newptr = this->allocator_.allocate(1);
        std::allocator_traits<allocator_type>::construct(this->allocator_,newptr,value, std::unique_ptr<node,deleter>(
        nullptr,deleter{&this->allocator_}));
        unique_ptr new_node(newptr,deleter{&this->allocator_});

        if (it != nullptr) {
            node *ptr = it.ptr_->parent;
            new_node->parent = it.ptr_->parent;
            it.ptr_->parent = new_node.get();
            if (ptr) {
                new_node->next = std::move(ptr->next);
                ptr->next = std::move(new_node);
            } else {
                new_node->next = std::move(root);
                root = std::move(new_node);
            }
        } else {
            new_node->next = nullptr;
            if(end_node==nullptr) {
                new_node->parent= nullptr;
                new_node->next= nullptr;
                list<T, Allocator>::root = std::move(new_node);
            }else{
                new_node->parent=end_node;
                new_node->next= nullptr;
                end_node->next=std::move(new_node);
            }
        }
        
        end_node = getTail(root.get());
    }
    template<class T, class Allocator>
    T list<T, Allocator>::End() {
        return end_node->value;
    }
    template<class T, class Allocator>
    void list<T, Allocator>::erase(const list<T, Allocator>::forward_iterator &it) {
        if (it.ptr_ == nullptr) {
            throw std::logic_error("erasing invalid iterator");
        }
        unique_ptr &pointer_from_parent = [&]() -> unique_ptr & {
            if (it.ptr_ == root.get()) {
                return root;
            }
            return it.ptr_->parent->next;
        }();
        pointer_from_parent = std::move(it.ptr_->next);

        end_node = getTail(root.get());
    }

//
    template<class T, class Allocator>
    typename list<T, Allocator>::forward_iterator list<T, Allocator>::node::nextf() {
        forward_iterator result(this->next.get());
        return result;
    }
template<class T, class Allocator>
T&  list<T, Allocator>::operator[] (const size_t index) {
    if (index>Size()) {
            throw std::logic_error("invalid index");

    }
    auto it = this->begin()+index;
    return *it;
}
 
    template<class T, class Allocator>
    list<T, Allocator>::forward_iterator::forward_iterator(node *ptr): ptr_{ptr} {}

    template<class T, class Allocator>
    T &list<T, Allocator>::forward_iterator::operator*() {
        return ptr_->value;
    }

    template<class T, class Allocator>
    typename list<T, Allocator>::forward_iterator &list<T, Allocator>::forward_iterator::operator++() {
        if (*this != nullptr) {
            *this = ptr_->nextf();
            return *this;
        } else {
            throw std::logic_error("invalid iterator");
        }
    }

    template<class T, class Allocator>
    typename list<T, Allocator>::forward_iterator list<T, Allocator>::forward_iterator::operator+(int r) {
        for (int i = 0; i < r; ++i) {
            ++*this;
        }
        return *this;
    }

    template<class T, class Allocator>
    bool list<T, Allocator>::forward_iterator::operator==(const forward_iterator &o) const {
        return ptr_ == o.ptr_;
    }

    template<class T, class Allocator>
    bool list<T, Allocator>::forward_iterator::operator!=(const forward_iterator &o) const {
        return ptr_ != o.ptr_;
    }

    template<class T, class Allocator>
    T list<T, Allocator>::front() {
        if (list<T, Allocator>::root == nullptr) {
            throw std::logic_error("no elements");
        }
        return list<T, Allocator>::root->value;
    }

    template<class T, class Allocator>
    void list<T, Allocator>::popStart() {
        if (list<T, Allocator>::root == nullptr) {
            throw std::logic_error("no elements");
        }
        erase(list<T, Allocator>::begin());
    }
        template<class T, class Allocator>
  void list<T, Allocator>::popEnd() {
        if (list<T, Allocator>::root == nullptr) {
            throw std::logic_error("no elements");
        }
        erase(list<T, Allocator>::getTail(list<T, Allocator>::begin()));
    }
    template<class T, class Allocator>
    void list<T, Allocator>::add(const T &value) {
        forward_iterator it(end_node);
        node* newptr = this->allocator_.allocate(1);
        std::allocator_traits<allocator_type>::construct(this->allocator_,newptr,value, std::unique_ptr<node,deleter>(
        nullptr,deleter{&this->allocator_}));
        unique_ptr new_node(newptr,deleter{&this->allocator_});
        if (it.ptr_) {
            new_node->parent = it.ptr_;
            it.ptr_->next = std::move(new_node);
        } else {
            new_node->next = nullptr;
            list<T, Allocator>::root = std::move(new_node);
        }
        list<T, Allocator>::end_node = getTail(root.get());
    }

}
#endif