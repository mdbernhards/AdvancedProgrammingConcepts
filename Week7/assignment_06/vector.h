#include <iostream>

namespace sax {

  namespace detail {

    template <typename T>
    struct vector_iterator {

      using value_type = T;
      using reference = T&;
      using pointer = T*;
      using difference_type = std::ptrdiff_t;
      using iterator_category = std::random_access_iterator_tag;
      using iterator_concept = std::random_access_iterator_tag;

      vector_iterator() = delete;
      vector_iterator(T* ptr): ptr_{ptr} {}

      vector_iterator(const vector_iterator<T>& other) = default;
      vector_iterator<T>& operator=(const vector_iterator<T>& other) = default;

      vector_iterator<T>& operator++() noexcept {
        ++ptr_;
        return *this;
      }

      vector_iterator<T> operator++(int) noexcept {
        auto tmp{*this};
        ++ptr_;
        return tmp;
      }

      vector_iterator<T>& operator--() noexcept {
        --ptr_;
        return *this;
      }

      vector_iterator<T> operator--(int) noexcept {
        auto tmp{*this};
        --ptr_;
        return tmp;
      }

      vector_iterator<T>& operator+=(difference_type n) noexcept {
        ptr_ += n;
        return *this;
      }

      vector_iterator<T>& operator-=(difference_type n) noexcept {
        ptr_ -= n;
        return *this;
      }

      vector_iterator<T> operator+(difference_type n) const noexcept {
        auto tmp{*this};
        tmp += n;
        return tmp;
      }

      vector_iterator<T> operator-(difference_type n) const noexcept {
        auto tmp{*this};
        tmp -= n;
        return tmp;
      }

      difference_type operator-(const vector_iterator<T>& other) const noexcept {
        return ptr_ - other.ptr_;
      }

      reference operator*() const noexcept {
        return *ptr_;
      }

      pointer operator->() const noexcept {
        return ptr_;
      }

      auto operator<=>(const vector_iterator<T>& other) const noexcept = default;

      T* ptr_{};
    };

  } // namespace detail

  template <typename T>
  struct vector {

    using iterator = detail::vector_iterator<T>;
    using const_iterator = detail::vector_iterator<const T>;

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;


    vector(std::size_t cap):
      begin_{static_cast<T*>( operator new(sizeof(T) * cap))},
      end_{begin_},
      last_{begin_ + cap} 
    {}

    vector():
      vector{kInitCap}
    {}

    ~vector() noexcept 
    {
      for (size_t i = 0; i < size(); i++)
      {
        (begin_ + i)->~T();
      }

      operator delete(begin_);
    }

    void clear() noexcept 
    {
      for (size_t i = 0; i < size(); i++)
      {
        (begin_ + i)->~T();
      }

      end_ = begin_;
    }

    vector(const vector<T>& other):
      vector{other.capacity()}
    {
      for (size_t i = 0; i < other.size(); i++)
      {
        new (begin_ + i) T{other.begin_[i]};
      }

      end_ = begin_ + other.size();
    }

    vector(vector<T>&& other) noexcept:
      vector{}
    {
      swap(other);
    }

    vector<T>& operator=(const vector<T>& other)
    {
      if (this != &other) 
      {
        if (other.size() > capacity())
        {
          auto tmpBegin = static_cast<T*>( operator new(other.capacity() * sizeof(T)));

          clear();
          operator delete(begin_);

          begin_ = tmpBegin;
          last_ = tmpBegin + other.capacity();
        }

        for (size_t i = 0; i < other.size(); i++) 
        {
          new (begin_ + i) T(other.begin_[i]);
        }

        end_ = begin_ + other.size();
      }

      return *this;
    }

    vector<T>& operator=(vector<T>&& other) noexcept {
      if (this != &other) {
        swap(other);
        other.clear();
      }
      return *this;
    }

    void swap(vector<T>& other) noexcept {
      std::swap(begin_, other.begin_);
      std::swap(end_, other.end_);
      std::swap(last_, other.last_);
    }

    void push_back(const T& value)
    {
      if (end_ == last_)
      {
        reserve(capacity() * 2);
      }

      new(end_) T{value};
      end_++;
    }

    void push_back(T&& value)
    {
      if (end_ == last_) 
      {
        reserve(capacity() * 2);
      }

      new(end_) T(std::forward<T>(value));
      end_++;
    }
    
    void pop_back()
    {
      end_->~T();
      --end_;
    }

    T& operator[](std::size_t index) noexcept {
      return *(begin_ + index);
    }

    const T& operator[](std::size_t index) const noexcept {
      return begin_[index];
    }

    T& at(std::size_t index){
      if (index >= size()) {
        throw std::out_of_range{"index out of range"};
      }
      return begin_[index];
    }

    const T& at(std::size_t index) const{
      if (index >= size()) {
        throw std::out_of_range{"index out of range"};
      }
      return begin_[index];
    }

    void reserve(std::size_t new_cap)
    {
      if (new_cap > capacity()) 
      {
        auto tmpBegin = static_cast<T*>( operator new(new_cap * sizeof(T)));

        auto tmpEnd = tmpBegin;
        for (size_t i = 0; i < size(); i++)
        {
          new(tmpEnd) T(std::move(*(begin_ + i)));
          tmpEnd++;
          (begin_ + i)->~T();
        }
        
        operator delete(begin_);

        begin_ = tmpBegin;
        end_ = tmpEnd;
        last_ = tmpBegin + new_cap;
      }
    }

    iterator begin() noexcept {
      return iterator{begin_};
    }

    iterator end() noexcept {
      return iterator{end_};
    }

    const_iterator begin() const noexcept {
      return const_iterator{begin_};
    }

    const_iterator end() const noexcept {
      return const_iterator{end_};
    }

    std::size_t size() const noexcept {
      return end_ - begin_;
    }

    std::size_t capacity() const noexcept {
      return last_ - begin_;
    }

    bool empty() const noexcept {
      return begin_ == end_;
    }

    iterator insert(iterator pos, const T& value) 
    {
      return insert(pos, T(value));
    }

    iterator insert(iterator pos, T&& value) 
    {
      if (end_ >= last_) 
      {
        reserve(capacity() * 2);
      }

      for (auto target = end_; target != pos; target--) 
      {
        new (target) T(std::move(*(target - 1)));
        (target - 1)->~T();
      }

      auto temp = pos - begin_;
      new (begin_ + temp) T(std::forward<T>(value));

      end_++;
      return pos;
    }

    iterator erase(iterator pos) 
    {
      return erase(pos, pos + 1);
    }

    iterator erase(const_iterator pos) 
    {
      return erase(const_cast<iterator>(pos), const_cast<iterator>(pos + 1));
    }

    iterator erase(iterator first, iterator last) 
    {
      if (first == last)
      {
        return first;
      }

      for (auto target = first; target != last; target++) 
      {
        target->~T();
      }

      auto elementsErased = last - first;
      for (auto i = 0; (last + i) != end_; i++) 
      {
        auto temp = first + i - begin_;
        new (begin_ + temp) T(std::move(*(last + i)));
        (last + i)->~T();
      }

      end_ -= elementsErased;
      return first;
    }

    iterator erase(const_iterator first, const_iterator last) 
    {
      return erase(const_cast<iterator>(first), const_cast<iterator>(last));
    }
    
  private:
    T* begin_{};
    T* end_{};
    T* last_{};
    static const std::size_t kInitCap{1};
  };

} // namespace sax
