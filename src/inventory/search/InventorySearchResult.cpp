#include "InventorySearchResult.h"
#include "../../item/Item.h"
#include "../../utils/DynamicArray.h"
#include <iomanip>
#include <iostream>

using namespace std;

InventorySearchResult::InventorySearchResult(
    const DynamicArray<Item *> &items) {
    this->items = items;
}

InventorySearchResult::~InventorySearchResult() {
    for (Item *item : items) {
        delete item;
    }
}

const DynamicArray<Item *> &InventorySearchResult::getItems() const {
    return items;
}

ostream &operator<<(ostream &os, const InventorySearchResult &result) {
    os << "Inventory Search Result" << endl
       << string(23, '-') << endl
       << "ID" << '\t' << "Name" << string(50, ' ') << '\t' << "Type"
       << string(16, ' ') << '\t' << "Stock" << '\t' << "Price" << endl;

    for (const Item *item : result.items) {
        cout << item->generateTableRow() << endl;
    }

    return os;
}