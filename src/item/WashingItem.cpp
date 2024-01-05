#include "WashingItem.h"
#include "ItemType.h"
#include <string>
#include <utility>

using namespace std;

WashingItem::WashingItem() : Item(ItemType::washing) {}

WashingItem::WashingItem(size_t id) : Item(id, ItemType::washing) {}

WashingItem::WashingItem(const string &name, const string &description,
                         size_t stock, float price)
    : Item(name, description, ItemType::washing, stock, price) {}

WashingItem::WashingItem(const WashingItem &copy)
    : Item(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

WashingItem::WashingItem(WashingItem &&other)
    : Item(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

WashingItem *WashingItem::deepClone() const { return new WashingItem(*this); }

WashingItem &WashingItem::operator=(const WashingItem &right) {
    Item::operator=(right);

    return *this;
}

WashingItem &WashingItem::operator=(WashingItem &&right) {
    Item::operator=(move(right));

    return *this;
}
