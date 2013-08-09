#ifndef TYPE_H
#define TYPE_H

#include <limits>
#include <stdexcept>

template <typename Type, Type Min, Type Max> class numeric;

template <typename Type, Type Min, Type Max>
inline numeric<Type, Min, Max> operator+(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value + __r._value);
}

template <typename Type, Type Min, Type Max>
inline numeric<Type, Min, Max> operator-(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value - __r._value);
}

template <typename Type, Type Min, Type Max>
inline numeric<Type, Min, Max> operator*(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value * __r._value);
}

template <typename Type, Type Min, Type Max>
inline numeric<Type, Min, Max> operator/(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value / __r._value);
}

template <typename Type, Type Min, Type Max>
numeric<Type, Min, Max> operator-(numeric<Type, Min, Max> const & __l) {
    return numeric<Type, Min, Max>(-__l._value);
}

template <typename Type,
         Type Min = std::numeric_limits<Type>::min(),
         Type Max = std::numeric_limits<Type>::max()>
         class numeric {
             public:
                 typedef Type value_type;

                 constexpr static Type min = Min;
                 constexpr static Type max = Max;

                 explicit numeric(value_type const & __n):
                     _value(__n)
             {
                 if(_value < min || _value > max)
                     throw std::domain_error("Value out of range");
             }

                 numeric(numeric<value_type, min, max> const & __n):
                     _value(__n._value)
             {
             }

                 template <Type _Min, Type _Max>
                     explicit numeric(numeric<value_type, _Min, _Max> const & __n):
                         _value(__n._value)
             {
                 static_assert(_Min >= Min && _Max <= Max, "Value out of range");
             }

                 numeric(numeric<value_type, min, max> && __n):
                     _value(__n._value)
             {
                 __n._value = min;
             }

                 ~numeric() = default;

                 numeric & operator=(numeric<value_type, min, max> __n) {
                     std::swap(_value, __n._value);
                     return *this;
                 }

                 template <Type _Min, Type _Max>
                     numeric & operator=(numeric<value_type, _Min, _Max> __n) {
                         static_assert(_Min >= Min && _Max <= Max, "Value out of range");
                         std::swap(_value, __n._value);
                         return *this;
                     }

                 inline operator value_type() const {
                     return _value;
                 }

                 friend numeric<value_type, min, max> operator+<>(
                         numeric<value_type, min, max> const &,
                         numeric<value_type, min, max> const &);
                 friend numeric<value_type, min, max> operator-<>(
                         numeric<value_type, min, max> const &,
                         numeric<value_type, min, max> const &);
                 friend numeric<value_type, min, max> operator*<>(
                         numeric<value_type, min, max> const &,
                         numeric<value_type, min, max> const &);
                 friend numeric<value_type, min, max> operator/<>(
                         numeric<value_type, min, max> const &,
                         numeric<value_type, min, max> const &);
                 friend numeric<value_type, min, max> operator-<>(
                         numeric<value_type, min, max> const &);

                 inline bool operator==(value_type const & __v) const {
                     return _value == __v;
                 }

                 inline bool operator!=(value_type const & __v) const {
                     return _value != __v;
                 }

                 inline bool operator<=(value_type const & __v) const {
                     return _value <= __v;
                 }

                 inline bool operator>=(value_type const & __v) const {
                     return _value >= __v;
                 }

                 inline bool operator<(value_type const & __v) const {
                     return _value < __v;
                 }

                 inline bool operator>(value_type const & __v) const {
                     return _value > __v;
                 }

                 inline bool operator==(numeric const & __n) const {
                     return *this == __n._value;
                 }

                 inline bool operator!=(numeric const & __n) const {
                     return *this != __n._value;
                 }

                 inline bool operator<=(numeric const & __n) const {
                     return *this <= __n._value;
                 }

                 inline bool operator>=(numeric const & __n) const {
                     return *this >=  __n._value;
                 }

                 inline bool operator<(numeric const & __n) const {
                     return *this <  __n._value;
                 }

                 inline bool operator>(numeric const & __n) const {
                     return *this >  __n._value;
                 }

                 inline numeric operator++(int) {
                     return *this += 1;
                 }

                 inline numeric operator++() {
                     return *this += 1;
                 }

                 inline numeric operator--(int) {
                     return *this -= 1;
                 }

                 inline numeric operator--() {
                     return *this -= 1;
                 }

                 numeric operator+=(value_type const & __n) {
                     _value += __n;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 numeric operator-=(value_type const & __n) {
                     _value -= __n;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 numeric operator*=(value_type const & __n) {
                     _value *= __n;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 numeric operator/=(value_type const & __n) {
                     _value /= __n;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 inline numeric operator+=(numeric const & __n) {
                     return *this += __n._value;
                 }

                 inline numeric operator-=(numeric const & __n) {
                     return *this -= __n._value;
                 }

                 inline numeric operator*=(numeric const & __n) {
                     return *this *= __n._value;
                 }

                 inline numeric operator/=(numeric const & __n) {
                     return *this /= __n._value;
                 }

                 inline value_type const & value() const {
                     return _value;
                 }

             protected:
                 value_type _value;
         };

#endif
