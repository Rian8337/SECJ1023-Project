#include "Item.h"
#include "ItemIdentifier.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

Item::Item() {
    identifier = new ItemIdentifier();
    stock = 0;
    price = 0;
}

Item::Item(size_t id) {
    identifier = new ItemIdentifier(id);
    stock = 0;
    price = 0;
};

Item::Item(string name, string description, ItemType type, size_t stock,
           float price) {
    identifier = new ItemIdentifier(name, description, type);
    this->stock = stock;

    setPrice(price);
}

Item::Item(const Item &copy) {
    identifier = new ItemIdentifier(*copy.identifier);
    stock = copy.stock;
    price = copy.price;
}

Item::~Item() { delete identifier; }

ItemIdentifier *Item::getIdentifier() const { return identifier; }

size_t Item::getStock() const { return stock; }
void Item::setStock(long stock) {
    if (stock < 0) {
        throw invalid_argument(
            "The stock of an item must be equal to or more than zero.");
    }

    this->stock = stock;
}

float Item::getPrice() const { return price; }
void Item::setPrice(float price) {
    if (price <= 0) {
        throw invalid_argument("The price of an item must be more than zero.");
    }

    this->price = price;
}

string Item::generateTableRow() const {
    ostringstream os;

    os << identifier->getID() << '\t' << left << setw(50)
       << identifier->getName() << '\t' << left << setw(16)
       << itemTypeToString(identifier->getType()) << '\t' << stock << '\t'
       << setprecision(2) << fixed << price;

    return os.str();
}

bool Item::operator==(const Item &right) const {
    return *identifier == *right.identifier;
}

bool Item::operator!=(const Item &right) const {
    return *identifier != *right.identifier;
}

bool Item::operator<(const Item &right) const {
    return *identifier < *right.identifier;
}

bool Item::operator>(const Item &right) const {
    return *identifier > *right.identifier;
}

ostream &operator<<(ostream &os, const Item &item) {
    const ItemIdentifier *identifier = item.getIdentifier();

    os << "Item Information" << string(16, '-') << endl
       << "Name: " << identifier->getName() << endl
       << "Description: " << identifier->getDescription() << endl
       << "Type: " << itemTypeToString(identifier->getType()) << endl
       << "Stock: " << item.getStock() << endl
       << "Price: RM" << setprecision(2) << fixed << item.getPrice() << endl;

    return os;
}

istream &operator>>(istream &is, Item &item) {
    is >> *item.getIdentifier();

    while (true) {
        string stock;
        cout << "Enter item stock (currently " << item.stock << "): ";
        getline(is, stock);

        try {
            item.setStock(stoul(stock));
            break;
        } catch (const exception &ignored) {
            cout << "Invalid stock." << endl;
        }
    }

    while (true) {
        string price;
        cout << "Enter item price (currently " << setprecision(2) << fixed
             << item.price << "): ";
        getline(is, price);

        try {
            item.setPrice(stof(price));
            break;
        } catch (const exception &ignored) {
            cout << "Invalid price." << endl;
        }
    }

    return is;
}
