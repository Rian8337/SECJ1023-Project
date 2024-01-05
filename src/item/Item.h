#ifndef ITEM_H
#define ITEM_H

#include "ItemIdentifier.h"
#include <string>

using namespace std;

/**
 * Represents an item.
*/
class Item {
  protected:
    ItemIdentifier *identifier;
    size_t stock;
    float price;

    /**
     * Returns an output of this `Item` to the console.
    */
    virtual string outputToConsole() const;

    /**
     * Populates this `Item` with data from user input.
    */
    virtual void inputData();

    Item(ItemType type = ItemType::none);
    Item(size_t id, ItemType type);
    Item(const string &name, const string &description, ItemType type,
         size_t stock, float price);
    Item(const Item &copy);
    Item(Item &&other);

  public:
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

    /**
     * Deep clones this `Item`.
    */
    virtual Item *deepClone() const = 0;

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
