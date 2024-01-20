#include "ItemSortMethod.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

ItemSortMethod parseSortMethod(short num) {
    switch (num) {
    case ItemSortMethod::sortById:
        return ItemSortMethod::sortById;
    case ItemSortMethod::sortByName:
        return ItemSortMethod::sortByName;
    case ItemSortMethod::sortByPriceSmallestToHighest:
        return ItemSortMethod::sortByPriceSmallestToHighest;
    case ItemSortMethod::sortByPriceHighestToSmallest:
        return ItemSortMethod::sortByPriceHighestToSmallest;
    case ItemSortMethod::sortByStockSmallestToHighest:
        return ItemSortMethod::sortByStockSmallestToHighest;
    case ItemSortMethod::sortByStockHighestToSmallest:
        return ItemSortMethod::sortByStockHighestToSmallest;
    default:
        throw invalid_argument(
            "Unable to parse the number into an ItemSortMethod.");
    }
}

string itemSortMethodToString(const ItemSortMethod &sortMethod) {
    switch (sortMethod) {
    case ItemSortMethod::sortById:
        return "ID";
    case ItemSortMethod::sortByName:
        return "Name";
    case ItemSortMethod::sortByPriceSmallestToHighest:
        return "Price (smallest to highest)";
    case ItemSortMethod::sortByPriceHighestToSmallest:
        return "Price (highest to smallest)";
    case ItemSortMethod::sortByStockSmallestToHighest:
        return "Stock (smallest to highest)";
    case ItemSortMethod::sortByStockHighestToSmallest:
        return "Stock (highest to smallest)";
    default:
        throw invalid_argument(
            "Unable to convert the sorting method to a string.");
    }
}

void listSortMethods() {
    cout << "Available item sorting methods:" << endl
         << "1. " << itemSortMethodToString(ItemSortMethod::sortById) << endl
         << "2. " << itemSortMethodToString(ItemSortMethod::sortByName) << endl
         << "3. "
         << itemSortMethodToString(ItemSortMethod::sortByPriceSmallestToHighest)
         << endl
         << "4. "
         << itemSortMethodToString(ItemSortMethod::sortByPriceHighestToSmallest)
         << endl
         << "5. "
         << itemSortMethodToString(ItemSortMethod::sortByStockSmallestToHighest)
         << endl
         << "6. "
         << itemSortMethodToString(ItemSortMethod::sortByStockHighestToSmallest)
         << endl;
}
