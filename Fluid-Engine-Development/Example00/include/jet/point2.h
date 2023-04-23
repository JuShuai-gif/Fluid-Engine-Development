#pragma once
#include "point.h"
#include "macros.h"
#include "math_utils.h"

#include <algorithm>
#include <cassert>

namespace jet {
	// 二维点
    template <typename T>
    class Point<T, 2> {
    public:
        static_assert(std::is_arithmetic<T>::value,
            "Point only can be instantiated with arithmetic types");

        // X
        T x;
        // Y
        T y;

        // 默认构造函数
        constexpr Point() : x(0), y(0) {}

        // 两个参数构造函数
        constexpr Point(T x_, T y_) : x(x_), y(y_) {}

        // 利用初始化列表构造Point
        template <typename U>
        Point(const std::initializer_list<U>& lst);

        // 拷贝赋值
        constexpr Point(const Point& v) : x(v.x), y(v.y) {}

        // MARK: Basic setters

        // Set设置相同的x\y
        void set(T s);

        // 同时设置x\y
        void set(T x, T y);

        // 初始化列表
        template <typename U>
        void set(const std::initializer_list<U>& lst);

        // Set拷贝
        void set(const Point& pt);

        // Set 0
        void setZero();

        // MARK: Binary operations: new instance = this (+) v

        // + (v, v).
        Point add(T v) const;

        // + (v.x, v.y).
        Point add(const Point& v) const;

        // - (v, v).
        Point sub(T v) const;

        // - (v.x, v.y).
        Point sub(const Point& v) const;

        // * (v, v).
        Point mul(T v) const;

        // * (v.x, v.y).
        Point mul(const Point& v) const;

        // / (v, v).
        Point div(T v) const;

        // / (v.x, v.y).
        Point div(const Point& v) const;

        // MARK：右减
        // (v, v) - this.
        Point rsub(T v) const;

        // (v.x, v.y) - this.
        Point rsub(const Point& v) const;

        // (v, v) / this.
        Point rdiv(T v) const;

        // (v.x, v.y) / this.
        Point rdiv(const Point& v) const;

        // 复合 this (+)= v

        // += (v, v).
        void iadd(T v);

        // += (v.x, v.y).
        void iadd(const Point& v);

        // -= (v, v).
        void isub(T v);

        // -= (v.x, v.y).
        void isub(const Point& v);

        // *= (v, v).
        void imul(T v);

        // *= (v.x, v.y).
        void imul(const Point& v);

        // /= (v, v).
        void idiv(T v);

        // /= (v.x, v.y).
        void idiv(const Point& v);

        // MARK: 基本的获取

        // 获取某位置元素（返回常量引用）
        const T& at(size_t i) const;

        // 获取某位置元素（返回数值）
        T& at(size_t i);

        // return x + y
        T sum() const;

        //! Returns the minimum value among x and y.
        T min() const;

        //! Returns the maximum value among x and y.
        T max() const;

        //! Returns the absolute minimum value among x and y.
        T absmin() const;

        //! Returns the absolute maximum value among x and y.
        T absmax() const;

        //! Returns the index of the dominant axis.
        size_t dominantAxis() const;

        //! Returns the index of the subminant axis.
        size_t subminantAxis() const;

        //! Returns a point with different value type.
        template <typename U>
        Point<U, 2> castTo() const;

        // 判断两个点是否相等
        bool isEqual(const Point& other) const;

        // MARK: 重载

        // 利用[] 查找某个元素（返回值）
        T& operator[](size_t i);

        // 利用[] 查找某个元素（返回常量引用）
        const T& operator[](size_t i) const;

        // 设置元素 使用初始化列表
        Point& operator=(const std::initializer_list<T>& lst);

        // 设置元素 利用另外Point
        Point& operator=(const Point& v);

        // += (v, v)
        Point& operator+=(T v);

        // this += (v.x, v.y)
        Point& operator+=(const Point& v);

        // this -= (v, v)
        Point& operator-=(T v);

        // this -= (v.x, v.y)
        Point& operator-=(const Point& v);

        // this *= (v, v)
        Point& operator*=(T v);

        // this *= (v.x, v.y)
        Point& operator*=(const Point& v);

        // this /= (v, v)
        Point& operator/=(T v);

        // this /= (v.x, v.y)
        Point& operator/=(const Point& v);

        // 判断两个点是否相等
        bool operator==(const Point& v) const;

        // 判断两个点是否不相等
        bool operator!=(const Point& v) const;
    };

    // 类型别名（二维点）
    template <typename T>
    using Point2 = Point<T, 2>;

    // 正号操作
    template <typename T>
    Point<T, 2> operator+(const Point<T, 2>& a);

    // 负号操作
    template <typename T>
    Point2<T> operator-(const Point2<T>& a);

    // (a, a) + (b.x, b.y).
    template <typename T>
    Point2<T> operator+(T a, const Point2<T>& b);

    // (a.x, a.y) + (b.x, b.y).
    template <typename T>
    Point2<T> operator+(const Point2<T>& a, const Point2<T>& b);

    // (a.x, a.y) - (b, b).
    template <typename T>
    Point2<T> operator-(const Point2<T>& a, T b);

    // (a, a) - (b.x, b.y).
    template <typename T>
    Point2<T> operator-(T a, const Point2<T>& b);

    // (a.x, a.y) - (b.x, b.y).
    template <typename T>
    Point2<T> operator-(const Point2<T>& a, const Point2<T>& b);

    // (a.x, a.y) * (b, b).
    template <typename T>
    Point2<T> operator*(const Point2<T>& a, T b);

    // (a, a) * (b.x, b.y).
    template <typename T>
    Point2<T> operator*(T a, const Point2<T>& b);

    // (a.x, a.y) * (b.x, b.y).
    template <typename T>
    Point2<T> operator*(const Point2<T>& a, const Point2<T>& b);

    // (a.x, a.y) / (b, b).
    template <typename T>
    Point2<T> operator/(const Point2<T>& a, T b);

    // (a, a) / (b.x, b.y).
    template <typename T>
    Point2<T> operator/(T a, const Point2<T>& b);

    // (a.x, a.y) / (b.x, b.y).
    template <typename T>
    Point2<T> operator/(const Point2<T>& a, const Point2<T>& b);

    // 返回两个点中最小 (x,y)
    template <typename T>
    Point2<T> min(const Point2<T>& a, const Point2<T>& b);

    // 返回两个点中最大 (x,y)
    template <typename T>
    Point2<T> max(const Point2<T>& a, const Point2<T>& b);

    //! Returns element-wise clamped point.
    template <typename T>
    Point2<T> clamp(const Point2<T>& v, const Point2<T>& low,
        const Point2<T>& high);

    //! Returns element-wise ceiled point.
    template <typename T>
    Point2<T> ceil(const Point2<T>& a);

    //! Returns element-wise floored point.
    template <typename T>
    Point2<T> floor(const Point2<T>& a);
    
    //MARK: 类型别名

    //! Float-type 2D point.
    typedef Point2<float> Point2F;

    //! Double-type 2D point.
    typedef Point2<double> Point2D;

    //! Integer-type 2D point.
    typedef Point2<ssize_t> Point2I;

    //! Unsigned integer-type 2D point.
    typedef Point2<size_t> Point2UI;



    /**************************************************/
    //      imp

    // Constructors
    template <typename T>
    template <typename U>
    Point<T, 2>::Point(const std::initializer_list<U>& lst) {
        set(lst);
    }

    // Basic setters
    template <typename T>
    void Point<T, 2>::set(T s) {
        x = s;
        y = s;
    }

    template <typename T>
    void Point<T, 2>::set(T newX, T newY) {
        x = newX;
        y = newY;
    }

    template <typename T>
    template <typename U>
    void Point<T, 2>::set(const std::initializer_list<U>& lst) {
        JET_ASSERT(lst.size() >= 2);

        auto inputElem = lst.begin();
        x = static_cast<T>(*inputElem);
        y = static_cast<T>(*(++inputElem));
    }

    template <typename T>
    void Point<T, 2>::set(const Point& v) {
        x = v.x;
        y = v.y;
    }

    template <typename T>
    void Point<T, 2>::setZero() {
        x = y = 0;
    }

    // Binary operators: new instance = this (+) v
    template <typename T>
    Point<T, 2> Point<T, 2>::add(T v) const {
        return Point(x + v, y + v);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::add(const Point& v) const {
        return Point(x + v.x, y + v.y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::sub(T v) const {
        return Point(x - v, y - v);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::sub(const Point& v) const {
        return Point(x - v.x, y - v.y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::mul(T v) const {
        return Point(x * v, y * v);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::mul(const Point& v) const {
        return Point(x * v.x, y * v.y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::div(T v) const {
        return Point(x / v, y / v);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::div(const Point& v) const {
        return Point(x / v.x, y / v.y);
    }

    // Binary operators: new instance = v (+) this
    template <typename T>
    Point<T, 2> Point<T, 2>::rsub(T v) const {
        return Point(v - x, v - y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rsub(const Point& v) const {
        return Point(v.x - x, v.y - y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rdiv(T v) const {
        return Point(v / x, v / y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rdiv(const Point& v) const {
        return Point(v.x / x, v.y / y);
    }

    // Augmented operators: this (+)= v
    template <typename T>
    void Point<T, 2>::iadd(T v) {
        x += v;
        y += v;
    }

    template <typename T>
    void Point<T, 2>::iadd(const Point& v) {
        x += v.x;
        y += v.y;
    }

    template <typename T>
    void Point<T, 2>::isub(T v) {
        x -= v;
        y -= v;
    }

    template <typename T>
    void Point<T, 2>::isub(const Point& v) {
        x -= v.x;
        y -= v.y;
    }

    template <typename T>
    void Point<T, 2>::imul(T v) {
        x *= v;
        y *= v;
    }

    template <typename T>
    void Point<T, 2>::imul(const Point& v) {
        x *= v.x;
        y *= v.y;
    }

    template <typename T>
    void Point<T, 2>::idiv(T v) {
        x /= v;
        y /= v;
    }

    template <typename T>
    void Point<T, 2>::idiv(const Point& v) {
        x /= v.x;
        y /= v.y;
    }

    // Basic getters
    template <typename T>
    const T& Point<T, 2>::at(size_t i) const {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    T& Point<T, 2>::at(size_t i) {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    T Point<T, 2>::sum() const {
        return x + y;
    }

    template <typename T>
    T Point<T, 2>::min() const {
        return std::min(x, y);
    }

    template <typename T>
    T Point<T, 2>::max() const {
        return std::max(x, y);
    }

    template <typename T>
    T Point<T, 2>::absmin() const {
        return jet::absmin(x, y);
    }

    template <typename T>
    T Point<T, 2>::absmax() const {
        return jet::absmax(x, y);
    }

    template <typename T>
    size_t Point<T, 2>::dominantAxis() const {
        return (std::fabs(x) > std::fabs(y)) ? 0 : 1;
    }

    template <typename T>
    size_t Point<T, 2>::subminantAxis() const {
        return (std::fabs(x) < std::fabs(y)) ? 0 : 1;
    }

    template <typename T>
    template <typename U>
    Point2<U> Point<T, 2>::castTo() const {
        return Point2<U>(static_cast<U>(x), static_cast<U>(y));
    }

    template <typename T>
    bool Point<T, 2>::isEqual(const Point& other) const {
        return (x == other.x && y == other.y);
    }

    // Operators
    template <typename T>
    T& Point<T, 2>::operator[](size_t i) {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    const T& Point<T, 2>::operator[](size_t i) const {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator=(const std::initializer_list<T>& lst) {
        set(lst);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator=(const Point& v) {
        set(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator+=(T v) {
        iadd(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator+=(const Point& v) {
        iadd(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator-=(T v) {
        isub(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator-=(const Point& v) {
        isub(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator*=(T v) {
        imul(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator*=(const Point& v) {
        imul(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator/=(T v) {
        idiv(v);
        return (*this);
    }

    template <typename T>
    Point<T, 2>& Point<T, 2>::operator/=(const Point& v) {
        idiv(v);
        return (*this);
    }

    template <typename T>
    bool Point<T, 2>::operator==(const Point& v) const {
        return isEqual(v);
    }

    template <typename T>
    bool Point<T, 2>::operator!=(const Point& v) const {
        return !isEqual(v);
    }

    // Math functions
    template <typename T>
    Point<T, 2> operator+(const Point<T, 2>& a) {
        return a;
    }

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2>& a) {
        return Point<T, 2>(-a.x, -a.y);
    }

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2>& a, T b) {
        return a.add(b);
    }

    template <typename T>
    Point<T, 2> operator+(T a, const Point<T, 2>& b) {
        return b.radd(a);
    }

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2>& a, const Point<T, 2>& b) {
        return a.add(b);
    }

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2>& a, T b) {
        return a.sub(b);
    }

    template <typename T>
    Point<T, 2> operator-(T a, const Point<T, 2>& b) {
        return b.rsub(a);
    }

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2>& a, const Point<T, 2>& b) {
        return a.sub(b);
    }

    template <typename T>
    Point<T, 2> operator*(const Point<T, 2>& a, T b) {
        return a.mul(b);
    }

    template <typename T>
    Point<T, 2> operator*(T a, const Point<T, 2>& b) {
        return b.rmul(a);
    }

    template <typename T>
    Point<T, 2> operator*(const Point<T, 2>& a, const Point<T, 2>& b) {
        return a.mul(b);
    }

    template <typename T>
    Point<T, 2> operator/(const Point<T, 2>& a, T b) {
        return a.div(b);
    }

    template <typename T>
    Point<T, 2> operator/(T a, const Point<T, 2>& b) {
        return b.rdiv(a);
    }

    template <typename T>
    Point<T, 2> operator/(const Point<T, 2>& a, const Point<T, 2>& b) {
        return a.div(b);
    }

    template <typename T>
    Point<T, 2> min(const Point<T, 2>& a, const Point<T, 2>& b) {
        return Point<T, 2>(std::min(a.x, b.x), std::min(a.y, b.y));
    }

    template <typename T>
    Point<T, 2> max(const Point<T, 2>& a, const Point<T, 2>& b) {
        return Point<T, 2>(std::max(a.x, b.x), std::max(a.y, b.y));
    }

    template <typename T>
    Point<T, 2> clamp(
        const Point<T, 2>& v, const Point<T, 2>& low, const Point<T, 2>& high) {
        return Point<T, 2>(clamp(v.x, low.x, high.x), clamp(v.y, low.y, high.y));
    }

    template <typename T>
    Point<T, 2> ceil(const Point<T, 2>& a) {
        return Point<T, 2>(std::ceil(a.x), std::ceil(a.y));
    }

    template <typename T>
    Point<T, 2> floor(const Point<T, 2>& a) {
        return Point<T, 2>(std::floor(a.x), std::floor(a.y));
    }
}
