#pragma once
#include <stdexcept> // Pour std::out_of_range
#include <type_traits> // Pour std::is_pointer

template <typename T>
class vector {
private:
    T* data;           // Tableau dynamique pour stocker les éléments
    size_t capacity;   // Capacité totale
    size_t size;       // Nombre d'éléments

    void resize(size_t newCapacity);  // Redimensionne le tableau interne

public:
    // Constructeurs et destructeurs
    vector();
    ~vector();
    vector(const vector<T>& other);
    vector<T>& operator=(const vector<T>& other);

    // Ajout et suppression
    void push_back(const T& value);
    void pop_back();
    void erase(size_t index);
    void clear();

    // Accès aux éléments
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Taille et capacité
    size_t get_size() const;
    size_t get_capacity() const;

    // Itérateurs simples
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;

    // Suppression des objets (pour les types pointeurs)
    void destroy();
};

#include "vector.tpp"
