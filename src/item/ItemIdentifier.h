#ifndef ITEM_IDENTIFIER_H
#define ITEM_IDENTIFIER_H

#include "ItemType.h"
#include <string>

using namespace std;

/**
 * A data class for identifying an `Item`.
*/
class ItemIdentifier {
  private:
    static size_t incrementalId;

    size_t id;
    string name;
    string description;
    ItemType type;

    ItemIdentifier(size_t id, ItemType type);

  public:
    ItemIdentifier(ItemType type = ItemType::none);
    ItemIdentifier(const string &name, const string &description,
                   ItemType type);
    ItemIdentifier(const ItemIdentifier &copy);
    ItemIdentifier(ItemIdentifier &&other);

    /**
     * Resets the incremental ID to the given ID.
     * 
     * @param id The ID to reset to. Defaults to 0.
    */
    static void resetIncrementalId(size_t id = 0);

    /**
     * The ID of the `Item` holding this `ItemIdentifier`.
    */
    size_t getID() const;

    /**
     * The ID of the `Item` holding this `ItemIdentifier`.
    */
    void setID(size_t id);

    /**
     * The name of the `Item` holding this `ItemIdentifier`.
    */
    string getName() const;

    /**
     * The name of the `Item` holding this `ItemIdentifier`.
    */
    void setName(const string &name);

    /**
     * The description of the `Item` holding this `ItemIdentifier`.
    */
    string getDescription() const;

    /**
     * The description of the `Item` holding this `ItemIdentifier`.
    */
    void setDescription(const string &description);

    /**
     * The type of the `Item` holding this `ItemIdentifier`.
    */
    ItemType getType() const;

    /**
     * Sets the current incremental ID.
     * 
     * @param incrementalId The new incremental ID.
    */
    static void setIncrementalID(size_t incrementalId);

    bool operator==(const ItemIdentifier &right) const;
    bool operator!=(const ItemIdentifier &right) const;
    bool operator<(const ItemIdentifier &right) const;
    bool operator>(const ItemIdentifier &right) const;
    ItemIdentifier &operator=(const ItemIdentifier &right);
    ItemIdentifier &operator=(ItemIdentifier &&right);

    friend istream &operator>>(istream &is, ItemIdentifier &identifier);
    friend class Item;
};

#endif
