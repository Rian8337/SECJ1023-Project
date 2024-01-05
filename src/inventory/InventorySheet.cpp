#include "InventorySheet.h"
#include "../item/Item.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

InventorySheet::InventorySheet(const DynamicArray<Item *> &items) {
    creationDate = time(0);

    this->items = items;
}

InventorySheet::~InventorySheet() {
    for (Item *item : items) {
        delete item;
    }
}

time_t InventorySheet::getCreationDate() const { return creationDate; }
const DynamicArray<Item *> &InventorySheet::getItems() const { return items; }

ostream &operator<<(ostream &os, const InventorySheet &sheet) {
    string dateStr(asctime(gmtime(&sheet.creationDate)));

    // Remove the newline character.
    dateStr.pop_back();

    // In Windows, \r may also be present.
    if (dateStr.back() == '\r') {
        dateStr.pop_back();
    }

    os << "Inventory report as of " << dateStr << " UTC" << endl
       << endl
       << "ID" << '\t' << "Name" << string(50, ' ') << '\t' << "Type"
       << string(16, ' ') << '\t' << "Stock" << '\t' << "Price (RM)" << endl;

    for (const Item *item : sheet.items) {
        os << item->generateTableRow() << endl;
    }

    return os;
}
