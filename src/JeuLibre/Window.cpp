#include "pch.h"
#include "Window.h"
#include "Entity.h"

Window::Window(const std::string& title, int width, int height)
    : window(sf::VideoMode(width, height), title) {}


void Window::PollEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Window::Clear() {
    window.clear();
}

void Window::Display() {
    window.display();
}

bool Window::IsOpen() const {
    return window.isOpen();
}

sf::RenderWindow& Window::GetRenderWindow() {
    return window;
}