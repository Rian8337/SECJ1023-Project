#ifndef ITEM_WITH_WEIGHT_H
#define ITEM_WITH_WEIGHT_H

#include <string>

using namespace std;

/**
 * Represents an `Item` that has a weight.
*/
class ItemWithWeight {
  protected:
    float weight;

    /**
     * Returns an output of this `Item` to the console.
    */
    string outputToConsole() const;

    /**
     * Populates this `Item` with data from user input.
    */
    void inputData();

  public:
    ItemWithWeight(float weight = 0);
    ItemWithWeight(const ItemWithWeight &copy);
    ItemWithWeight(ItemWithWeight &&other);

    /**
     * The weight of this `Item` in g.
    */
    float getWeight() const;

    /**
     * The weight of this `Item` in g.
    */
    void setWeight(float weight);

    ItemWithWeight &operator=(const ItemWithWeight &right);
    ItemWithWeight &operator=(ItemWithWeight &&right);
};

#endif
