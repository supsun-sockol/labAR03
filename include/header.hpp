// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <map>
#include <atomic>

template <typename T>
class SharedPtr;

class shared_ptr_control_block{
public:
    shared_ptr_control_block(){};
    ~shared_ptr_control_block(){};
private:
    std::map <int, std::atomic_uint> table;
    template <typename T>
    friend class SharedPtr;
};
shared_ptr_control_block Shared_ptr_control_block();

template <typename T>
class SharedPtr {
public:
    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();
    auto operator=(const SharedPtr& r) -> SharedPtr&;
    auto operator=(SharedPtr&& r) -> SharedPtr&;

    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;

    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t;
private:
    T* ptr;
};

#endif // INCLUDE_HEADER_HPP_
