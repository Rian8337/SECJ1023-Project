#include "SoftDrinksItem.h"
#include "ItemType.h"
#include <utility>

using namespace std;

SoftDrinksItem::SoftDrinksItem()
    : FoodItem(ItemType::softDrinks), ItemWithVolume() {}

SoftDrinksItem::SoftDrinksItem(size_t id)
    : FoodItem(id, ItemType::softDrinks), ItemWithVolume() {}

SoftDrinksItem::SoftDrinksItem(const string &name, const string &description,
                               size_t stock, float price, float calories,
                               float volume)
    : FoodItem(name, description, ItemType::softDrinks, stock, price, calories),
      ItemWithVolume(volume) {}

SoftDrinksItem::SoftDrinksItem(const SoftDrinksItem &copy)
    : FoodItem(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

SoftDrinksItem::SoftDrinksItem(SoftDrinksItem &&other)
    : FoodItem(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

SoftDrinksItem *SoftDrinksItem::deepClone() const {
    return new SoftDrinksItem(*this);
}

string SoftDrinksItem::outputToConsole() const {
    return FoodItem::outputToConsole() + ItemWithVolume::outputToConsole();
}

void SoftDrinksItem::inputData() {
    FoodItem::inputData();
    ItemWithVolume::inputData();
}

SoftDrinksItem &SoftDrinksItem::operator=(const SoftDrinksItem &right) {
    FoodItem::operator=(right);
    ItemWithVolume::operator=(right);

    return *this;
}

SoftDrinksItem &SoftDrinksItem::operator=(SoftDrinksItem &&right) {
    FoodItem::operator=(move(right));
    ItemWithVolume::operator=(move(right));

    return *this;
}
