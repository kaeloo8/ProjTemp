#include "pch.h"
#include "Inventory.h"

Inventory::Inventory(int size) : maxSize(size) {}

InventorySlot* Inventory::findSlot(ItemType type) {
    for (auto& slot : slots) {
        if (slot.item.type == type) return &slot;
    }
    return nullptr;
}

bool Inventory::addItem(const Item& item, int quantity) {
    InventorySlot* slot = findSlot(item.type);
    if (slot) {
        if (slot->quantity + quantity <= item.maxStack) {
            slot->quantity += quantity;
            return true;
        }
    }
    if (slots.size() < maxSize) {
        slots.emplace_back(item, quantity);
        return true;
    }
    return false; // inventaire plein
}

void Inventory::removeItem(ItemType type, int quantity) {
    auto it = std::remove_if(slots.begin(), slots.end(), [&](InventorySlot& slot) {
        if (slot.item.type == type) {
            slot.quantity -= quantity;
            return slot.quantity <= 0;
        }
        return false;
        });
    slots.erase(it, slots.end());
}

void Inventory::printInventory() const {
    for (const auto& slot : slots) {
        std::cout << slot.item.name << " x" << slot.quantity << std::endl;
    }
}
