#ifndef FRUIT_ITEM_H
#define FRUIT_ITEM_H

#include "FoodItem.h"
#include "ItemWithWeight.h"
#include <string>

using namespace std;

/**
 * Represents a fruit item.
*/
class FruitItem : public FoodItem, public ItemWithWeight {
  protected:
    /**
     * Returns an output of this `FruitItem` to the console.
    */
    string outputToConsole() const override;

    /**
     * Populates this `FruitItem` with data from user input.
    */
    void inputData() override;

  public:
    FruitItem();
    FruitItem(size_t id);
    FruitItem(const string &name, const string &description, size_t stock,
              float price, float calories, float weight);
    FruitItem(const FruitItem &copy);
    FruitItem(FruitItem &&other);

    /**
     * Deep clones this `FruitItem`.
    */
    FruitItem *deepClone() const override;

    FruitItem &operator=(const FruitItem &right);
    FruitItem &operator=(FruitItem &&right);
};

#endif
