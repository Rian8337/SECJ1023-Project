#include "ItemIdentifier.h"
#include "ItemType.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

size_t ItemIdentifier::incrementalId = 0;

void ItemIdentifier::resetIncrementalId(size_t id) { incrementalId = id; }

ItemIdentifier::ItemIdentifier(ItemType type)
    : ItemIdentifier(++incrementalId, type) {}

ItemIdentifier::ItemIdentifier(size_t id, ItemType type) {
    this->id = id;
    name = "";
    description = "";
    this->type = type;
}

ItemIdentifier::ItemIdentifier(const string &name, const string &description,
                               ItemType type) {
    id = ++incrementalId;
    this->name = name;
    this->description = description;
    this->type = type;
}

ItemIdentifier::ItemIdentifier(const ItemIdentifier &copy) { *this = copy; }

ItemIdentifier::ItemIdentifier(ItemIdentifier &&other) { *this = move(other); }

size_t ItemIdentifier::getID() const { return id; }
void ItemIdentifier::setID(size_t id) { this->id = id; }

string ItemIdentifier::getName() const { return name; }
void ItemIdentifier::setName(const string &name) { this->name = name; }

string ItemIdentifier::getDescription() const { return description; }
void ItemIdentifier::setDescription(const string &description) {
    this->description = description;
}

ItemType ItemIdentifier::getType() const { return type; }

void ItemIdentifier::setIncrementalID(size_t incrementalId) {
    ItemIdentifier::incrementalId = incrementalId;
}

bool ItemIdentifier::operator==(const ItemIdentifier &right) const {
    return id == right.id;
}

bool ItemIdentifier::operator!=(const ItemIdentifier &right) const {
    return id != right.id;
}

bool ItemIdentifier::operator<(const ItemIdentifier &right) const {
    return id < right.id;
}

bool ItemIdentifier::operator>(const ItemIdentifier &right) const {
    return id > right.id;
}

ItemIdentifier &ItemIdentifier::operator=(const ItemIdentifier &right) {
    if (&right != this) {
        id = right.id;
        name = right.name;
        description = right.description;
        type = right.type;
    }

    return *this;
}

ItemIdentifier &ItemIdentifier::operator=(ItemIdentifier &&right) {
    if (&right != this) {
        id = right.id;
        name = right.name;
        description = right.description;
        type = right.type;

        right.id = 0;
        right.name = "";
        right.description = "";
        right.type = ItemType::none;
    }

    return *this;
}

istream &operator>>(istream &is, ItemIdentifier &identifier) {
    while (true) {
        string name;
        cout << "Enter the name of item, up to 50 characters (currently "
             << (!identifier.name.empty() ? identifier.name : "None")
             << "): " << endl;
        getline(is, name);
        cout << endl;

        if (name.empty()) {
            cout << "Name cannot be empty." << endl;
            continue;
        }

        if (name.size() > 50) {
            cout << "Name must not exceed 50 characters." << endl;
            continue;
        }

        identifier.setName(name);
        break;
    }

    while (true) {
        string description;
        cout << "Enter the description of the item, up to 100 characters "
                "(currently "
             << (!identifier.description.empty() ? identifier.description
                                                 : "None")
             << "): " << endl;
        getline(is, description);
        cout << endl;

        if (description.empty()) {
            cout << "Description cannot be empty." << endl;
            continue;
        }

        if (description.size() > 100) {
            cout << "Description must not exceed 100 characters." << endl;
            continue;
        }

        identifier.setDescription(description);
        break;
    }

    return is;
}
