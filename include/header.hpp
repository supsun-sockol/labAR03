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
        auto it = Shared_ptr_control_block<T>.table.find(Ptr);
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
        this->ptr =nullptr;
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
    auto operator=(const SharedPtr& r) -> SharedPtr&{
        if (r != *this){
            Shared_ptr_control_block<T>.table[r.ptr]++;
            this->ptr = r.ptr;
        }
        return *this;
    }
    auto operator=(SharedPtr&& r) -> SharedPtr&{
        if (r != *this){
            this->ptr=nullptr;
            Shared_ptr_control_block<T>.table[this->ptr]--;
            std::swap(this->ptr, r.ptr);
        }
        return *this;
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const{return this->ptr != nullptr;}
    auto operator*() const -> T&{
            return *this->ptr;
    }
    auto operator->() const -> T*{
        return this->ptr;
    }

    auto get() -> T*{
        return this->ptr;
    }
    void reset(){
        this->ptr=nullptr;
        Shared_ptr_control_block<T>.table[this->ptr]--;
    }
    void reset(T* ptr){
        Shared_ptr_control_block<T>.table[this->ptr]--;
        this->ptr=ptr;
        Shared_ptr_control_block<T>.table[this->ptr]++;
    }
    void swap(SharedPtr& r){
        std::swap(this->ptr, r.ptr);
    }
    // возвращает количество объектов SharedPtr,
    //которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t{
        return Shared_ptr_control_block<T>.table[this->ptr];
    }

private:
    T* ptr;
};

#endif // INCLUDE_HEADER_HPP_
