#include "FoodItem.h"
#include <iomanip>
#include <iostream>

using namespace std;

FoodItem::FoodItem(ItemType type) : Item(type) { calories = 0; }

FoodItem::FoodItem(size_t id, ItemType type) : Item(id, type) { calories = 0; }

FoodItem::FoodItem(const string &name, const string &description, ItemType type,
                   size_t stock, float price, float calories)
    : Item(name, description, type, stock, price) {
    calories = 0;
}

FoodItem::FoodItem(const FoodItem &copy)
    : Item(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

FoodItem::FoodItem(FoodItem &&other)
    : Item(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

float FoodItem::getCalories() const { return calories; }

void FoodItem::setCalories(float calories) {
    if (calories < 0) {
        throw invalid_argument(
            "The calories of a food must be more than or equal to zero.");
    }

    this->calories = calories;
}

string FoodItem::outputToConsole() const {
    ostringstream os(Item::outputToConsole());

    os << "Calories: " << setprecision(2) << fixed << calories << "kcal"
       << endl;

    return os.str();
}

void FoodItem::inputData() {
    Item::inputData();

    while (true) {
        string calories;
        cout << "Enter food calories in kcal (currently " << setprecision(2)
             << fixed << this->calories << "): ";
        getline(cin, calories);

        try {
            setCalories(stof(calories));
            break;
        } catch (const exception &ignored) {
            cout << "Invalid calories." << endl;
        }
    }
}

FoodItem *FoodItem::deepClone() const { return new FoodItem(*this); }

FoodItem &FoodItem::operator=(const FoodItem &right) {
    Item::operator=(right);

    calories = right.calories;

    return *this;
}

FoodItem &FoodItem::operator=(FoodItem &&other) {
    Item::operator=(move(other));

    calories = other.calories;
    other.calories = 0;

    return *this;
}
