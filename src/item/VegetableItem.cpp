#include "VegetableItem.h"
#include <string>
#include <utility>

using namespace std;

VegetableItem::VegetableItem()
    : FoodItem(ItemType::vegetables), ItemWithWeight() {}

VegetableItem::VegetableItem(size_t id)
    : FoodItem(id, ItemType::vegetables), ItemWithWeight() {}

VegetableItem::VegetableItem(const string &name, const string &description,
                             size_t stock, float price, float calories,
                             float weight)
    : FoodItem(name, description, ItemType::vegetables, stock, price, calories),
      ItemWithWeight(weight) {}

VegetableItem::VegetableItem(const VegetableItem &copy)
    : FoodItem(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

VegetableItem::VegetableItem(VegetableItem &&other)
    : FoodItem(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

VegetableItem *VegetableItem::deepClone() const {
    return new VegetableItem(*this);
}

string VegetableItem::outputToConsole() const {
    return FoodItem::outputToConsole() + ItemWithWeight::outputToConsole();
}

void VegetableItem::inputData() {
    FoodItem::inputData();
    ItemWithWeight::inputData();
}

VegetableItem &VegetableItem::operator=(const VegetableItem &right) {
    FoodItem::operator=(right);
    ItemWithWeight::operator=(right);

    return *this;
}

VegetableItem &VegetableItem::operator=(VegetableItem &&right) {
    FoodItem::operator=(move(right));
    ItemWithWeight::operator=(move(right));

    return *this;
}
