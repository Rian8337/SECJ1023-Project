#include "InventorySearchQuery.h"
#include "../item/ItemFilterMethod.h"
#include "../item/ItemSortMethod.h"
#include "../item/ItemType.h"
#include "../utils/ArrayUtils.h"
#include <iostream>
#include <string>

using namespace ArrayUtils;
using namespace std;

InventorySearchQuery::InventorySearchQuery() {
    query = "";
    sortMethod = ItemSortMethod::sortById;
    filterMethod = ItemFilterMethod::filterByName;
    itemTypesSize = 5;
    numItemTypes = 0;
    itemTypes = new ItemType[itemTypesSize];
}

InventorySearchQuery::~InventorySearchQuery() { delete[] itemTypes; }

string InventorySearchQuery::getQuery() const { return query; }
void InventorySearchQuery::setQuery(string query) { this->query = query; }

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

ItemType *InventorySearchQuery::getItemTypes() const { return itemTypes; }

void InventorySearchQuery::addItemType(const ItemType itemType) {
    addElement(itemTypes, itemType, numItemTypes, itemTypesSize, true);
}

void InventorySearchQuery::removeItemType(const ItemType itemType) {
    removeElement(itemTypes, itemType, numItemTypes);
}

void InventorySearchQuery::emptyItemTypes() {
    // We have no way to "remove elements from an array" other than setting
    // the counter to 0 to make it seem like the elements were removed.
    numItemTypes = 0;
}

size_t InventorySearchQuery::getNumItemTypes() const { return numItemTypes; }

ostream &operator<<(ostream &os, const InventorySearchQuery &query) {
    os << "Inventory Search Information" << endl
       << string(28, '-') << endl
       << "Search term: " << (!query.query.empty() ? query.query : "None")
       << endl
       << "Sort by: " << itemSortMethodToString(query.sortMethod) << endl
       << "Filter by: " << itemFilterMethodToString(query.filterMethod) << endl
       << "Included item types: ";

    if (query.numItemTypes > 0) {
        os << itemTypeToString(query.itemTypes[0]);

        for (size_t i = 1; i < query.numItemTypes; ++i) {
            os << ", " << itemTypeToString(query.itemTypes[i]);
        }
    } else {
        os << "All";
    }

    os << endl;

    return os;
}