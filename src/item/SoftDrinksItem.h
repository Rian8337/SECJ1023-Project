#ifndef SOFT_DRINKS_ITEM_H
#define SOFT_DRINKS_ITEM_H

#include "FoodItem.h"
#include "ItemWithVolume.h"
#include <string>

using namespace std;

/**
 * Represents a soft drinks item.
*/
class SoftDrinksItem : public FoodItem, public ItemWithVolume {
  protected:
    /**
     * Returns an output of this `SoftDrinksItem` to the console.
    */
    string outputToConsole() const override;

    /**
     * Populates this `SoftDrinksItem` with data from user input.
    */
    void inputData() override;

  public:
    SoftDrinksItem();
    SoftDrinksItem(size_t id);
    SoftDrinksItem(const string &name, const string &description, size_t stock,
                   float price, float calories, float volume);
    SoftDrinksItem(const SoftDrinksItem &copy);
    SoftDrinksItem(SoftDrinksItem &&other);

    /**
     * Deep clones this `SoftDrinksItem`.
    */
    SoftDrinksItem *deepClone() const override;

    SoftDrinksItem &operator=(const SoftDrinksItem &right);
    SoftDrinksItem &operator=(SoftDrinksItem &&right);
};

#endif
