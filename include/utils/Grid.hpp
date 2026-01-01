#pragma once
#include <memory> 

template <typename T>
class Grid {
public:
    Grid(int width, int height);
    ~Grid() = default;

    // Accès rapide [x][y]
    T* operator[](int x);
    const T* operator[](int x) const;

    int getWidth() const;
    int getHeight() const;

private:
    std::unique_ptr<T[]> m_data;
    int m_width;
    int m_height;
};


template <typename T>
Grid<T>::Grid(int width, int height) 
    : m_width(width), m_height(height) 
{
    m_data = std::make_unique<T[]>(width * height);
}

template <typename T>
T* Grid<T>::operator[](int x) {
    return m_data.get() + (x * m_height);
}

template <typename T>
const T* Grid<T>::operator[](int x) const {
    return m_data.get() + (x * m_height);
}

template <typename T>
int Grid<T>::getWidth() const { return m_width; }

template <typename T>
int Grid<T>::getHeight() const { return m_height; }