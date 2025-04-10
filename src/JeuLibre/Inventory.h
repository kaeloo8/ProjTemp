#pragma once
#include <string>
#include <iostream>
#include <vector>


enum class ItemType {
    Carrot,
    Axe,
    Wood,
    // Ajoute ce que tu veux
};

struct Item {
    ItemType type;
    std::string name;
    int maxStack;

    Item(ItemType t, const std::string& n, int max)
        : type(t), name(n), maxStack(max) {
    }
};

struct InventorySlot {
    Item item;
    int quantity;

    InventorySlot(const Item& i, int q)
        : item(i), quantity(q) {
    }
};

class Inventory {
public:
    Inventory(int size);

    bool addItem(const Item& item, int quantity = 1);
    void removeItem(ItemType type, int quantity = 1);
    void printInventory() const;

private:
    int maxSize;
    std::vector<InventorySlot> slots;

    InventorySlot* findSlot(ItemType type);
};
