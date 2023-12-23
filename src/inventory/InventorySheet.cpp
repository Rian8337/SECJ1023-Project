#include "InventorySheet.h"
#include "../item/Item.h"
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

InventorySheet::InventorySheet(Item **items, const size_t numItems) {
    creationDate = time(0);

    this->items = items;
    this->numItems = numItems;
}

InventorySheet::~InventorySheet() {
    for (size_t i = 0; i < numItems; ++i) {
        delete items[i];
    }

    delete[] items;
}

time_t InventorySheet::getCreationDate() const { return creationDate; }
size_t InventorySheet::getNumItems() const { return numItems; }
Item **InventorySheet::getItems() const { return items; }

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

    for (size_t i = 0; i < sheet.numItems; ++i) {
        os << sheet.items[i]->generateTableRow() << endl;
    }

    return os;
}
