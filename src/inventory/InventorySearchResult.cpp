#include "InventorySearchResult.h"
#include "../item/Item.h"
#include <iomanip>
#include <iostream>

using namespace std;

InventorySearchResult::InventorySearchResult(Item **items,
                                             const size_t numItems) {
    this->items = items;
    this->numItems = numItems;
}

InventorySearchResult::~InventorySearchResult() { delete[] items; }

size_t InventorySearchResult::getNumItems() const { return numItems; }

Item **InventorySearchResult::getItems() const { return items; }

ostream &operator<<(ostream &os, const InventorySearchResult &result) {
    os << "Inventory Search Result" << endl
       << string(23, '-') << endl
       << "ID" << '\t' << "Name" << string(50, ' ') << '\t' << "Type"
       << string(16, ' ') << '\t' << "Stock" << '\t' << "Price" << endl;

    for (size_t i = 0; i < result.numItems; ++i) {
        cout << result.items[i]->generateTableRow() << endl;
    }

    return os;
}