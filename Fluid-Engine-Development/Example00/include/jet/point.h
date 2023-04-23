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
        // N ά�ȱ������0
        static_assert(
            N > 0, "Size of static-sized point should be greater than zero.");
        // T�����ͱ���Ϊ��ֵ����
        static_assert(
            std::is_arithmetic<T>::value,
            "Point only can be instantiated with arithmetic types");

        // Ĭ�Ϲ��캯��
        Point();

        // �ɱ�εĹ��캯��
        template <typename... Params>
        explicit Point(Params... params);

        // ��ʼ���б��캯��
        template <typename U>
        explicit Point(const std::initializer_list<U>& lst);

        // �������캯��
        Point(const Point& other);

        // ʹ��Setʵ�����б�
        template <typename U>
        void set(const std::initializer_list<U>& lst);

        // Set ����
        void set(const Point& other);

        // ������ֵ
        template <typename U>
        Point& operator=(const std::initializer_list<U>& lst);

        // Set������ֵ
        Point& operator=(const Point& other);

        // []����
        const T& operator[](size_t i) const;

        // []��������
        T& operator[](size_t);

    private:
        // ����ΪT������ΪN
        std::array<T, N> _elements;

        // ��iλ���������͵�v�Ĳ���������
        template <typename... Params>
        void setAt(size_t i, T v, Params... params);

        // ��iλ����������v�ĵ�������
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

