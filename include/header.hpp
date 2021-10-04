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
    //std::map <T*, std::atomic_uint> table;
    std::map <T*, int> table;
    friend class SharedPtr<T>;
};

template <typename T>
shared_ptr_control_block<T> Shared_ptr_control_block;

template <typename T>
class SharedPtr {
public:
    SharedPtr(){
        this->tptr = nullptr;
    }
    explicit SharedPtr(T* Ptr){
        auto it = Shared_ptr_control_block<T>.table.find(Ptr);
        if (it == Shared_ptr_control_block<T>.table.end()){
            Shared_ptr_control_block<T>.table[Ptr] = 1;
        } else{
            it->second++;
        }
        this->tptr = Ptr;
    }
    SharedPtr(const SharedPtr& r){
        Shared_ptr_control_block<T>.table[r.tptr]++;
        this->tptr = r.tptr;
    }
    SharedPtr(SharedPtr&& r){
        this->tptr = nullptr;
        std::swap(this->tptr, r.tptr);
    }
    ~SharedPtr(){
        if (this->tptr != nullptr){
            Shared_ptr_control_block<T>.table[this->tptr]--;
            if (Shared_ptr_control_block<T>.table[this->tptr] == 0){
                delete[] this->tptr;
            }
        }
    }
    auto operator=(const SharedPtr& r) -> SharedPtr&{
        if (r != *this){
            Shared_ptr_control_block<T>.table[r.tptr]++;
            this->tptr = r.tptr;
        }
        return *this;
    }
    auto operator=(SharedPtr&& r) -> SharedPtr&{
        if (r != *this){
            this->tptr = nullptr;
            Shared_ptr_control_block<T>.table[this->tptr]--;
            std::swap(this->tptr, r.tptr);
        }
        return *this;
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const{return this->tptr != nullptr;}
    auto operator*() const -> T&{
            return *this->tptr;
    }
    auto operator->() const -> T*{
        return this->tptr;
    }

    auto get() -> T*{
        return this->tptr;
    }
    void reset(){
        this->tptr = nullptr;
        Shared_ptr_control_block<T>.table[this->tptr]--;
    }
    void reset(T* ptr){
        Shared_ptr_control_block<T>.table[this->tptr]--;
        this->tptr = ptr;
        Shared_ptr_control_block<T>.table[this->tptr]++;
    }
    void swap(SharedPtr& r){
        std::swap(this->tptr, r.tptr);
    }
    // возвращает количество объектов SharedPtr,
    //которые ссылаются на тот же управляемый объект
    auto use_count() const{
        return Shared_ptr_control_block<T>.table[this->tptr];
    }

private:
    T* tptr;
};

#endif // INCLUDE_HEADER_HPP_
