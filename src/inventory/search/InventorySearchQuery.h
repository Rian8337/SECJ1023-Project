#ifndef INVENTORY_SEARCH_QUERY_H
#define INVENTORY_SEARCH_QUERY_H

#include "../../item/ItemType.h"
#include "../../utils/DynamicArray.h"
#include "ItemFilterMethod.h"
#include "ItemSortMethod.h"
#include <string>

using namespace std;

/**
* Utility class for querying an `InventoryManager`.
*/
class InventorySearchQuery {
    string query;
    ItemSortMethod sortMethod;
    ItemFilterMethod filterMethod;
    DynamicArray<ItemType> itemTypes;

  public:
    InventorySearchQuery();

    /**
     * The query of this `InventorySearchQuery`.
    */
    string getQuery() const;

    /**
     * The query of this `InventorySearchQuery`.
    */
    void setQuery(const string &query);

    /**
     * The sorting method of this `InventorySearchQuery`.
    */
    ItemSortMethod getSortMethod() const;

    /**
     * The sorting method of this `InventorySearchQuery`.
    */
    void setSortMethod(ItemSortMethod sortMethod);

    /**
     * The filtering method of this `InventorySearchQuery`.
    */
    ItemFilterMethod getFilterMethod() const;

    /**
     * The filtering method of this `InventorySearchQuery`.
    */
    void setFilterMethod(ItemFilterMethod filterMethod);

    /**
     * The types of items to be included in the result.
    */
    const DynamicArray<ItemType> &getItemTypes() const;

    /**
     * Adds an item type to be included in the result.
     * 
     * @param itemType The type of item.
    */
    void addItemType(const ItemType itemType);

    /**
     * Removes an item type from being included in the result.
     * 
     * @param itemType The type of the item.
    */
    void removeItemType(const ItemType itemType);

    /**
     * Removes all item types filter.
    */
    void emptyItemTypes();

    friend ostream &operator<<(ostream &os, const InventorySearchQuery &query);
};

#endif
