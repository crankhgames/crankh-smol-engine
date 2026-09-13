#include "Math/Math.h"

namespace Core::Math {
    Vec2::operator Vec2Int() const{
        return Vec2Int{static_cast<int>(x), static_cast<int>(y)};
    }

    Vec2Int::operator Vec2() const{
        return Vec2{static_cast<double>(x), static_cast<double>(y)};
    }
}