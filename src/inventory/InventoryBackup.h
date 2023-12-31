#ifndef INVENTORY_BACKUP_H
#define INVENTORY_BACKUP_H

#include "../item/Item.h"
#include "../item/ItemIdentifier.h"
#include "../utils/DynamicArray.h"
#include <ctime>
#include <string>

using namespace std;

/**
 * Represents the backup of an `InventoryManager`.
*/
class InventoryBackup {
    time_t creationDate;
    DynamicArray<Item *> items;

  public:
    InventoryBackup(const DynamicArray<Item *> &items);
    ~InventoryBackup();

    /**
     * Reads a backup from a file.
     * 
     * @param fileName The name of the file.
     * @returns An `InventoryBackup` generated from the file.
    */
    static InventoryBackup readBackup(const string &fileName);

    /**
     * The time at which this `InventoryBackup` was created.
    */
    time_t getCreationDate() const;

    /**
     * The items in this `InventoryBackup`.
    */
    const DynamicArray<Item *> &getItems() const;

    /**
     * The filename of this `InventoryBackup` were it to be saved.
    */
    string getFilename() const;

    /**
     * Saves this `InventoryBackup` to a file.
     * 
     * @returns Whether the operation succeeded.
    */
    bool saveToFile();

    friend ostream &operator<<(ostream &out, const InventoryBackup &backup);
};

#endif
