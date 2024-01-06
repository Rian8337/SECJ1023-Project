#include "ItemType.h"
#include <iostream>
#include <stdexcept>

using namespace std;

ItemType parseItemType(const short num) {
    switch (num) {
    case ItemType::cosmetic:
        return ItemType::cosmetic;
    case ItemType::kitchenware:
        return ItemType::kitchenware;
    case ItemType::softDrinks:
        return ItemType::softDrinks;
    case ItemType::breakfastSpread:
        return ItemType::breakfastSpread;
    case ItemType::noodles:
        return ItemType::noodles;
    case ItemType::washing:
        return ItemType::washing;
    case ItemType::fruit:
        return ItemType::fruit;
    case ItemType::vegetables:
        return ItemType::vegetables;
    default:
        throw invalid_argument("Unable to parse the number into an ItemType.");
    }
}

string itemTypeToString(const ItemType &itemType) {
    switch (itemType) {
    case ItemType::none:
        return "None";
    case ItemType::cosmetic:
        return "Cosmetic";
    case ItemType::kitchenware:
        return "Kitchenware";
    case ItemType::softDrinks:
        return "Soft Drink";
    case ItemType::breakfastSpread:
        return "Breakfast Spread";
    case ItemType::noodles:
        return "Noodles";
    case ItemType::washing:
        return "Washing";
    case ItemType::fruit:
        return "Fruit";
    case ItemType::vegetables:
        return "Vegetables";
    default:
        throw invalid_argument("Unable to convert the item type to a string.");
    }
}

void listItemTypes() {
    cout << "Available item types:" << endl
         << "1. " << itemTypeToString(ItemType::cosmetic) << endl
         << "2. " << itemTypeToString(ItemType::kitchenware) << endl
         << "3. " << itemTypeToString(ItemType::softDrinks) << endl
         << "4. " << itemTypeToString(ItemType::breakfastSpread) << endl
         << "5. " << itemTypeToString(ItemType::noodles) << endl
         << "6. " << itemTypeToString(ItemType::washing) << endl
         << "7. " << itemTypeToString(ItemType::fruit) << endl
         << "8. " << itemTypeToString(ItemType::vegetables) << endl;
}
