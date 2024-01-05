#ifndef COSMETIC_ITEM_H
#define COSMETIC_ITEM_H

#include "Item.h"
#include <string>

using namespace std;

/**
 * Represents a cosmetic item.
*/
class CosmeticItem : public Item {
  public:
    CosmeticItem();
    CosmeticItem(size_t id);
    CosmeticItem(const string &name, const string &description, size_t stock,
                 float price);
    CosmeticItem(const CosmeticItem &copy);
    CosmeticItem(CosmeticItem &&other);

    /**
     * Deep clones this `CosmeticItem`.
    */
    CosmeticItem *deepClone() const override;

    CosmeticItem &operator=(const CosmeticItem &right);
    CosmeticItem &operator=(CosmeticItem &&right);
};

#endif
