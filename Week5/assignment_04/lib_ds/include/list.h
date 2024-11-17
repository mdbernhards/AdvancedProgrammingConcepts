#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H

/**
 * @file list.h
 * @brief Doubly-linked list implementation
 */

#include <type_traits>
#include <iterator>
#include <initializer_list>
#include <memory>

namespace saxion {

    //forward declaration of the class list
    template<typename T>
    class list;

    /**
     * Implementation details for the saxion::list
     */
    namespace detail {
        // more forward declarations
        template<typename T, typename NodeT>
        struct list_iterator;

        template<typename T, typename NodeT>
        struct const_list_iterator;

        /**
         * @brief Base class for list nodes
         *
         * This class contains only the pointers to the next and previous nodes. The previous pointers is non-owning. The next pointer is owning.
         */
        struct list_node_base {
            list_node_base* prev_{};
            std::unique_ptr<list_node_base> next_{};

            list_node_base() noexcept:
                prev_{},
                next_{}
            {}

            list_node_base(list_node_base* prev, list_node_base* next) noexcept :
                prev_{prev},
                next_{next}
            {}

            [[nodiscard]]
            list_node_base* next() const noexcept {
                return next_.get();
            }


            [[nodiscard]]
            list_node_base* prev() const noexcept {
                return prev_;
            }

            virtual ~list_node_base() noexcept = default;
        };

        /**
         * @brief Sentinel node
         * 
         * Node type used as sentinel.
         */
        struct list_node_sentinel : public list_node_base {

            /// size of the list
            std::size_t size_{};

            /**
             * @brief Construct a new list node sentinel object
             * 
             * @note An empty sentinel owns itself.
             * 
             */
            list_node_sentinel():
                list_node_base(),
                size_{}
            {
                prev_ = this;
                next_.reset(this);
            }

            /**
             * @brief Destroy the list node sentinel object
             * 
             * @note If the sentinel is empty it release itself to prevent recursive destruction.
             * 
             */
            virtual ~list_node_sentinel() noexcept {

                if (next() == this){
                    next_.release();
                }
            }

            /**
             * @brief Swaps this node with another sentinel
             * 
             * @param other another sentinel
             */
            void swap(list_node_sentinel& other) noexcept {
                std::swap(prev_, other.prev_);
                std::swap(next_, other.next_);
                std::swap(size_, other.size_);
            }

            /**
             * @brief Increment the size of the list
             * 
             * @return std::size_t 
             */
            std::size_t inc_size() noexcept {
                return ++size_;
            }

            /**
             * @brief Decrement the size of the list
             * 
             * @return std::size_t 
             */

            std::size_t dec_size() noexcept {
                return --size_;
            }

            [[nodiscard]]
            std::size_t size() const noexcept {
                return size_;
            }

            [[nodiscard]]
            list_node_base* node_base() noexcept {
                return this;
            }

        };

        /**
         * @brief Node that contains a value
         * 
         * @tparam T type of the value
         */
        template<typename T>
        struct list_node : public list_node_base {
            template<typename T_> friend
            class ::saxion::list;

            T value_;

            list_node() = delete;

            void swap(list_node& other) noexcept {
                std::swap(prev_, other.prev_);
                std::swap(next_, other.next_);
                std::swap(value_, other.value_);
            }

            list_node(T&& v, list_node_base* prev, list_node_base* next) :
                list_node_base{ prev, next },
                value_{ std::move(v) }
            {}

            list_node(T const& v, list_node_base* prev, list_node_base* next) :
                list_node_base{ prev, next },
                value_{v}
            {}

            [[nodiscard]]
            T& value() {
                return value_;
            }

            [[nodiscard]]
            T const& value() const {
                return value_;
            }

            virtual ~list_node() noexcept = default;
        };

        template<typename T, typename NodeT = list_node_base>
        struct list_iterator 
        {
            template<typename> friend 
            class ::saxion::list;

            using node_t = NodeT;
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            NodeT* current_;

            explicit list_iterator(NodeT* node) : current_(node) {}

            NodeT* node() const 
            { 
                return current_; 
            }

            list_iterator& operator++() 
            {
                current_ = current_->next();

                return *this;
            }

            list_iterator operator++(int) 
            {
                list_iterator temp = *this;
                ++(*this);

                return temp;
            }

            list_iterator& operator--() 
            {
                current_ = current_->prev();

                return *this;
            }

            list_iterator operator--(int) 
            {
                list_iterator temp = *this;
                --(*this);

                return temp;
            }

            reference operator*() const 
            {
                return static_cast<detail::list_node<T>*>(current_)->value();
            }

            pointer operator->() const 
            {
                return &static_cast<detail::list_node<T>*>(current_)->value();
            }

            bool operator==(const list_iterator& second) const 
            {
                return current_ == second.current_;
            }

            bool operator!=(const list_iterator& second) const 
            {
                return !(*this == second);
            }
        };

        template<typename T, typename NodeT = list_node_base>
        struct const_list_iterator 
        {
            // list is a friend of the iterator
            template<typename> friend class ::saxion::list;

            using node_t = NodeT;
            using value_type = T;
            using reference = const T&;
            using pointer = const T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            const NodeT* current_;

            explicit const_list_iterator(const NodeT* node) : current_(node) {}

            const NodeT* node() const 
            { 
                return current_; 
            }

            const_list_iterator& operator++() 
            {
                current_ = current_->next();

                return *this;
            }

            const_list_iterator operator++(int) 
            {
                const_list_iterator temp = *this;
                ++(*this);

                return temp;
            }

            const_list_iterator& operator--() 
            {
                current_ = current_->prev();

                return *this;
            }

            const_list_iterator operator--(int) 
            {
                const_list_iterator temp = *this;
                --(*this);

                return temp;
            }

            reference operator*() const 
            {
                return static_cast<const detail::list_node<T>*>(current_)->value();
            }

            pointer operator->() const 
            {
                return &static_cast<const detail::list_node<T>*>(current_)->value();
            }

            bool operator==(const const_list_iterator& second) const 
            {
                return current_ == second.current_;
            }

            bool operator!=(const const_list_iterator& second) const 
            {
                return !(*this == second);
            }
        };

        template <typename T, typename NodeT>
        [[nodiscard]]
        inline bool operator==(const list_iterator<T, NodeT>& lhs, const const_list_iterator<T, NodeT>& rhs) 
        {
            return lhs.current_ == rhs.current_;
        }

        template <typename T, typename NodeT>
        [[nodiscard]]
        inline bool operator!=(const list_iterator<T, NodeT>& lhs, const const_list_iterator<T, NodeT>& rhs) 
        {
            return !(lhs == rhs);
        }
    }

    /**
     * @brief Doubly-linked list
     * 
     * @tparam T type of the elements
     */
    template<typename T>
    class list {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = T const&;
        using pointer = T*;
        using const_pointer = T const*;
        using size_type = std::size_t;

    private:

        using node_t = detail::list_node<T>;
        using sentinel_node_t = detail::list_node_sentinel;

        sentinel_node_t node_{};

        [[nodiscard]]
        detail::list_node_base* tail() const noexcept{
            return node_.prev();
        }

        [[nodiscard]]
        detail::list_node_base* head() const noexcept{
            return node_.next();
        }

    public:

        using iterator = detail::list_iterator<T, detail::list_node_base>;
        using const_iterator = detail::const_list_iterator<T, detail::list_node_base>;

        /**
         * @brief Construct a new, empty list object
         * 
         */
        list() :
                node_{}
                 { }

        /**
         * @brief Construct a new list object from an initializer list
         * 
         * @tparam U type of the elements in the initializer list
         * @param init_list initializer list
         */
        template<class U>
        list(std::initializer_list<U> init_list) :
                list{} {
            for (auto item : init_list) {
                push_back(std::move(item));
            }
        }

        /**
         * @brief Copy constructor
         * 
         * @param list to create a copy of
         */
        list(const list& other) :
                list{} {
            for (auto othernext_{other.head()};
                 othernext_->next() != other.head();
                 othernext_ = othernext_->next()) {

                push_back(static_cast<node_t*>(othernext_)->value());
            }
        }

        /**
         * @brief Copy assignment operator
         * 
         * @param other list to copy
         * @return reference to self
         */
        list& operator=(const list& other) {
            if (this != &other) {
                clear();

                for (auto othernext_{other.head()};
                     othernext_->next() != other.head();
                     othernext_ = othernext_->next()) {

                    push_back(static_cast<node_t*>(othernext_)->value());
                }
            }
            return *this;
        }

        /**
         * @brief Move constructor
         * 
         * @param other list to move from 
         */
        list(list&& other) noexcept :
                list{} {
            swap(other);
        }

        /**
         * @brief Move assignment operator
         * 
         * @param other list to move from
         * @return return reference to self
         */
        list& operator=(list&& other) noexcept {
            if (this != &other) {
                clear();
                swap(other);
            }
            return *this;
        }

        /**
         * @brief Construct a new list object from a range
         * 
         * @tparam _Iter type of the iterator
         * @param begin begin of the range
         * @param end end of the range
         */
        template<typename _Iter, typename = std::enable_if_t<
                std::is_same_v<
                        typename std::iterator_traits<_Iter>::value_type,
                        value_type >>>
        list(_Iter begin, _Iter end):
                list() {
            for (; begin != end; ++begin) {
                push_back(*begin);
            }
        }

        /**
         * @brief Returns an iterator to the first element of the list
         * 
         * @return iterator 
         */
        [[nodiscard]]
        iterator begin() noexcept {
            return iterator(node_.next());
        }

        /**
         * @brief Returns an iterator to the end of the list
         * 
         * @return iterator 
         */
        [[nodiscard]]
        iterator end() noexcept {
            return iterator(&node_);
        }

        /**
         * @brief Returns a const iterator to the first element of the list
         * 
         * @return const_iterator 
         */
        [[nodiscard]]
        const_iterator begin() const noexcept {
            return const_iterator(node_.next());
        }

        /**
         * @brief Returns a const iterator to the end of the list
         * 
         * @return const_iterator 
         */
        [[nodiscard]]
        const_iterator end() const noexcept {
            return const_iterator(&node_);
        }

        /**
         * @brief Returns a const iterator to the first element of the list
         * 
         * @return const_iterator 
         */
        [[nodiscard]]
        const_iterator cbegin() const noexcept {
            return const_iterator(node_.next());
        }

        /**
         * @brief Returns a const iterator to the end of the list
         * 
         * @return const_iterator 
         */
        [[nodiscard]]
        const_iterator cend() const noexcept {
            return const_iterator(&node_);
        }

        void swap(list& other) noexcept {
            std::swap(head()->prev_, other.head()->prev_);
            node_.swap(other.node_);
            std::swap(tail()->next_, other.tail()->next_);
        }


        /**
         * @brief Returns a reference to the first element of the list
         * 
         * @return reference 
         */
        [[nodiscard]]
        reference front() {
            return static_cast<node_t*>(head())->value();
        }

        /**
         * @brief Returns a const reference to the first element of the list
         * 
         * @return const_reference 
         */
        [[nodiscard]]
        const_reference front() const {
            return static_cast<node_t*>(head())->value();
        }

        /**
         * @brief Returns a reference to the last element of the list
         * 
         * @return reference 
         */
        [[nodiscard]]
        reference back() {
            return static_cast<node_t*>(tail())->value();
        }

        /**
         * @brief Returns a const reference to the last element of the list
         * 
         * @return const_reference 
         */
        [[nodiscard]]
        const_reference back() const {
            return static_cast<node_t*>(tail())->value();
        }

        /**
         * @brief Returns a reference to the element at the given index
         * 
         * @param index 
         * @return reference to the element
         * @note This function is slow. Do not use it.
         */
        [[nodiscard]]
        reference operator[](size_type index) {
            auto current = head();
            while (index--) { current = current->next(); }
            return static_cast<node_t*>(current)->value();
        }

        /**
         * @brief Returns a const reference to the element at the given index
         * 
         * @param index 
         * @return const reference to the element
         * @note This function is slow. Do not use it.
         */
        [[nodiscard]]
        const_reference operator[](size_type index) const {
            auto current = head();
            while (index--) { current = current->next(); }
            return static_cast<node_t*>(current)->value();
        }

        /**
         * @brief Returns a reference to the element at the given index
         * 
         * @param index 
         * @return reference to the element
         * @throw std::length_error if index is out of bounds
         * @note This function is slow. Do not use it.
         */
        [[nodiscard]]
        reference at(size_type index) {
            if (index < node_.size()) {
                auto current = head();
                while (index--) { current = current->next(); }
                return static_cast<node_t*>(current)->value();
            }
            throw std::length_error("index out of bounds");
        }

        /**
         * @brief Returns a const reference to the element at the given index
         * 
         * @param index 
         * @return const reference to the element
         * @throw std::length_error if index is out of bounds
         * @note This function is slow. Do not use it.
         */
        [[nodiscard]]
        const_reference at(size_type index) const {
            if (index < node_.size()) {
                auto current = head();
                while (index--) { current = current->next(); }
                return static_cast<node_t*>(current)->value();
            }
            throw std::length_error("index out of bounds");
        }

        /**
         * @brief Removes the first element of the list
         * 
         */
        void pop_front() noexcept {
            if (node_.prev_ != std::addressof(node_)) {
                node_.next_ = std::move(node_.next_->next_);
                head()->prev_ = &node_;
                node_.dec_size();
            }
        }

        /**
         * @brief Removes the last element of the list
         * 
         */
        void pop_back() noexcept {
            if (node_.prev_ != std::addressof(node_)) {
                node_.prev_ = node_.prev()->prev();
                tail()->next_ = std::move(tail()->next()->next_);
                node_.dec_size();
            }
        }

        /**
         * @brief Returns true if the list is empty
         * 
         * @return true if list is empty
         * @return false if list is not empty
         */
        [[nodiscard]]
        bool empty() const {
            return node_.size() == 0;
        }

        /**
         * @brief Returns the size of the list
         * 
         * @return size_type 
         */
        [[nodiscard]]
        size_type size() const {
            return node_.size();
        }

        /**
         * @brief Clears the list
         * 
         * @note This function might be slow. Do not use it;).
         */
        void clear() noexcept {
            if (node_.prev_ != std::addressof(node_)) {
                // unlink the nodes iteratively
                while (head() != &node_) {
                    node_.next_ = std::move(node_.next_->next_);
                    node_.next_->prev_ = &node_;
                    node_.dec_size();
                }
            }
        }

        /**
         * @brief Destroy the list object
         * 
         */
        ~list() noexcept {
          tail()->next_.release();
          auto iter = tail();

          while(iter != &node_){
              iter->next_.reset();
              iter = iter->prev();
          }
        }

        /**
         * @brief Appends an element to the end of the list
         * 
         * @param rvalue reference to the object to append
         * @return iterator to the appended element
         */
        iterator push_back(T&& value) {
            tail()->next_ = std::make_unique<node_t>(std::move(value), tail(), tail()->next_.release());
            node_.prev_ = node_.prev_->next();
            node_.inc_size();
            return iterator{tail()};
        }

        /**
         * @brief Appends an element to the end of the list
         * 
         * @param lvalue reference to the value to append
         * @return iterator to the appended element
         */
        iterator push_back(const_reference value) {
            tail()->next_ = std::make_unique<node_t>(value, tail(), tail()->next_.release());
            node_.prev_ = node_.prev_->next();
            node_.inc_size();
            return iterator{tail()};
        }

        /**
         * @brief Emplaces an element to the end of the list by constructing it in-place
         * 
         * @tparam Args types of the arguments
         * @param args arguments passed to the constructor of the element
         * @return iterator to the appended element
         */
        template<typename... Args>
        iterator emplace_back(Args&& ... args) {
            tail()->next_ = std::make_unique<node_t>(T(std::forward<Args>(args)...), tail(), tail()->next_.release());
            node_.prev_ = node_.prev_->next();
            node_.inc_size();
            return iterator{tail()};
        }

        /**
         * @brief Appends an element to the front of the list
         * 
         * @param rvalue reference to the object to append
         * @return iterator to the appended element
         */
        template<typename V>
        iterator push_front(V&& value) {
            node_.next_ = std::make_unique<node_t>(std::forward<V>(value), &node_, node_.next_.release());
            head()->next_->prev_ = node_.next_.get();
            node_.inc_size();
            return iterator{head()};
        }

        /**
         * @brief Erases an element from the list
         * 
         * @param pos iterator to the element to erase
         * @return iterator to the next element after the erased one
         */
        iterator erase(iterator pos) {
            if (begin() != end()){
                auto res(pos.current_->next());
                pos.current_->next_->prev_ = pos.current_->prev_;
                pos.current_->prev_->next_ = std::move(pos.current_->next_);
                node_.dec_size();
                return iterator(res);
            }
            return iterator(pos.current_->next());
        }

        /**
         * @brief Inserts an element before the given position
         * 
         * @param pos iterator position to insert before
         * @param value an lvalue reference to the value to insert
         * @return iterator iterator to the inserted element
         */
        iterator insert(iterator pos, const_reference value) {
            // grab previous element?
            pos.current_->prev_->next_ = std::make_unique<node_t>(value, pos.current_->prev_, pos.current_->prev_->next_.release());
            pos.current_->prev_ = pos.current_->prev()->next();
            node_.inc_size();
            return iterator(pos.current_->prev());
        }

        /**
         * @brief Inserts an element before the given position
         * 
         * @param pos iterator position to insert before
         * @param value an rvalue reference to the value to insert
         * @return iterator iterator to the inserted element
         */
        iterator insert(iterator pos, T&& value) {
            // grab previous element?
            pos.current_->prev_->next_ = std::make_unique<node_t>(std::move(value), pos.current_->prev_, pos.current_->prev_->next_.release());
            pos.current_->prev_ = pos.current_->prev()->next();
            node_.inc_size();
            return iterator(pos.current_->prev());
        }

        /**
         * @brief Emplaces an element before the given position
         * 
         * @tparam Args types of the arguments
         * @param pos iterator position to insert before
         * @param args arguments passed to the constructor of the element
         * @return iterator iterator to the inserted element
         */
        template<typename... Args>
        iterator emplace(iterator pos, Args&& ... args) {
            // grab previous element?
            pos.current_->prev_->next_ = std::make_unique<node_t>(T(std::forward<Args>(args)...), pos.current_->prev_, pos.current_->prev_->next_.release());
            pos.current_->prev_ = pos.current_->prev()->next();
            node_.inc_size();
            return iterator(pos.current_->prev());
        }

    };

    /// Deduction guide for iterator arguments
    template<typename _Iter>
    list(_Iter b, _Iter e) -> list<typename std::iterator_traits<_Iter>::value_type>;

    /// Deduction guide for initializer list arguments
    template<typename _V>
    list(std::initializer_list<_V>) -> list<_V>;
}

namespace std{
    template<typename T>
    inline void swap(saxion::list<T>& x, saxion::list<T>& y) noexcept {
        x.swap(y);
    }
}


#endif