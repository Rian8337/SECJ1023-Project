#ifndef VEGETABLE_ITEM_H
#define VEGETABLE_ITEM_H

#include "FoodItem.h"
#include "ItemWithWeight.h"

using namespace std;

/**
 * Represents a vegetable item.
*/
class VegetableItem : public FoodItem, public ItemWithWeight {
  protected:
    /**
     * Returns an output of this `VegetableItem` to the console.
    */
    string outputToConsole() const override;

    /**
     * Populates this `VegetableItem` with data from user input.
    */
    void inputData() override;

  public:
    VegetableItem();
    VegetableItem(size_t id);
    VegetableItem(const string &name, const string &description, size_t stock,
                  float price, float calories, float weight);
    VegetableItem(const VegetableItem &copy);
    VegetableItem(VegetableItem &&other);

    /**
     * Deep clones this `VegetableItem`.
    */
    VegetableItem *deepClone() const override;

    VegetableItem &operator=(const VegetableItem &right);
    VegetableItem &operator=(VegetableItem &&right);
};

#endif
