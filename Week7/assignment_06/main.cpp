#include <iostream>
#include <cassert>
#include "vector.h"

int main(){
    sax::vector<int> v1{};
    v1.push_back(1);
    v1.push_back(2);

    sax::vector<int> v2{};

    v2 = v1;

    for (auto& element: v2){
    std::cout << element << '\n';
    }

    auto iter_ = v1.begin();

    auto end_ = v1.end();
    for(; iter_ != end_; ++iter_){
        auto& element = *iter_;
        std::cout << element << '\n';
    }

    for (auto i{0u}; i < v2.size(); ++i){
        std::cout << "By size: " << v2[i] << '\n';
    }

    sax::vector<int> v3{10};
    assert(v3.capacity() == 10);

    sax::vector<int> v4;
    v4.push_back(5);
    v4.push_back(22);
    assert(v4.size() == 2);
    assert(v4[0] == 5);
    assert(v4[1] == 22);

    sax::vector<int> v5{v4};
    assert(v5.size() == v4.size());
    assert(v5[0] == 5);
    assert(v5[1] == 22);

    sax::vector<int> v6;
    v6 = v5;
    assert(v6.size() == v5.size());
    assert(v6[0] == 5);
    assert(v6[1] == 22);

    sax::vector<int> v7;
    v7.reserve(10);
    assert(v7.capacity() >= 10);
    assert(v7.size() == 0);

    v7.insert(v7.begin(), 100);
    v7.insert(v7.end(), 200);
    assert(v7.size() == 2);
    assert(v7[0] == 100);
    assert(v7[1] == 200);

    v7.erase(v7.begin());
    assert(v7.size() == 1);
    assert(v7[0] == 200);

    v7.erase(v7.begin(), v7.end());
    assert(v7.size() == 0);

    v7.push_back(300);
    v7.push_back(400);
    v7.pop_back();
    assert(v7.size() == 1);
    assert(v7[0] == 300);

    v7.clear();
    assert(v7.size() == 0);
    assert(v7.empty());

    return 0;
}

