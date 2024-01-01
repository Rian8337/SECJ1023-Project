#include "InventoryManager.h"
#include "../item/Item.h"
#include "../item/ItemFilterMethod.h"
#include "../item/ItemSortMethod.h"
#include "../item/ItemType.h"
#include "../utils/StringUtils.h"
#include "InventoryBackup.h"
#include "InventorySearchQuery.h"
#include "InventorySearchResult.h"
#include "InventorySheet.h"
#include <cstring>
#include <stdexcept>
#include <string>

using namespace std;

void InventoryManager::sortItems(DynamicArray<Item *> &items,
                                 const ItemSortMethod &sortMethod) {

    /**
     * Searches the location where an item should belong using the binary search algorithm.
     * 
     * @note
     * The binary search algorithm narrows the location of the item by comparing it against the middle
     * item of the given range. If the item is on the left side of the range (`left`), the range will be shrunk
     * to the left side of the array. If the item is on the right side of the range (`right`), the range will be
     * shrunk to the right side of the array. This operation is repeated until the range becomes invalid
     * (`left > right`) or the supposed location of the item is found.
     * 
     * @param item The item to search the location for.
     * @param left The leftmost position in the array in which the search will be performed.
     * @param right The rightmost position in the array in which the search will be performed.
     * @returns The supposed location of the item.
    */
    auto binarySearch = [&](const Item *item, size_t left, size_t right) {
        while (left <= right) {
            // Get the middle point of the current range.
            const size_t mid = left + (right - left) / 2;
            const Item *midItem = items[mid];

            // Legend:
            // - `0` = item is equal
            // - `>0` = item is on the left
            // - `<0` = item is on the right
            int comparison = 0;

            switch (sortMethod) {
            case ItemSortMethod::sortByName:
                // Sort name by case-insensitive strcmp result.
                comparison = strcmp(
                    StringUtils::tolower(item->getIdentifier()->getName())
                        .data(),
                    StringUtils::tolower(midItem->getIdentifier()->getName())
                        .data());

                break;
            case ItemSortMethod::sortByPriceSmallestToHighest:
            case ItemSortMethod::sortByPriceHighestToSmallest:
                if (item->getPrice() == midItem->getPrice()) {
                    comparison = 0;
                } else if (item->getPrice() > midItem->getPrice()) {
                    comparison = 1;
                } else {
                    comparison = -1;
                }

                break;
            case ItemSortMethod::sortByStockSmallestToHighest:
            case ItemSortMethod::sortByStockHighestToSmallest:
                if (item->getStock() == midItem->getStock()) {
                    comparison = 0;
                } else if (item->getStock() > midItem->getStock()) {
                    comparison = 1;
                } else {
                    comparison = -1;
                }

                break;
            default:
                if (*item == *midItem) {
                    comparison = 0;
                } else if (*item > *midItem) {
                    comparison = 1;
                } else {
                    comparison = -1;
                }
            }

            if (comparison == 0) {
                // "Same" item is found, return the next index for insertion.
                return mid + 1;
            } else if (comparison > 0) {
                // The item should be on the right side of the array, move towards it.
                left = mid + 1;
            } else {
                // 0 - 1 on an unsigned number will cause an underflow, so we need to avoid that.
                // This can happen when the array size is 1.
                if (mid == 0) {
                    return mid + 1;
                }

                // The item should be on the left side of the array, move towards it.
                right = mid - 1;
            }
        }

        return left;
    };

    for (size_t i = 1; i < items.size(); ++i) {
        size_t j = i - 1;
        Item *selected = items[i];

        size_t idx = binarySearch(selected, 0, j);

        // Move all elements after the index to create space for the selected index.
        while (j >= idx) {
            items[j + 1] = items[j];
            j--;
        }

        items[j + 1] = selected;
    }

    if (sortMethod == ItemSortMethod::sortByPriceHighestToSmallest ||
        sortMethod == ItemSortMethod::sortByStockHighestToSmallest) {
        items.reverse();
    }
}

DynamicArray<Item *> InventoryManager::copyItems(const bool deep) const {
    DynamicArray<Item *> items = DynamicArray<Item *>(this->items.size());

    for (Item *item : this->items) {
        items.append(deep ? new Item(*item) : item);
    }

    return items;
}

size_t InventoryManager::getItemIndex(size_t id) const {
    if (items.empty()) {
        return 0;
    }

    size_t left = 0;
    size_t right = items.size() - 1;

    while (left <= right) {
        // Get the middle point of the current range.
        const size_t mid = left + (right - left) / 2;
        size_t midId = items[mid]->getIdentifier()->getID();

        if (id == midId) {
            return mid;
        } else if (id > midId) {
            left = mid + 1;
        } else {
            // 0 - 1 on an unsigned number will cause an underflow, so we need to avoid that.
            if (mid == 0) {
                return mid;
            }

            right = mid - 1;
        }
    }

    return left;
}

InventoryManager::InventoryManager() { items = DynamicArray<Item *>(10); }

InventoryManager::~InventoryManager() {
    for (const Item *item : items) {
        delete item;
    }
}

void InventoryManager::addItem(Item *item) {
    // Make sure that the item does not exist.
    size_t idx = getItemIndex(item->getIdentifier()->getID());

    if (!items.empty() && idx < items.size() - 1 &&
        items[idx]->getIdentifier()->getID() ==
            item->getIdentifier()->getID()) {
        return;
    }

    items.add(item, idx);
}

bool InventoryManager::removeItem(size_t id) {
    if (items.empty()) {
        return false;
    }

    size_t idx = getItemIndex(id);

    // Make sure that the item is what we actually want to remove.
    if (idx > items.size() - 1 || items[idx]->getIdentifier()->getID() != id) {
        return false;
    }

    items.remove(idx);

    return true;
}

Item *InventoryManager::getItem(size_t id) const {
    size_t idx = getItemIndex(id);

    if (idx > items.size() - 1 || items[idx]->getIdentifier()->getID() != id) {
        return nullptr;
    }

    return items[idx];
}

const DynamicArray<Item *> &InventoryManager::getItems() const { return items; }

const DynamicArray<Item *>
InventoryManager::getItems(const ItemSortMethod &sortMethod) {
    DynamicArray<Item *> items = copyItems(false);

    sortItems(items, sortMethod);

    return items;
}

InventorySearchResult
InventoryManager::searchItems(const InventorySearchQuery &query) {
    DynamicArray<Item *> items = DynamicArray<Item *>(this->items.size());

    // Apply the filter first and then sort, otherwise the sort operation may be more expensive.
    for (Item *item : this->items) {
        bool insert = true;

        if (!query.getQuery().empty()) {
            switch (query.getFilterMethod()) {
            case ItemFilterMethod::filterByName:
                insert = item->getIdentifier()->getName().find(
                             query.getQuery()) != string::npos;
                break;
            case ItemFilterMethod::filterByDescription:
                insert = item->getIdentifier()->getDescription().find(
                             query.getQuery()) != string::npos;
                break;
            }
        }

        if (!query.getItemTypes().empty()) {
            insert = false;

            for (size_t j = 0; j < query.getItemTypes().size() && !insert;
                 ++j) {
                if (query.getItemTypes()[j] ==
                    item->getIdentifier()->getType()) {
                    insert = true;
                }
            }
        }

        if (insert) {
            items.append(item);
        }
    }

    sortItems(items, query.getSortMethod());

    return InventorySearchResult(items);
}

bool InventoryManager::loadBackup(const InventoryBackup &backup) {
    for (Item *item : backup.getItems()) {
        addItem(new Item(*item));
    }

    return true;
}

InventoryBackup InventoryManager::createBackup() const {
    return InventoryBackup(copyItems(true));
}

InventorySheet InventoryManager::createSheet() const {
    return InventorySheet(copyItems(true));
}
