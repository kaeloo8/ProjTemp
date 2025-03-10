#include "pch.h"
#include "Camera.h"

sf::Vector2f Camera::GetPos() {
	return CameraPos;
}
float Camera::GetPosX() {
	return CameraPos.x;
}
float Camera::GetPosY() {
	return CameraPos.y;
}

void Camera::SetPos(sf::Vector2f Pos) {
	CameraPos = Pos;
}
void Camera::SetPos(float x,float y) {
	CameraPos = {x,y };
}
void Camera::SetPosX(float PosX) {
	CameraPos.x = PosX;
}
void Camera::SetPosY(float PosY) {
	CameraPos.y = PosY;
}

void Camera::Add(float x, float y) {
	CameraPos.x += x;
	CameraPos.y += y;
}
