#ifndef FOOD_ITEM_H
#define FOOD_ITEM_H

#include "Item.h"
#include "ItemType.h"
#include "ItemWithVolume.h"
#include <iostream>

/**
 * Represents a food item.
*/
class FoodItem : public Item {
    float calories;

  protected:
    /**
     * Returns an output of this `FoodItem` to the console.
    */
    string outputToConsole() const override;

    /**
     * Populates this `FoodItem` with data from user input.
    */
    void inputData() override;

    FoodItem(ItemType type = ItemType::none);
    FoodItem(size_t id, ItemType type);
    FoodItem(const string &name, const string &description, ItemType type,
             size_t stock, float price, float calories);
    FoodItem(const FoodItem &copy);
    FoodItem(FoodItem &&other);

  public:
    /**
     * The calories of this `FoodItem`.
    */
    float getCalories() const;

    /**
     * The calories of this `FoodItem`.
    */
    void setCalories(float calories);

    /**
     * Deep clones this `FoodItem`.
    */
    FoodItem *deepClone() const override;

    FoodItem &operator=(const FoodItem &right);
    FoodItem &operator=(FoodItem &&right);
};

#endif