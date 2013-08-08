#ifndef TYPE_H
#define TYPE_H

#include <numeric_limits>
#include <exception>

template <typename Type,
         Type Min = std::numeric_limits<Type>::min(),
         Type Max = std::numeric_limits<Type>::max()>
         class numeric {
             public:
                 typedef Type value_type;

                 constexpr static Type min = Min;
                 constexpr static Type max = Max;

                 numeric(value_type const & __n):
                     _value(__n)
             {
                 if(_value < min || _value > max)
                     throw std::domain_error("Value out of range");
             }

                 numeric(numeric<type, min, max> const & __n):
                     _value(__n._value)
             {
             }

                 template <Type _Min, Type _Max>
                     explicit numeric(numeric<type, _Min, _Max> const & __n):
                         _value(__n._value)
             {
                 static_assert(_Min >= Min && _Max <= Max, "Value out of range");
             }

                 numeric(numeric<type, min, max> && __n):
                     _value(__n._value)
             {
                 __n._value = min;
             }

                 ~numeric() = default;

                 numeric & operator=(numeric<type, min, max> __n) {
                     std::swap(_value, __n._value);
                     return *this;
                 }

                 template <Type _Min, Type _Max>
                     numeric & operator=(numeric<type, _Min, _Max> __n) {
                         static_assert(_Min >= Min && _Max <= Max, "Value out of range");
                         std::swap(_value, __n._value);
                         return *this;
                     }

                 friend numeric operator+(numeric const &, numeric const &);
                 friend numeric operator-(numeric const &, numeric const &);
                 friend numeric operator*(numeric const &, numeric const &);
                 friend numeric operator/(numeric const &, numeric const &);
                 friend numeric operator-(numeric const &);

                 numeric operator+=(numeric const & __n) {
                     _value += __n._value;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 numeric operator-=(numeric const & __n) {
                     _value -= __n._value;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 numeric operator*=(numeric const & __n) {
                     _value *= __n._value;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 numeric operator/=(numeric const & __n) {
                     _value /= __n._value;
                     if(_value < min || _value > max)
                         throw std::domain_error("Value out of range");
                     return *this;
                 }

                 value_type const & value() const {
                     return _value;
                 }

             protected:
                 value_type _value;
         };

template <typename Type, Type Min, Type Max>
numeric<Type, Min, Max> operator+(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value + __r._value);
}

template <typename Type, Type Min, Type Max>
numeric<Type, Min, Max> operator-(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value - __r._value);
}

template <typename Type, Type Min, Type Max>
numeric<Type, Min, Max> operator*(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value * __r._value);
}

template <typename Type, Type Min, Type Max>
numeric<Type, Min, Max> operator/(
        numeric<Type, Min, Max> const & __l,
        numeric<Type, Min, Max> const & __r) {
    return numeric<Type, Min, Max>(__l._value / __r._value);
}

template <typename Type, Type Min, Type Max>
numeric<Type, Min, Max> operator-(numeric<Type, Min, Max> const & __l) {
    return numeric<Type, Min, Max>(-__l._value);
}

#endif
