#include "CosmeticItem.h"
#include <utility>

using namespace std;

CosmeticItem::CosmeticItem() : Item(ItemType::cosmetic) {}

CosmeticItem::CosmeticItem(size_t id) : Item(id, ItemType::cosmetic) {}

CosmeticItem::CosmeticItem(const string &name, const string &description,
                           size_t stock, float price)
    : Item(name, description, ItemType::cosmetic, stock, price) {}

CosmeticItem::CosmeticItem(const CosmeticItem &copy)
    : Item(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

CosmeticItem::CosmeticItem(CosmeticItem &&other) { *this = move(other); }

CosmeticItem *CosmeticItem::deepClone() const {
    return new CosmeticItem(*this);
}

CosmeticItem &CosmeticItem::operator=(const CosmeticItem &right) {
    Item::operator=(right);

    return *this;
}

CosmeticItem &CosmeticItem::operator=(CosmeticItem &&right) {
    Item::operator=(move(right));

    return *this;
}
