#ifndef INVENTORY_SEARCH_QUERY_H
#define INVENTORY_SEARCH_QUERY_H

#include "../item/ItemFilterMethod.h"
#include "../item/ItemSortMethod.h"
#include "../item/ItemType.h"
#include <string>

using namespace std;

/**
* Utility class for querying an `InventoryManager`.
*/
class InventorySearchQuery {
    string query;
    ItemSortMethod sortMethod;
    ItemFilterMethod filterMethod;

    ItemType *itemTypes;
    size_t itemTypesSize;
    size_t numItemTypes;

  public:
    InventorySearchQuery();
    ~InventorySearchQuery();

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
    ItemType *getItemTypes() const;

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

    /**
     * The amount of item types to be included in the result.
    */
    size_t getNumItemTypes() const;

    friend ostream &operator<<(ostream &os, const InventorySearchQuery &query);
};

#endif