#ifndef INVENTORY_SHEET_H
#define INVENTORY_SHEET_H

#include "../item/Item.h"
#include <ctime>

using namespace std;

/**
 * Represents an inventory sheet containing the state of an `InventoryManager` when it was created.
*/
class InventorySheet {
    time_t creationDate;
    size_t numItems;
    Item **items;

  public:
    InventorySheet(Item **items, const size_t numItems);
    ~InventorySheet();

    /**
     * The time at which this `InventorySheet` was created.
    */
    time_t getCreationDate() const;

    /**
     * The amount of items in this `InventorySheet`.
    */
    size_t getNumItems() const;

    /**
     * The items in this `InventorySheet`.
    */
    Item **getItems() const;

    friend ostream &operator<<(ostream &os, const InventorySheet &sheet);
};

#endif
