#ifndef INVENTORY_SHEET_H
#define INVENTORY_SHEET_H

#include "../item/Item.h"
#include "../utils/DynamicArray.h"
#include <ctime>

using namespace std;

/**
 * Represents an inventory sheet containing the state of an `InventoryManager` when it was created.
*/
class InventorySheet {
    time_t creationDate;
    DynamicArray<Item *> items;

  public:
    InventorySheet(const DynamicArray<Item *> &items);
    ~InventorySheet();

    /**
     * The time at which this `InventorySheet` was created.
    */
    time_t getCreationDate() const;

    /**
     * The items in this `InventorySheet`.
    */
    const DynamicArray<Item *> &getItems() const;

    friend ostream &operator<<(ostream &os, const InventorySheet &sheet);
};

#endif
