#include "FruitItem.h"
#include "ItemType.h"
#include <string>
#include <utility>

using namespace std;

FruitItem::FruitItem() : FoodItem(ItemType::fruit), ItemWithWeight() {}

FruitItem::FruitItem(size_t id)
    : FoodItem(id, ItemType::fruit), ItemWithWeight() {}

FruitItem::FruitItem(const string &name, const string &description,
                     size_t stock, float price, float calories, float weight)
    : FoodItem(name, description, ItemType::fruit, stock, price, calories),
      ItemWithWeight(weight) {}

FruitItem::FruitItem(const FruitItem &copy)
    : FoodItem(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

FruitItem::FruitItem(FruitItem &&other)
    : FoodItem(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

string FruitItem::outputToConsole() const {
    return FoodItem::outputToConsole() + ItemWithWeight::outputToConsole();
}

FruitItem *FruitItem::deepClone() const { return new FruitItem(*this); }

void FruitItem::inputData() {
    FoodItem::inputData();
    ItemWithWeight::inputData();
}

FruitItem &FruitItem::operator=(const FruitItem &right) {
    FoodItem::operator=(right);
    ItemWithWeight::operator=(right);

    return *this;
}

FruitItem &FruitItem::operator=(FruitItem &&right) {
    FoodItem::operator=(move(right));
    ItemWithWeight::operator=(move(right));

    return *this;
}
