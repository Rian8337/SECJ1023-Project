#include "KitchenwareItem.h"
#include "ItemType.h"
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

KitchenwareItem::KitchenwareItem() : Item(ItemType::kitchenware) {
    material = "";
}

KitchenwareItem::KitchenwareItem(size_t id) : Item(id, ItemType::kitchenware) {
    material = "";
}

KitchenwareItem::KitchenwareItem(const string &name, const string &description,
                                 size_t stock, float price,
                                 const string &material)
    : Item(name, description, ItemType::kitchenware, stock, price) {
    this->material = material;
}

KitchenwareItem::KitchenwareItem(const KitchenwareItem &copy)
    : Item(copy.identifier->getID(), copy.identifier->getType()) {
    *this = copy;
}

KitchenwareItem::KitchenwareItem(KitchenwareItem &&other)
    : Item(other.identifier->getID(), other.identifier->getType()) {
    *this = move(other);
}

string KitchenwareItem::getMaterial() const { return material; }

void KitchenwareItem::setMaterial(const string &material) {
    this->material = material;
}

KitchenwareItem *KitchenwareItem::deepClone() const {
    return new KitchenwareItem(*this);
}

string KitchenwareItem::outputToConsole() const {
    ostringstream os(Item::outputToConsole());

    os << "Material: " << material << endl;

    return os.str();
}

void KitchenwareItem::inputData() {
    Item::inputData();

    while (true) {
        cout << "Enter kitchenware item material (currently "
             << (!material.empty() ? material : "None") << "): ";
        cin >> material;

        if (material.empty()) {
            cout << "Material cannot be empty." << endl;
            continue;
        }
    }
}

KitchenwareItem &KitchenwareItem::operator=(const KitchenwareItem &right) {
    Item::operator=(right);

    material = right.material;

    return *this;
}

KitchenwareItem &KitchenwareItem::operator=(KitchenwareItem &&right) {
    Item::operator=(move(right));

    material = right.material;
    right.material = "";

    return *this;
}
