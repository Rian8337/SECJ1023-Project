#include "InventorySearchQuery.h"
#include "../item/ItemFilterMethod.h"
#include "../item/ItemSortMethod.h"
#include "../item/ItemType.h"
#include "../utils/DynamicArray.h"
#include <iostream>
#include <string>

using namespace std;

InventorySearchQuery::InventorySearchQuery() {
    query = "";
    sortMethod = ItemSortMethod::sortById;
    filterMethod = ItemFilterMethod::filterByName;
    itemTypes = DynamicArray<ItemType>(5);
}

string InventorySearchQuery::getQuery() const { return query; }
void InventorySearchQuery::setQuery(const string &query) {
    this->query = query;
}

ItemSortMethod InventorySearchQuery::getSortMethod() const {
    return sortMethod;
}
void InventorySearchQuery::setSortMethod(ItemSortMethod sortMethod) {
    this->sortMethod = sortMethod;
}

ItemFilterMethod InventorySearchQuery::getFilterMethod() const {
    return filterMethod;
}
void InventorySearchQuery::setFilterMethod(ItemFilterMethod filterMethod) {
    this->filterMethod = filterMethod;
}

const DynamicArray<ItemType> &InventorySearchQuery::getItemTypes() const {
    return itemTypes;
}

void InventorySearchQuery::addItemType(const ItemType itemType) {
    if (itemTypes.has(itemType)) {
        return;
    }

    itemTypes.append(itemType);
}

void InventorySearchQuery::removeItemType(const ItemType itemType) {
    itemTypes.remove(itemType);
}

void InventorySearchQuery::emptyItemTypes() { itemTypes.clear(); }

ostream &operator<<(ostream &os, const InventorySearchQuery &query) {
    os << "Inventory Search Information" << endl
       << string(28, '-') << endl
       << "Search term: " << (!query.query.empty() ? query.query : "None")
       << endl
       << "Sort by: " << itemSortMethodToString(query.sortMethod) << endl
       << "Filter by: " << itemFilterMethodToString(query.filterMethod) << endl
       << "Included item types: ";

    if (query.itemTypes.size() > 0) {
        os << itemTypeToString(query.itemTypes[0]);

        for (size_t i = 1; i < query.itemTypes.size(); ++i) {
            os << ", " << itemTypeToString(query.itemTypes[i]);
        }
    } else {
        os << "All";
    }

    os << endl;

    return os;
}
