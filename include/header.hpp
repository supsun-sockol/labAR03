// Copyright 2020 Supsun supsun-sockol@yandex.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <map>
#include <atomic>
#include <utility>

template <typename T>
class SharedPtr;

template <typename T>
class shared_ptr_control_block{
public:
    shared_ptr_control_block(){}
    ~shared_ptr_control_block(){}
private:
    std::map <T*, std::atomic_uint> table;

    friend class SharedPtr<T>;
};

template <typename T>
shared_ptr_control_block<T> Shared_ptr_control_block;

template <typename T>
class SharedPtr {
public:
    SharedPtr(){
        this->ptr = nullptr;
    }
    explicit SharedPtr(T* Ptr){
        typename std::map <T*, std::atomic_uint> :: iterator it;
        it = Shared_ptr_control_block<T>.table.find(Ptr);
        if (it == Shared_ptr_control_block<T>.table.end()){
            it->second = 1;
        } else{
            it->second++;
        }
        this->ptr = Ptr;
    }
    SharedPtr(const SharedPtr& r){
        Shared_ptr_control_block<T>.table[r.ptr]++;
        this->ptr = r.ptr;
    }
    SharedPtr(SharedPtr&& r){
        this->ptr =     nullptr;
        std::swap(this->ptr, r.ptr);
    }
    ~SharedPtr(){
        if (this->ptr != nullptr){
            Shared_ptr_control_block<T>.table[this->ptr]--;
            if (Shared_ptr_control_block<T>.table[this->ptr] == 0){
                delete[] this->ptr;
            }
        }
    }
    auto operator=(const SharedPtr& r) -> SharedPtr&;
    auto operator=(SharedPtr&& r) -> SharedPtr&;

    // проверяет, указывает ли указатель на объект
    operator bool() const{return this->ptr != nullptr;}
    auto operator*() const -> T&;
    auto operator->() const -> T*;

    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr,
    //которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t;

private:
    T* ptr;
};

#endif // INCLUDE_HEADER_HPP_
