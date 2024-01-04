#include "ItemFilterMethod.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

ItemFilterMethod parseFilterMethod(const short num) {
    switch (num) {
    case ItemFilterMethod::filterByName:
        return ItemFilterMethod::filterByName;
    case ItemFilterMethod::filterByDescription:
        return ItemFilterMethod::filterByDescription;
    default:
        throw invalid_argument(
            "Unable to parse the number into an ItemFilterMethod.");
    }
}

string itemFilterMethodToString(const ItemFilterMethod &filterMethod) {
    switch (filterMethod) {
    case ItemFilterMethod::filterByName:
        return "Name";
    case ItemFilterMethod::filterByDescription:
        return "Description";
    default:
        throw invalid_argument(
            "Unable to convert the filter method to a string.");
    }
}

void listFilterMethods() {
    cout << "Available item filtering methods:" << endl
         << "1. " << itemFilterMethodToString(ItemFilterMethod::filterByName)
         << endl
         << "2. "
         << itemFilterMethodToString(ItemFilterMethod::filterByDescription)
         << endl;
}
