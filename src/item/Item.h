#ifndef ITEM_TYPE_H
#define ITEM_H

#include "ItemIdentifier.h"
#include <string>

using namespace std;

/**
 * Represents an item.
*/
class Item {
    ItemIdentifier *identifier;
    size_t stock;
    float price;

  public:
    Item();
    Item(size_t id);
    Item(const string &name, const string &description, ItemType type,
         size_t stock, float price);
    Item(const Item &copy);
    Item(Item &&other);

    ~Item();

    /**
     * The identifier of this `Item`.
    */
    ItemIdentifier *getIdentifier() const;

    /**
     * The available stock of this `Item`.
    */
    size_t getStock() const;

    /**
     * The available stock of this `Item`.
    */
    void setStock(long stock);

    /**
     * The price of this `Item`.
    */
    float getPrice() const;

    /**
     * The price of this `Item`.
    */
    void setPrice(float price);

    /**
     * Generates a table row of this `Item`.
    */
    string generateTableRow() const;

    bool operator==(const Item &right) const;
    bool operator!=(const Item &right) const;
    bool operator<(const Item &right) const;
    bool operator>(const Item &right) const;
    Item &operator=(const Item &right);
    Item &operator=(Item &&right);
    friend ostream &operator<<(ostream &os, const Item &item);
    friend istream &operator>>(istream &is, Item &item);
};

#endif
