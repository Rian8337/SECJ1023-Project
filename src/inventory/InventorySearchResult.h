#ifndef INVENTORY_SEARCH_RESULT_H
#define INVENTORY_SEARCH_RESULT_H

#include "../item/Item.h"

using namespace std;

/**
 * Represents the search result of an `InventoryManager`.
*/
class InventorySearchResult {
    size_t numItems;
    Item **items;

  public:
    InventorySearchResult(Item **items, const size_t numItems);

    ~InventorySearchResult();

    /**
     * The amount of items in this `InventorySearchResult`.
    */
    size_t getNumItems() const;

    /**
     * The items in this `InventorySearchResult`.
    */
    Item **getItems() const;

    friend ostream &operator<<(ostream &os,
                               const InventorySearchResult &result);
};

#endif
