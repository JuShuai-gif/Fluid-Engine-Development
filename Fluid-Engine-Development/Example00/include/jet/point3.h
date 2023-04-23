#pragma once
#include "point2.h"
#include "macros.h"
#include "math_utils.h"

#include <algorithm>
#include <cassert>
namespace jet {
    template <typename T>
    class Point<T, 3> {
    public:
        static_assert(std::is_arithmetic<T>::value,
            "Point only can be instantiated with arithematic types");

        // X 
        T x,y,z;

        // MARK: 构造函数

        //! Constructs default point (0, 0, 0).
        constexpr Point() : x(0), y(0), z(0) {}

        //! Constructs point with given parameters \p x_, \p y_, and \p z_.
        constexpr Point(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

        // 利用point2 + z_
        constexpr Point(const Point2<T>& v, T z_) : x(v.x), y(v.y), z(z_) {}

        // 构造函数（利用初始化列表）
        template <typename U>
        Point(const std::initializer_list<U>& lst);

        // 拷贝构造
        constexpr Point(const Point& v) : x(v.x), y(v.y), z(v.z) {}

        // MARK: Basic setters

        // x\y\z相同，同为 s
        void set(T s);

        // x, y, and z 
        void set(T x, T y, T z);

        // 利用point模板 + z 设置元素的值
        void set(const Point2<T>& pt, T z);

        // 模板初始化列表初始化
        template <typename U>
        void set(const std::initializer_list<U>& lst);

        // 三个值都为 v
        void set(const Point& v);

        // x\y\z同为 0
        void setZero();

        // MARK: Binary operations: new instance = this (+) v

        //this + (v, v, v).
        Point add(T v) const;

        //this + (v.x, v.y, v.z).
        Point add(const Point& v) const;

        // this - (v, v, v).
        Point sub(T v) const;

        // this - (v.x, v.y, v.z).
        Point sub(const Point& v) const;

        // this * (v, v, v).
        Point mul(T v) const;

        // this * (v.x, v.y, v.z).
        Point mul(const Point& v) const;
        // this / (v, v, v).
        Point div(T v) const;

        // this / (v.x, v.y, v.z).
        Point div(const Point& v) const;

        // 当前point3在操作符右边

        // (v, v, v) - this.
        Point rsub(T v) const;

        // (v.x, v.y, v.z) - this.
        Point rsub(const Point& v) const;

        // (v, v, v) / this.
        Point rdiv(T v) const;

        // (v.x, v.y, v.z) / this.
        Point rdiv(const Point& v) const;

        // MARK: 复合操作

        // this += (v, v, v).
        void iadd(T v);

        // this += (v.x, v.y, v.z).
        void iadd(const Point& v);

        // this -= (v, v, v).
        void isub(T v);

        // this -= (v.x, v.y, v.z).
        void isub(const Point& v);

        // this *= (v, v, v).
        void imul(T v);

        // this *= (v.x, v.y, v.z).
        void imul(const Point& v);

        // this /= (v, v, v).
        void idiv(T v);

        // this /= (v.x, v.y, v.z).
        void idiv(const Point& v);

        // 索引获取操作

        //! Returns const reference to the \p i -th element of the point.
        const T& at(size_t i) const;

        //! Returns reference to the \p i -th element of the point.
        T& at(size_t i);

        //! Returns the sum of all the components (i.e. x + y).
        T sum() const;

        //! Returns the minimum value among x, y, and z.
        T min() const;

        //! Returns the maximum value among x, y, and z.
        T max() const;

        // 返回绝对最小值
        T absmin() const;
        // 返回绝对最大值
        T absmax() const;

        // 返回最大的那个轴 x(0),y(1),z(2)
        size_t dominantAxis() const;
        // 返回最小的那个轴 x(0),y(1),z(2)
        size_t subminantAxis() const;

        // 当前point3的类型转为 U
        template <typename U>
        Point<U, 3> castTo() const;

        //! Returns true if \p other is the same as this point.
        bool isEqual(const Point& other) const;

        // MARK: 重载

        //! Returns reference to the \p i -th element of the point.
        T& operator[](size_t i);

        //! Returns const reference to the \p i -th element of the point.
        const T& operator[](size_t i) const;

        //! Set x, y, and z components with given initializer list.
        Point& operator=(const std::initializer_list<T>& lst);

        //! Set x, y, and z with other point \p pt.
        Point& operator=(const Point& v);

        //! Computes this += (v, v, v)
        Point& operator+=(T v);

        //! Computes this += (v.x, v.y, v.z)
        Point& operator+=(const Point& v);

        //! Computes this -= (v, v, v)
        Point& operator-=(T v);

        //! Computes this -= (v.x, v.y, v.z)
        Point& operator-=(const Point& v);

        //! Computes this *= (v, v, v)
        Point& operator*=(T v);

        //! Computes this *= (v.x, v.y, v.z)
        Point& operator*=(const Point& v);

        //! Computes this /= (v, v, v)
        Point& operator/=(T v);

        //! Computes this /= (v.x, v.y, v.z)
        Point& operator/=(const Point& v);

        //! Returns true if \p other is the same as this point.
        bool operator==(const Point& v) const;

        //! Returns true if \p other is the not same as this point.
        bool operator!=(const Point& v) const;
    };

    //! 三维向量别名
    template <typename T>
    using Point3 = Point<T, 3>;

    // 转为正号向量
    template <typename T>
    Point<T, 3> operator+(const Point<T, 3>& a);

    // 转为负号向量
    template <typename T>
    Point3<T> operator-(const Point3<T>& a);

    // (a, a, a) + (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator+(T a, const Point3<T>& b);

    // (a.x, a.y, a.z) + (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator+(const Point3<T>& a, const Point3<T>& b);

    // (a.x, a.y, a.z) - (b, b, b).
    template <typename T>
    Point3<T> operator-(const Point3<T>& a, T b);

    // (a, a, a) - (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator-(T a, const Point3<T>& b);

    // (a.x, a.y, a.z) - (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator-(const Point3<T>& a, const Point3<T>& b);

    //! Computes (a.x, a.y, a.z) * (b, b, b).
    template <typename T>
    Point3<T> operator*(const Point3<T>& a, T b);

    //! Computes (a, a, a) * (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator*(T a, const Point3<T>& b);

    //! Computes (a.x, a.y, a.z) * (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator*(const Point3<T>& a, const Point3<T>& b);

    //! Computes (a.x, a.y, a.z) / (b, b, b).
    template <typename T>
    Point3<T> operator/(const Point3<T>& a, T b);

    //! Computes (a, a, a) / (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator/(T a, const Point3<T>& b);

    //! Computes (a.x, a.y, a.z) / (b.x, b.y, b.z).
    template <typename T>
    Point3<T> operator/(const Point3<T>& a, const Point3<T>& b);

    //! Returns element-wise min point.
    template <typename T>
    Point3<T> min(const Point3<T>& a, const Point3<T>& b);

    //! Returns element-wise max point.
    template <typename T>
    Point3<T> max(const Point3<T>& a, const Point3<T>& b);

    //! Returns element-wise clamped point.
    template <typename T>
    Point3<T> clamp(const Point3<T>& v, const Point3<T>& low,
        const Point3<T>& high);

    //! Returns element-wise ceiled point.
    template <typename T>
    Point3<T> ceil(const Point3<T>& a);

    //! Returns element-wise floored point.
    template <typename T>
    Point3<T> floor(const Point3<T>& a);

    //! Float-type 3D point.
    typedef Point3<float> Point3F;

    //! Double-type 3D point.
    typedef Point3<double> Point3D;

    //! Integer-type 3D point.
    typedef Point3<ssize_t> Point3I;

    //! Unsigned integer-type 3D point.
    typedef Point3<size_t> Point3UI;

    /******************************************/
    // imp

    // Constructors
    template <typename T>
    template <typename U>
    Point<T, 3>::Point(const std::initializer_list<U>& lst) {
        set(lst);
    }

    // Basic setters
    template <typename T>
    void Point<T, 3>::set(T s) {
        x = s;
        y = s;
        z = s;
    }

    template <typename T>
    void Point<T, 3>::set(T newX, T newY, T newZ) {
        x = newX;
        y = newY;
        z = newZ;
    }

    template <typename T>
    void Point<T, 3>::set(const Point2<T>& pt, T newZ) {
        x = pt.x;
        y = pt.y;
        z = newZ;
    }

    template <typename T>
    template <typename U>
    void Point<T, 3>::set(const std::initializer_list<U>& lst) {
        assert(lst.size() >= 3);

        auto inputElem = lst.begin();
        x = static_cast<T>(*inputElem);
        y = static_cast<T>(*(++inputElem));
        z = static_cast<T>(*(++inputElem));
    }

    template <typename T>
    void Point<T, 3>::set(const Point& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    template <typename T>
    void Point<T, 3>::setZero() {
        x = y = z = 0;
    }

    // Binary operators: new instance = this (+) v
    template <typename T>
    Point<T, 3> Point<T, 3>::add(T v) const {
        return Point(x + v, y + v, z + v);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::add(const Point& v) const {
        return Point(x + v.x, y + v.y, z + v.z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::sub(T v) const {
        return Point(x - v, y - v, z - v);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::sub(const Point& v) const {
        return Point(x - v.x, y - v.y, z - v.z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::mul(T v) const {
        return Point(x * v, y * v, z * v);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::mul(const Point& v) const {
        return Point(x * v.x, y * v.y, z * v.z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::div(T v) const {
        return Point(x / v, y / v, z / v);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::div(const Point& v) const {
        return Point(x / v.x, y / v.y, z / v.z);
    }

    // Binary operators: new instance = v (+) this
    template <typename T>
    Point<T, 3> Point<T, 3>::rsub(T v) const {
        return Point(v - x, v - y, v - z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rsub(const Point& v) const {
        return Point(v.x - x, v.y - y, v.z - z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rdiv(T v) const {
        return Point(v / x, v / y, v / z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rdiv(const Point& v) const {
        return Point(v.x / x, v.y / y, v.z / z);
    }

    // Augmented operators: this (+)= v
    template <typename T>
    void Point<T, 3>::iadd(T v) {
        x += v;
        y += v;
        z += v;
    }

    template <typename T>
    void Point<T, 3>::iadd(const Point& v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    template <typename T>
    void Point<T, 3>::isub(T v) {
        x -= v;
        y -= v;
        z -= v;
    }

    template <typename T>
    void Point<T, 3>::isub(const Point& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    template <typename T>
    void Point<T, 3>::imul(T v) {
        x *= v;
        y *= v;
        z *= v;
    }

    template <typename T>
    void Point<T, 3>::imul(const Point& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
    }

    template <typename T>
    void Point<T, 3>::idiv(T v) {
        x /= v;
        y /= v;
        z /= v;
    }

    template <typename T>
    void Point<T, 3>::idiv(const Point& v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
    }

    // Basic getters
    template <typename T>
    const T& Point<T, 3>::at(size_t i) const {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    T& Point<T, 3>::at(size_t i) {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    T Point<T, 3>::sum() const {
        return x + y + z;
    }

    template <typename T>
    T Point<T, 3>::min() const {
        return std::min(std::min(x, y), z);
    }

    template <typename T>
    T Point<T, 3>::max() const {
        return std::max(std::max(x, y), z);
    }

    template <typename T>
    T Point<T, 3>::absmin() const {
        return jet::absmin(jet::absmin(x, y), z);
    }

    template <typename T>
    T Point<T, 3>::absmax() const {
        return jet::absmax(jet::absmax(x, y), z);
    }

    template <typename T>
    size_t Point<T, 3>::dominantAxis() const {
        return (std::fabs(x) > std::fabs(y))
            ? ((std::fabs(x) > std::fabs(z)) ? 0 : 2)
            : ((std::fabs(y) > std::fabs(z)) ? 1 : 2);
    }

    template <typename T>
    size_t Point<T, 3>::subminantAxis() const {
        return (std::fabs(x) < std::fabs(y))
            ? ((std::fabs(x) < std::fabs(z)) ? 0 : 2)
            : ((std::fabs(y) < std::fabs(z)) ? 1 : 2);
    }

    template <typename T>
    template <typename U>
    Point3<U> Point<T, 3>::castTo() const {
        return Point3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
    }

    template <typename T>
    bool Point<T, 3>::isEqual(const Point& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    // Operators
    template <typename T>
    T& Point<T, 3>::operator[](size_t i) {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    const T& Point<T, 3>::operator[](size_t i) const {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator=(const std::initializer_list<T>& lst) {
        set(lst);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator=(const Point& v) {
        set(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator+=(T v) {
        iadd(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator+=(const Point& v) {
        iadd(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator-=(T v) {
        isub(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator-=(const Point& v) {
        isub(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator*=(T v) {
        imul(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator*=(const Point& v) {
        imul(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator/=(T v) {
        idiv(v);
        return (*this);
    }

    template <typename T>
    Point<T, 3>& Point<T, 3>::operator/=(const Point& v) {
        idiv(v);
        return (*this);
    }

    template <typename T>
    bool Point<T, 3>::operator==(const Point& v) const {
        return isEqual(v);
    }

    template <typename T>
    bool Point<T, 3>::operator!=(const Point& v) const {
        return !isEqual(v);
    }

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3>& a) {
        return a;
    }

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3>& a) {
        return Point<T, 3>(-a.x, -a.y, -a.z);
    }

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3>& a, T b) {
        return a.add(b);
    }

    template <typename T>
    Point<T, 3> operator+(T a, const Point<T, 3>& b) {
        return b.radd(a);
    }

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3>& a, const Point<T, 3>& b) {
        return a.add(b);
    }

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3>& a, T b) {
        return a.sub(b);
    }

    template <typename T>
    Point<T, 3> operator-(T a, const Point<T, 3>& b) {
        return b.rsub(a);
    }

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3>& a, const Point<T, 3>& b) {
        return a.sub(b);
    }

    template <typename T>
    Point<T, 3> operator*(const Point<T, 3>& a, T b) {
        return a.mul(b);
    }

    template <typename T>
    Point<T, 3> operator*(T a, const Point<T, 3>& b) {
        return b.rmul(a);
    }

    template <typename T>
    Point<T, 3> operator*(const Point<T, 3>& a, const Point<T, 3>& b) {
        return a.mul(b);
    }

    template <typename T>
    Point<T, 3> operator/(const Point<T, 3>& a, T b) {
        return a.div(b);
    }

    template <typename T>
    Point<T, 3> operator/(T a, const Point<T, 3>& b) {
        return b.rdiv(a);
    }

    template <typename T>
    Point<T, 3> operator/(const Point<T, 3>& a, const Point<T, 3>& b) {
        return a.div(b);
    }

    template <typename T>
    Point<T, 3> min(const Point<T, 3>& a, const Point<T, 3>& b) {
        return Point<T, 3>(std::min(a.x, b.x), std::min(a.y, b.y),
            std::min(a.z, b.z));
    }

    template <typename T>
    Point<T, 3> max(const Point<T, 3>& a, const Point<T, 3>& b) {
        return Point<T, 3>(std::max(a.x, b.x), std::max(a.y, b.y),
            std::max(a.z, b.z));
    }

    template <typename T>
    Point<T, 3> clamp(const Point<T, 3>& v, const Point<T, 3>& low,
        const Point<T, 3>& high) {
        return Point<T, 3>(clamp(v.x, low.x, high.x), clamp(v.y, low.y, high.y),
            clamp(v.z, low.z, high.z));
    }

    template <typename T>
    Point<T, 3> ceil(const Point<T, 3>& a) {
        return Point<T, 3>(std::ceil(a.x), std::ceil(a.y), std::ceil(a.z));
    }

    template <typename T>
    Point<T, 3> floor(const Point<T, 3>& a) {
        return Point<T, 3>(std::floor(a.x), std::floor(a.y), std::floor(a.z));
    }
}

