#include "pch.h"
#include "FillBar.h"

FillBar::FillBar() {
	MaxSize;
	Fill = MaxSize;
	Heigh = 10;
	Bar.setFillColor(sf::Color::Green);
	Background.setFillColor(sf::Color::Blue);
}

void FillBar::SetFill(float x)
{
	Fill = x;
}

float FillBar::GetFill() {
	return Fill;
}

void FillBar::OnUpdate()
{
	/*
	Background.setSize({ MaxSize + 2, Heigh + 2 });
	Bar.setSize({ Fill, Heigh });
	Background.setPosition(0, 100);
	Bar.setPosition(Background.getPosition());*/
}
