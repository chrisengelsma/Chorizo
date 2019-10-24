#ifndef CHORIZO_MATHS_H_
#define CHORIZO_MATHS_H_

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif

namespace chorizo
{
    class CHORIZO_EXPORT Maths
    {

    public:
        template<typename T = double>
        static constexpr double Pi{T(3.14159265358979323846264338327950288L)};

        template<typename T = double>
        static constexpr T ToRadians(const T& degrees)
        {
            return static_cast<T>(degrees * Pi<long double> / 180);
        }

        template<typename T = double>
        static constexpr T ToDegrees(const T& radians)
        {
            return static_cast<T>(radians * 180 / Pi<long double>);
        }

        template<typename T = double>
        static T WrapDegrees(const T& degrees)
        {
            auto x{std::fmod(degrees, 360)};
            if (x < 0)
            {
                x += 360;
            }

            return static_cast<T>(x);
        }

        template<typename T = double>
        static T WrapRadians(const T& radians)
        {
            auto x{std::fmod(radians, 2 * Pi<T>)};

            if (x < 0)
            {
                x += 2 * Pi<T>;
            }

            return static_cast<T>(x);
        }

        template<typename T = double>
        static constexpr T Sind(const T& deg)
        {
            return std::sin(ToRadians(deg));
        }

        template<typename T = double>
        static constexpr T Cosd(const T& deg)
        {
            return std::cos(ToRadians(deg));
        }

        template<typename T = double >
        static constexpr bool ArrayContains(const T* array, const T& val)
        {
            for (int i : array)
            {
                if (i == val)
                {
                    return true;
                }
            }
            return false;
        }
    };

}
#endif // CHORIZO_MATHS_H_
