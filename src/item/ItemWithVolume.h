#ifndef ITEM_WITH_VOLUME_H
#define ITEM_WITH_VOLUME_H

#include <string>

using namespace std;

/**
 * Represents an `Item` that has a volume.
*/
class ItemWithVolume {
  protected:
    float volume;

    /**
     * Returns an output of this `Item` to the console.
    */
    string outputToConsole() const;

    /**
     * Populates this `Item` with data from user input.
    */
    void inputData();

  public:
    ItemWithVolume(float volume = 0);
    ItemWithVolume(const ItemWithVolume &copy);
    ItemWithVolume(ItemWithVolume &&other);

    /**
     * The volume of this `Item` in mL.
    */
    float getVolume() const;

    /**
     * The volume of this `Item` in mL.
    */
    void setVolume(float volume);

    ItemWithVolume &operator=(const ItemWithVolume &right);
    ItemWithVolume &operator=(ItemWithVolume &&right);
};

#endif
