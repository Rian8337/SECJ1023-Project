#include "NoodlesItem.h"
#include "ItemType.h"
#include <string>
#include <utility>

using namespace std;

NoodlesItem::NoodlesItem() : FoodItem(ItemType::noodles), ItemWithWeight() {}

NoodlesItem::NoodlesItem(size_t id)
    : FoodItem(id, ItemType::noodles), ItemWithWeight() {}

NoodlesItem::NoodlesItem(const string &name, const string &description,
                         size_t stock, float price, float calories,
                         float weight)
    : FoodItem(name, description, ItemType::noodles, stock, price, calories),
      ItemWithWeight(weight) {}

NoodlesItem::NoodlesItem(const NoodlesItem &copy)
    : FoodItem(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

NoodlesItem::NoodlesItem(NoodlesItem &&other)
    : FoodItem(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

NoodlesItem *NoodlesItem::deepClone() const { return new NoodlesItem(*this); }

string NoodlesItem::outputToConsole() const {
    return FoodItem::outputToConsole() + ItemWithWeight::outputToConsole();
}

void NoodlesItem::inputData() {
    FoodItem::inputData();
    ItemWithWeight::inputData();
}

NoodlesItem &NoodlesItem::operator=(const NoodlesItem &right) {
    FoodItem::operator=(right);
    ItemWithWeight::operator=(right);

    return *this;
}

NoodlesItem &NoodlesItem::operator=(NoodlesItem &&right) {
    FoodItem::operator=(move(right));
    ItemWithWeight::operator=(move(right));

    return *this;
}
