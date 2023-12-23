#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "../item/Item.h"
#include "../item/ItemFilterMethod.h"
#include "../item/ItemSortMethod.h"
#include "InventoryBackup.h"
#include "InventorySearchQuery.h"
#include "InventorySearchResult.h"
#include "InventorySheet.h"

using namespace std;

/**
 * The manager of an inventory.
*/
class InventoryManager {
    size_t numItems;
    size_t itemSize;
    Item **items;

    /**
     * Performs a binary insertion sort on an array of items.
     * 
     * @param items The array of items to sort.
     * @param numItems The amount of items in the array.
     * @param sortMethod The method to sort the items for.
    */
    void sortItems(Item **items, const size_t numItems,
                   const ItemSortMethod &sortMethod);

    /**
     * Creates a shallow copy of the items in this manager.
     * 
     * @note
     * The array returned by this method is a dynamically allocated array.
     * Ensure to delete it from the memory after operation.
     */
    Item **shallowCopyItems() const;

    /**
     * Creates a deep copy of the items in this manager.
     * 
     * @note
     * The array returned by this method is a dynamically allocated array.
     * Ensure to delete it from the memory after operation.
    */
    Item **deepCopyItems() const;

    /**
     * Gets the index of an item with an ID using the binary search algorithm.
     * 
     * @param id The ID of the item.
     * @returns The index of the item with the ID. If the item is not found, the method
     * will return the index at which the item with that ID would be entered in.
    */
    size_t getItemIndex(size_t id) const;

  public:
    InventoryManager();
    ~InventoryManager();

    /**
     * Adds an item to this `InventoryManager`.
     * 
     * @param item The item to add.
    */
    void addItem(Item *item);

    /**
     * Removes an item from this `InventoryManager`.
     * 
     * @param id The ID of the item.
     * @returns Whether the item was removed.
    */
    bool removeItem(size_t id);

    /**
     * Searches for the item with the given ID using the binary search algorithm.
     * 
     * @note
     * The binary search algorithm narrows the location of the item by comparing it against the middle
     * item of the given range. If the item is on the left side of the range (`left`), the range will be shrunk
     * to the left side of the array. If the item is on the right side of the range (`right`), the range will be
     * shrunk to the right side of the array. This operation is repeated until the range is invalid
     * (`left > right`) or the item is found.
     * 
     * @param id The ID of the item.
     * @returns The item, `nullptr` if not found.
    */
    Item *getItem(size_t id) const;

    /**
     * The items on this `InventoryManager`.
    */
    Item **getItems() const;

    /**
     * Gets the sorted items on this `InventoryManager`.
     * 
     * @param sortMethod The sort method.
     * 
     * @note
     * The array created from this method is a dynamically allocated array.
     * Ensure to delete it from the memory after operation.
    */
    Item **getItems(const ItemSortMethod &sortMethod);

    /**
     * The amount of items in this `InventoryManager`.
    */
    size_t getNumItems() const;

    /**
     * Searches for items in this `InventoryManager`.
     * 
     * @param query The query to search for.
     * @returns An `InventorySearchResult` containing the search result.
    */
    InventorySearchResult searchItems(const InventorySearchQuery &query);

    /**
     * Performs a backup of the items in this `InventoryManager`.
     * 
     * @returns An `InventoryBackup` containing the backup of this `InventoryManager`'s current state.
    */
    InventoryBackup createBackup() const;

    /**
     * Loads a backup into this `InventoryManager`.
     * 
     * @param backup The backup to load.
     * @returns Whether the backup was successfully loaded.
    */
    bool loadBackup(const InventoryBackup &backup);

    /**
     * Creates an `InventorySheet` of this `InventoryManager`.
     * 
     * @returns An `InventorySheet` representing the current state of this `InventoryManager`.
    */
    InventorySheet createSheet() const;
};

#endif
