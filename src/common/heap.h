//
// Created by lxy on 18-4-7.
//

#ifndef MEEPO_HEAP_H
#define MEEPO_HEAP_H

#include <algorithm>
#include <vector>
#include <functional>

namespace meepo
{

namespace common
{

template <typename T>
class Heap
{
public:
    enum HeapType
    {
        MaxHeap,
        MinHeap
    };

    using CompareFuncType = std::function<bool(const T&, const T&)>;

public:
    Heap(HeapType type, int heap_size)
        : type_(type), arr_(heap_size)
    {
        if (type_ == MaxHeap)
            comp_func_ = std::less<T>();
        else
            comp_func_ = std::greater<T>();
        init_heap();
    }

    Heap(HeapType type, int heap_size, const CompareFuncType& comp_func)
        : type_(type), arr_(heap_size), comp_func_(comp_func)
    {
        init_heap();
    }

    void push_heap(const T& val)
    {
        arr_.push_back(val);
        std::push_heap(arr_.begin(), arr_.end(), comp_func_);
    }

    T pop_heap()
    {
        std::pop_heap(arr_.begin(), arr_.end(), comp_func_);
        const T& val = arr_.back();
        arr_.pop_back();
        return val;
    }

private:
    void init_heap()
    {
        std::make_heap(arr_.begin(), arr_.end(), comp_func_);
    }

private:
    HeapType type_;
    CompareFuncType comp_func_;
    std::vector<T> arr_;
};

}

}

#endif //MEEPO_HEAP_H
