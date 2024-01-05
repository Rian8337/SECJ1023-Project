#ifndef BREAKFAST_SPREAD_ITEM_H
#define BREAKFAST_SPREAD_ITEM_H

#include "FoodItem.h"
#include <string>

using namespace std;

/**
 * Represents a breakfast spread item.
*/
class BreakfastSpreadItem : public FoodItem {
  public:
    BreakfastSpreadItem();
    BreakfastSpreadItem(size_t id);
    BreakfastSpreadItem(const string &name, const string &description,
                        size_t stock, float price, float calories);
    BreakfastSpreadItem(const BreakfastSpreadItem &copy);
    BreakfastSpreadItem(BreakfastSpreadItem &&other);

    /**
     * Deep clones this `BreakfastSpreadItem`.
    */
    BreakfastSpreadItem *deepClone() const override;

    BreakfastSpreadItem &operator=(const BreakfastSpreadItem &right);
    BreakfastSpreadItem &operator=(BreakfastSpreadItem &&right);
};

#endif
