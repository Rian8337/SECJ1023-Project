#ifndef KITCHENWARE_ITEM_H
#define KITCHENWARE_ITEM_H

#include "Item.h"
#include <string>

/**
 * Represents a kitchenware item.
*/
class KitchenwareItem : public Item {
    string material;

  protected:
    /**
     * Returns an output of this `KitchenwareItem` to the console.
    */
    string outputToConsole() const override;

    /**
     * Populates this `KitchenwareItem` with data from user input.
    */
    void inputData() override;

  public:
    KitchenwareItem();
    KitchenwareItem(size_t id);
    KitchenwareItem(const string &name, const string &description, size_t stock,
                    float price, const string &material);
    KitchenwareItem(const KitchenwareItem &copy);
    KitchenwareItem(KitchenwareItem &&other);

    /**
     * The material of this `KitchenwareItem`.
    */
    string getMaterial() const;

    /**
     * The material of this `KitchenwareItem`.
    */
    void setMaterial(const string &material);

    /**
     * Deep clones this `KitchenwareItem`.
    */
    KitchenwareItem *deepClone() const override;

    KitchenwareItem &operator=(const KitchenwareItem &right);
    KitchenwareItem &operator=(KitchenwareItem &&right);
};

#endif