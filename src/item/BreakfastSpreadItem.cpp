#include "BreakfastSpreadItem.h"
#include "ItemType.h"
#include <string>
#include <utility>

using namespace std;

BreakfastSpreadItem::BreakfastSpreadItem()
    : FoodItem(ItemType::breakfastSpread) {}

BreakfastSpreadItem::BreakfastSpreadItem(size_t id)
    : FoodItem(id, ItemType::breakfastSpread) {}

BreakfastSpreadItem::BreakfastSpreadItem(const string &name,
                                         const string &description,
                                         size_t stock, float price,
                                         float calories)
    : FoodItem(name, description, ItemType::breakfastSpread, stock, price,
               calories) {}

BreakfastSpreadItem::BreakfastSpreadItem(const BreakfastSpreadItem &copy)
    : FoodItem(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

BreakfastSpreadItem::BreakfastSpreadItem(BreakfastSpreadItem &&other)
    : FoodItem(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

BreakfastSpreadItem *BreakfastSpreadItem::deepClone() const {
    return new BreakfastSpreadItem(*this);
}

BreakfastSpreadItem &
BreakfastSpreadItem::operator=(const BreakfastSpreadItem &right) {
    FoodItem::operator=(right);

    return *this;
}

BreakfastSpreadItem &
BreakfastSpreadItem::operator=(BreakfastSpreadItem &&right) {
    FoodItem::operator=(move(right));

    return *this;
}