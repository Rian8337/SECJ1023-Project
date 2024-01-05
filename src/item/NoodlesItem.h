#ifndef NOODLES_ITEM_H
#define NOODLES_ITEM_H

#include "FoodItem.h"
#include "ItemWithWeight.h"
#include <string>

using namespace std;

/**
 * Represents a noodles item.
*/
class NoodlesItem : public FoodItem, public ItemWithWeight {
  protected:
    /**
     * Returns an output of this `NoodlesItem` to the console.
    */
    string outputToConsole() const override;

    /**
     * Populates this `NoodlesItem` with data from user input.
    */
    void inputData() override;

  public:
    NoodlesItem();
    NoodlesItem(size_t id);
    NoodlesItem(const string &name, const string &description, size_t stock,
                float price, float calories, float weight);
    NoodlesItem(const NoodlesItem &copy);
    NoodlesItem(NoodlesItem &&other);

    /**
     * Deep clones this `NoodlesItem`.
    */
    NoodlesItem *deepClone() const override;

    NoodlesItem &operator=(const NoodlesItem &right);
    NoodlesItem &operator=(NoodlesItem &&right);
};

#endif
