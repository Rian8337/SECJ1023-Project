#ifndef INVENTORY_SEARCH_RESULT_H
#define INVENTORY_SEARCH_RESULT_H

#include "../item/Item.h"
#include "../utils/DynamicArray.h"

using namespace std;

/**
 * Represents the search result of an `InventoryManager`.
*/
class InventorySearchResult {
    DynamicArray<Item *> items;

  public:
    InventorySearchResult(const DynamicArray<Item *> &items);
    ~InventorySearchResult();

    /**
     * The items in this `InventorySearchResult`.
    */
    const DynamicArray<Item *> &getItems() const;

    friend ostream &operator<<(ostream &os,
                               const InventorySearchResult &result);
};

#endif
