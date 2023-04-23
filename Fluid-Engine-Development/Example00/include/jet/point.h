#pragma once
#include "macros.h"
#include "point2.h"
#include "math_utils.h"
#include <type_traits>
#include <algorithm>
#include <cassert>
#include <array>

namespace jet {
    template <typename T, size_t N>
    class Point final {
    public:
        // N 维度必须大于0
        static_assert(
            N > 0, "Size of static-sized point should be greater than zero.");
        // T的类型必须为数值类型
        static_assert(
            std::is_arithmetic<T>::value,
            "Point only can be instantiated with arithmetic types");

        // 默认构造函数
        Point();

        // 可变参的构造函数
        template <typename... Params>
        explicit Point(Params... params);

        // 初始化列表构造函数
        template <typename U>
        explicit Point(const std::initializer_list<U>& lst);

        // 拷贝构造函数
        Point(const Point& other);

        // 使用Set实例化列表
        template <typename U>
        void set(const std::initializer_list<U>& lst);

        // Set 构造
        void set(const Point& other);

        // 拷贝赋值
        template <typename U>
        Point& operator=(const std::initializer_list<U>& lst);

        // Set拷贝赋值
        Point& operator=(const Point& other);

        // []重载
        const T& operator[](size_t i) const;

        // []返回引用
        T& operator[](size_t);

    private:
        // 类型为T，长度为N
        std::array<T, N> _elements;

        // 在i位置设置类型的v的不定长参数
        template <typename... Params>
        void setAt(size_t i, T v, Params... params);

        // 在i位置设置类型v的单个参数
        void setAt(size_t i, T v);
    };


    template <typename T, size_t N>
    Point<T, N>::Point() {
        for (auto& elem : _elements) {
            elem = static_cast<T>(0);
        }
    }
    // 
    template <typename T, size_t N>
    template <typename... Params>
    Point<T, N>::Point(Params... params) {
        static_assert(sizeof...(params) == N, "Invalid number of parameters.");

        setAt(0, params...);
    }

    template <typename T, size_t N>
    template <typename U>
    Point<T, N>::Point(const std::initializer_list<U>& lst) {
        JET_ASSERT(lst.size() >= N);

        size_t i = 0;
        for (const auto& inputElem : lst) {
            _elements[i] = static_cast<T>(inputElem);
            ++i;
        }
    }

    template <typename T, size_t N>
    Point<T, N>::Point(const Point& other) :
        _elements(other._elements) {
    }

    template <typename T, size_t N>
    template <typename U>
    void Point<T, N>::set(const std::initializer_list<U>& lst) {
        assert(lst.size() >= N);

        size_t i = 0;
        for (const auto& inputElem : lst) {
            _elements[i] = static_cast<T>(inputElem);
            ++i;
        }
    }

    template <typename T, size_t N>
    void Point<T, N>::set(const Point& other) {
        _elements = other._elements;
    }

    template <typename T, size_t N>
    template <typename U>
    Point<T, N>& Point<T, N>::operator=(const std::initializer_list<U>& lst) {
        set(lst);
        return *this;
    }

    template <typename T, size_t N>
    Point<T, N>& Point<T, N>::operator=(const Point& other) {
        set(other);
        return *this;
    }

    template <typename T, size_t N>
    const T& Point<T, N>::operator[](size_t i) const {
        return _elements[i];
    }

    template <typename T, size_t N>
    T& Point<T, N>::operator[](size_t i) {
        return _elements[i];
    }

    template <typename T, size_t N>
    template <typename... Params>
    void Point<T, N>::setAt(size_t i, T v, Params... params) {
        _elements[i] = v;

        setAt(i + 1, params...);
    }

    template <typename T, size_t N>
    void Point<T, N>::setAt(size_t i, T v) {
        _elements[i] = v;
    }
}

