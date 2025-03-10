#include "pch.h"
#include "Vector2f.h"

Vector2f::Vector2f() {
    x = 0;
    y = 0;
}
Vector2f::Vector2f(float _x,float _y) {
    x = _x;
    y = _y;
}

Vector2f Vector2f::GetVect2f(){
    return { x, y };
}