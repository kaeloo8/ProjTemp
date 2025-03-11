#include "pch.h"
#include "Util.h"


Vector2f::Vector2f() {
    x = 0;
    y = 0;
}
Vector2f::Vector2f(float _x,float _y) {
    x = _x;
    y = _y;
}

void Vector2f::Set(float _x, float _y) {
    x = _x;
    y = _y;
}

////////////////////////////////////////////////////////////////////////////

Depth::Depth() {
    DepthIndice = 0;
}

Depth::Depth(int Value) {
    DepthIndice = Value;
}

int Depth::GetDepth() {
    return DepthIndice;
}

void Depth::SetDepth(int Value) {
    DepthIndice = Value;
}

////////////////////////////////////////////////////////////////////////////

ItemInfo::ItemInfo(std::string name, int quantity, sf::Texture texture) : ImgItem(texture){
    Name = name;
    Quantity = quantity;
}

int ItemInfo::GetQuantity() {
    return Quantity;
}
std::string ItemInfo::GetName() {
    return Name;
}
sf::Texture& ItemInfo::GetTexture() {
    return ImgItem;
}

void ItemInfo::SetQuantity(int quantity) {
    Quantity = quantity;
}
void ItemInfo::SetName(std::string name) {
    Name = name;
}
void ItemInfo::SetTexture(sf::Texture texture) {
    ImgItem = texture;
}

void ItemInfo::AddQuantity(int Value) {
    Quantity += Value;
}
void ItemInfo::LessQuantity(int Value) {
    Quantity -= Value;
}
void ItemInfo::DivideQuantity(int Value) {
    Quantity /= Value;
}
void ItemInfo::MultiplyQuantity(int Value) {
    Quantity *= Value;
}

////////////////////////////////////////////////////////////////////////////

ColiderABBA::ColiderABBA() {

}
ColiderABBA::ColiderABBA(float sx, float sy) {

}

void ColiderABBA::SetSize(float sx, float sy) {

}
void ColiderABBA::SetPos(float x, float y) {

}

////////////////////////////////////////////////////////////////////////////

ColiderCircle::ColiderCircle() {

}
ColiderCircle::ColiderCircle(float rad) {

}

void ColiderCircle::SetRad(float rad) {

}
void ColiderCircle::SetPos(float x, float y) {

}