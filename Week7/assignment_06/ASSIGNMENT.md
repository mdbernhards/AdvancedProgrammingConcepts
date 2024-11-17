# Advanced Programming Concepts, assignment 6

In this assignment you'll work on extending and fixing the functionality of the `vector` class. The overarching goal is to make `vector` well-behaved and work correctly with various item types.


As it happens, `vector` [doesn't work with many, even simple classes](https://godbolt.org/z/YjxT1cdsz). For instance, this seemingly innocent piece of code fails to compile:

```c++
class oops {
  int n_;
public:
  oops(int n): n_{n}{}
  operator int() const { return n_; }
};

int main(){
  sax::vector<oops> arr{};
}
```

## Separating memory allocation and object construction

The reason for this is somewhat obscure, but straightforward--the `oops` class has no default constructor. Because of this, neither of those line can compile:

```c++
oops why{};
oops doesnt[42];
oops* it = new oops{};
oops* compile = new oops[42]{}; // that's what vector does
```

### `vector` and memory management

The issue with `vector` is that it allocates an array of objects in its constructor (and other places) that are default-constructed:

```c++
vector(std::size_t cap):
    begin_{ new T[cap]{} }, // <- all the objects in the allocated array are 
                            // initialized by calling their default constructors
    end_{ begin_ },
    last_{ begin_ + cap }
  {}
```

This cannot work for types that are not *default-constructible*. To solve this, the constructor of `vector` must only allocate memory for storage. The construction of objects should then happen in other places, like the `push_back` function, where objects are added to `vector`.


In C, you use `malloc` and `free` to allocate and deallocate memory on the heap. It is possible to use those function in C++ but it's not a portable solution because it bypasses other language mechanisms. Instead, the `operator new` and `operator delete` are used. `operator new`, just like `malloc`, takes the number of bytes to allocate. For instance, to allocate enough storage to fit 16 `std::string` objects you can write:

```c++
auto array = operator new[]( 16 * sizeof(std::string) );
```

Notice, that `new` in its array form (`new[]`) is used to allocate memory for multiple objects. To get memory for just one object you'd:

```c++
auto one_object = operator new( sizeof(std::string) );
```

To free the memory allocated with `operator new`, use `operator delete`:

```c++
operator delete[] array;

operator delete one_object;
```

Again, the array and non-array forms are used as needed.

The return type of `operator new` is, just like for `malloc`, the type `void*`. In C++ you cannot assign a `void` pointer directly to a pointer of a different type. Consequently, a cast is needed:

```c++
std::string * array = operator new[]( 16 * sizeof(std::string) );   // ERROR, won't compile
std::string * array = static_cast<std::string*>( operator new[]( 16 * sizeof(std::string) ) );   // OK
```

Memory obtained with `operator new` is uninitialized. It is illegal and dangerous to use it as if there were objects located in it. The following snippet demonstrates it. After allocating array storage for string objects, the item at index `0` is assigned a new value:

```c++
// storage for 16 strings
std::string * array = static_cast<std::string*>( operator new[]( 16 * sizeof(std::string) ) );  

array[0] = "Danger";    // ERROR
```

Such an assignment calls the *move assignment operator* of `std::string`. This will go wrong, because there's no `std::string` object at `array[0]` yet. Such an object needs first to be created with [*placement new*](https://isocpp.org/wiki/faq/dtors#placement-new). It's a special `new` syntax that creates an object at a specified location:

```c++
new (pointer_to_location) Type_of_object_to_create{ constructor, arguments, if, any };
```

The location where an object is created with *placement new* must be a valid location with enough storage to fit the object. To create a string object at index 0 of `array`, you'll write:

```c++
// allocate storage for 16 strings
std::string * array = static_cast<std::string*>( operator new[]( 16 * sizeof(std::string) ) );  

new (&array[0]) std::string{ "This if fine to do" };
```

Going a step further 16 strings can be created in a loop:

```c++
// storage for 16 strings
std::string * array = static_cast<std::string*>( operator new[]( 16 * sizeof(std::string) ) );  

for (auto i{0}; i < 16; ++i)
  new (array + i) std::string{ "Danger?" };
  // ^^^ pointers instead of arrays, equivalent to: new (&array[i])...
```

Any object that's once created needs to be properly cleaned-up. Normally, the runtime takes care of it for objects on the stack by calling their destructors automatically when they fall out of scope. This doesn't happen for objects allocated on the heap. The programmer is responsible for the clean-up process. With the standard `new`/ `delete` pair, where `new` both allocates and initializes an object, `delete` also calls the object's destructor. This is not the case for objects created with *placement new*. Those need to be cleaned-up manually. There is no *placement delete* counterpart to *placement new*. Instead, you as a programmer need to explicitly call the object's destructor. This is done with:

```c++
pointer_to_location_where_the_object_resides->~Type_of_object_to_destroy();
```

A bit awkward but it works. To destroy a string object at the beginning of an array you can:

```c++
// storage for 16 strings
std::string * array = static_cast<std::string*>( operator new[]( 16 * sizeof(std::string) ) );

new (array) std::string{ "This is fine to do" };    // create a string at index 0

array->~basic_string<char>();
```

Don't be surprised by seeing `~basic_string<char>()` instead of `~string()`. This is the real type of what is know as `std::string`. If in doubt, you can always let the compiler figure out the correct type of an object:

```c++
template <typename T>
void destroy(T* location){
  location->~T();
}

destroy(array);  // calls the destructor on the first object of array
```

You can even have a function that destroys all the objects in an array (assuming that they were constructed):

```c++
template <typename T>
void destroy_n(T* location, std::size_t n){
  for (auto i{0u}; i < n; ++i)
    (location + i)->~T();
}
```

## Task

You have seen how memory allocation and object construction can be separated from each other:

* Uninitialized memory is allocated with `operator new` / `operator new[]`

* Objects are created in uninitialized memory with *placement new*

* Objects are destroyed by calling their destructors explicitly.

* Once there are no objects in it, memory is freed with `operator delete` / `operator delete[]`


The following snippet demonstrates how all those steps are done:

```c++
// allocate storage for 16 strings
std::string * array = static_cast<std::string*>( operator new[]( 16 * sizeof(std::string) ) );

// create 3 strings at the beginning of the array
new (array + 0) std::string{ "This is " };
new (array + 1) std::string{ "some crazy " };
new (array + 2) std::string{ "stuff!" };

// print them
for (auto i{0}; i < 3; ++i)
  std::cout << *(array + i) << '\n';

// destroy the 3 strings
for (auto i{0}; i < 3; ++i)
  (array + i)->~basic_string<char>();

// deallocate the whole array
operator delete[] array;
```


The whole cycle that consists of four steps can be simplified by using function templates:

```c++
// allocates storage for n objects
template <typename T>
T* allocate(std::size_t n=1){
    return static_cast<T*>( operator new[](sizeof(T) * n) );
}

// deallocates storage
template <typename T>
void deallocate(T* ptr){
    operator delete[](ptr);
}

// constructs an object at location with one argument passed to its constructor
template <typename T, typename Arg>
void construct(T* location, const Arg& arg){
    new (location) T{arg};
}

// destroys an object at location
template <typename T>
void destroy(T* location){
    location->~T();
}
```

The `construct` function above is not really powerful because it can only pass one argument to the object's constructor. what's worse, it is always passed by `const` reference. Compare this with the possibilities that `std::string` offers:

```c++
std::string str{"Zenon"};

std::string * array = static_cast<std::string*>( operator new[]( 16 * sizeof(std::string) ) );  // storage for 16 strings

new (array + 0) std::string{ "Alice" };
new (array + 1) std::string{ 42, '*' };
new (array + 2) std::string{ str };
new (array + 3) std::string{ std::move(str) };
```

You can always overload construct for 0, 2, 3, 4, etc. arguments that should be passed to an object's constructor.

Nevertheless, even with this shortcoming, those function can be used together to:

```c++
// allocate storage for 16 strings, need to specify template argument, it can't be deduced
std::string * array = allocate<std::string>(16);

// create 8 strings at the beginning of the array
for (auto i{0}; i < 8; ++i)
    construct(array + i, std::to_string(i) );

// print them
for (auto i{0}; i < 8; ++i)
    std::cout << *(array + i) << '\n';

// destroy the 8 strings
for (auto i{0}; i < 8; ++i)
    destroy(array + i);

// deallocate the whole array
deallocate(array);
```

## Things to do

### Memory management in `vector`

Change the implementation of `vector` to use separate memory allocation and object creation/ destruction. You'll need to refactor the following functions:


1. `push_back`, both of them. They should use *placement new* to create objects at correct locations.

2. `pop_back` must destroy the last object in the storage before manipulating the `end_` pointer.
   
2. `vector(std::size_t cap)`, this should only allocate memory for storage with `operator new`, not allocate and create objects as it does now.

3. Depending on how the *copy constructor* is implemented you may need to change it. Specifically, this function cannot use `std::copy` anymore. If it doesn't, you are most likely good. Ok, it does...

4. The *copy assignment operator* should first allocate new, uninitialized memory (if needed) and then copy objects into this storage. Pay attention that objects that have belonged to the current instance are correctly destroyed. Also, don't forget to deallocate the old storage. Just like with the *copy constructor*, you cannot easily use `std::copy` anymore in this function--it assumes that objects already exist at the destination. Finally, this function should handle cases properly when the capacity doesn't change. 

5. `vector`'s destructor should first destroy the objects in the storage and then free the memory.
   
6. `clear` must also destroy the objects currently stored in `vector` before manipulating the `end_` pointer.

7. `reserve`, this one's fun. After checking that you need to allocate new storage:
   
    * Allocate new storage with enough space for new capacity.
    * Move  all the objects from the old storage to the new one by using *placement new*
    * Destroy all the objects in the old storage
    * Deallocate the old storage
    * Adjust the pointers (`begin_`, `end_`, `last_`) as needed.

    When you refactor this function set `DEF_CAP` to 1 to catch errors early.

### Functions `insert` and `erase`

Implement functions `insert` and `erase` for `vector`. 


`insert` should be overloaded for lvalue and rvalue references:

```c++
template <typename T>
class vector {
public:

  using iterator = T*;
  using const_iterator = const T*;

  iterator insert(const_iterator pos, const T& value);
  iterator insert(const_iterator pos, T&& value);

};
```

`vector::insert` should work just like the [`std::vector`'s functions work](https://en.cppreference.com/w/cpp/container/vector/insert). It takes a position and a value. The value should be inserted before the position pointed to by the `pos` argument. `insert` returns an iterator pointing to the inserted value. You'll need to:

* possibly resize the storage to fit the extra item,
* move the existing items in the storage to fit the new item, 
* copy-assign or move-assign the new item to its place.


`erase` should have the following overloads and work just like its [`std::vector`'s counterpart](https://en.cppreference.com/w/cpp/container/vector/erase) does:

```c++
template <typename T>
class vector {
public:

  using iterator = T*;
  using const_iterator = const T*;

  iterator erase( iterator pos );
  iterator erase( const_iterator pos );
  iterator erase( iterator first, iterator last );
  iterator erase( const_iterator pos, const_iterator last );
};
```

The first two overloads erase an element at `pos`. The remaining overloads erase all the elements in the range `[first, last)` (including element `first` and excluding `last`). All overloads return an iterator the the first element following the erased item(s). You'll need to, not necessarily in this order, there are multiple ways to accomplish this task:

* destroy the erased elements,
* move the existing elements.


That's all. Good luck!