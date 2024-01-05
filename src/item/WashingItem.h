#ifndef WASHING_ITEM_H
#define WASHING_ITEM_H

#include "Item.h"
#include <string>

using namespace std;

/**
 * Represents a washing item.
*/
class WashingItem : public Item {
  public:
    WashingItem();
    WashingItem(size_t id);
    WashingItem(const string &name, const string &description, size_t stock,
                float price);
    WashingItem(const WashingItem &copy);
    WashingItem(WashingItem &&other);

    /**
     * Deep clones this `WashingItem`.
    */
    WashingItem *deepClone() const override;

    WashingItem &operator=(const WashingItem &right);
    WashingItem &operator=(WashingItem &&right);
};

#endif
