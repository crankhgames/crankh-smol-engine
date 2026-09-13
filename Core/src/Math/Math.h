#pragma once

#include <iostream>
#include <format>
#include <cmath>

namespace Core::Math{

    class Vec2;
    class Vec2Int;

    class Vec2{
    private:
        double x{};
        double y{};

    public:
        Vec2():
            x{0.0}, y{0.0}
        {}

        Vec2(double _x, double _y):
            x{_x}, y{_y}
        {}

        ~Vec2() = default;

        Vec2(const Vec2& other):
            x{other.x}, y{other.y}
        {}

        Vec2& operator=(const Vec2& other){
            x = other.x;
            y = other.y;
            return *this;
        }

        double getX() const {return x;}
        double getY() const {return y;}

        void setX(double _x){
            x = _x;
        }
        void setY(double _y){
            y = _y;
        }
        void set(double _x, double _y){
            x = _x;
            y = _y;
        }


        void operator+=(const Vec2& other){
            x += other.x;
            y += other.y;
        }
        void operator-=(const Vec2& other){
            x -= other.x;
            y -= other.y;
        }
        void operator*=(double factor){
            x *= factor;
            y *= factor;
        }
        void operator/=(double factor){
            x /= factor;
            y /= factor;
        }
        
        friend Vec2 operator+(const Vec2& v1, const Vec2& v2){
            return Vec2{v1.x + v2.x, v1.y + v2.y};
        }

        friend Vec2 operator-(const Vec2& v1, const Vec2& v2){
            return Vec2{v1.x - v2.x, v1.y - v2.y};
        }

        friend Vec2 operator*(const Vec2& v, double factor){
            return Vec2{factor * v.x, factor * v.y};
        }
        friend Vec2 operator*(double factor, const Vec2& v){
            return Vec2{factor * v.x, factor * v.y};
        }

        friend Vec2 operator/(const Vec2& v, double factor){
            return Vec2{v.x / factor, v.y / factor};
        }
        friend Vec2 operator/(double factor, const Vec2& v){
            return Vec2{v.x / factor, v.y / factor};
        }


        double magnitudeSquared() const {
            return x*x + y*y;
        }
        double magnitude() const {
            return std::sqrt(x*x + y*y);
        }

        Vec2 normalized(){
            double mag {magnitude()};
            constexpr double epsilon {1e-5};

            if (mag < epsilon){
                return {0.0, 0.0};
            }
            else{
                return *this / mag;
            }

        }

        operator Vec2Int() const;

        friend std::ostream& operator<<(std::ostream& out, const Vec2& vec){
            out << std::format("({}, {})", vec.x, vec.y);
            return out;
        }
    };

    class Vec2Int{
    private:
        int x{};
        int y{};

    public:
        Vec2Int():
            x{0}, y{0}
        {}

        Vec2Int(int _x, int _y):
            x{_x}, y{_y}
        {}

        ~Vec2Int() = default;

        Vec2Int(const Vec2Int& other):
            x{other.x}, y{other.y}
        {}

        Vec2Int& operator=(const Vec2Int& other){
            x = other.x;
            y = other.y;
            return *this;
        }

        int getX() const {return x;}
        int getY() const {return y;}

        void setX(int _x){
            x = _x;
        }
        void setY(int _y){
            y = _y;
        }
        void set(int _x, int _y){
            x = _x;
            y = _y;
        }


        void operator+=(const Vec2Int& other){
            x += other.x;
            y += other.y;
        }
        void operator-=(const Vec2Int& other){
            x -= other.x;
            y -= other.y;
        }
        void operator*=(int factor){
            x *= factor;
            y *= factor;
        }
        void operator/=(int factor){
            x /= factor;
            y /= factor;
        }
        
        friend Vec2Int operator+(const Vec2Int& v1, const Vec2Int& v2){
            return Vec2Int{v1.x + v2.x, v1.y + v2.y};
        }

        friend Vec2Int operator-(const Vec2Int& v1, const Vec2Int& v2){
            return Vec2Int{v1.x - v2.x, v1.y - v2.y};
        }

        friend Vec2Int operator*(const Vec2Int& v, int factor){
            return Vec2Int{factor * v.x, factor * v.y};
        }
        friend Vec2Int operator*(int factor, const Vec2Int& v){
            return Vec2Int{factor * v.x, factor * v.y};
        }

        friend Vec2Int operator/(const Vec2Int& v, int factor){
            return Vec2Int{v.x / factor, v.y / factor};
        }
        friend Vec2Int operator/(int factor, const Vec2Int& v){
            return Vec2Int{v.x / factor, v.y / factor};
        }

        int magnitudeSquared() const {
            return x*x + y*y;
        }
        double magnitude() const {
            return std::sqrt(x*x + y*y);
        }

        Vec2Int normalized(){
            double mag {magnitude()};
            constexpr double epsilon {1e-5};

            if (mag < epsilon){
                return {0, 0};
            }
            else{
                return *this / mag;
            }

        }

        operator Vec2() const;

        friend std::ostream& operator<<(std::ostream& out, const Vec2Int& vec){
            out << std::format("({}, {})", vec.x, vec.y);
            return out;
        }
    };
 
    
}

template<>
struct std::formatter<Core::Math::Vec2>{

    constexpr auto parse(std::format_parse_context& ctx){
        return ctx.begin();
    }

    auto format(const Core::Math::Vec2& vec, std::format_context& ctx) const{
        return std::format_to(ctx.out(), "({}, {})", vec.getX(), vec.getY());
    }
};
