#include "vector.h"

// Fonction privée de redimensionnement du tableau interne
template <typename T>
void vector<T>::resize(size_t newCapacity) {
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// Constructeur par défaut
template <typename T>
vector<T>::vector() : data(nullptr), capacity(0), size(0) {}

// Destructeur
template <typename T>
vector<T>::~vector() {
    delete[] data;
}

// Constructeur par copie
template <typename T>
vector<T>::vector(const vector<T>& other)
    : data(new T[other.capacity]), capacity(other.capacity), size(other.size) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// Opérateur d'affectation
template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    if (this != &other) {
        delete[] data;
        data = new T[other.capacity];
        capacity = other.capacity;
        size = other.size;
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Ajout d'un élément à la fin
template <typename T>
void vector<T>::push_back(const T& value) {
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}

// Suppression du dernier élément
template <typename T>
void vector<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

// Suppression d'un élément à une position donnée
template <typename T>
void vector<T>::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index hors limites");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

// Vider le vecteur
template <typename T>
void vector<T>::clear() {
    size = 0;
}

// Accès en lecture-écriture aux éléments
template <typename T>
T& vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index hors limites");
    }
    return data[index];
}

// Accès en lecture aux éléments
template <typename T>
const T& vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index hors limites");
    }
    return data[index];
}

// Taille actuelle du vecteur
template <typename T>
size_t vector<T>::get_size() const {
    return size;
}

// Capacité totale du vecteur
template <typename T>
size_t vector<T>::get_capacity() const {
    return capacity;
}

// Itérateur sur le début
template <typename T>
T* vector<T>::begin() {
    return data;
}

// Itérateur constant sur le début
template <typename T>
const T* vector<T>::begin() const {
    return data;
}

// Itérateur sur la fin
template <typename T>
T* vector<T>::end() {
    return data + size;
}

// Itérateur constant sur la fin
template <typename T>
const T* vector<T>::end() const {
    return data + size;
}

// Suppression des objets dans le vecteur pour les types pointeurs
template <typename T>
void vector<T>::destroy() {
    if constexpr (std::is_pointer<T>::value) {
        for (size_t i = 0; i < size; ++i) {
            delete data[i]; // Supprime les éléments pointés par le tableau
        }
    }
    size = 0; // Vider le vecteur, peu importe le type
}
