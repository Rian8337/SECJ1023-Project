#include "Item.h"
#include "ItemIdentifier.h"
#include "ItemType.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

Item::Item(ItemType type) {
    identifier = new ItemIdentifier(type);
    stock = 0;
    price = 0;
}

Item::Item(size_t id, ItemType type) {
    identifier = new ItemIdentifier(id, type);
    stock = 0;
    price = 0;
};

Item::Item(const string &name, const string &description, ItemType type,
           size_t stock, float price) {
    identifier = new ItemIdentifier(name, description, type);
    this->stock = stock;

    setPrice(price);
}

Item::Item(const Item &copy) {
    identifier = new ItemIdentifier(copy.identifier->id, copy.identifier->type);

    *this = copy;
}

Item::Item(Item &&other) { *this = move(other); }

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

void Item::inputData() {
    cin >> *identifier;

    while (true) {
        string stock;
        cout << "Enter item stock (currently " << this->stock << "): ";
        getline(cin, stock);

        try {
            setStock(stoul(stock));
            break;
        } catch (const exception &ignored) {
            cout << "Invalid stock." << endl;
        }
    }

    while (true) {
        string price;
        cout << "Enter item price in RM (currently " << setprecision(2) << fixed
             << this->price << "): ";
        getline(cin, price);

        try {
            setPrice(stof(price));
            break;
        } catch (const exception &ignored) {
            cout << "Invalid price." << endl;
        }
    }
}

string Item::outputToConsole() const {
    ostringstream os;

    os << "Item Information" << endl
       << string(16, '-') << endl
       << "Name: " << identifier->name << endl
       << "Description: " << identifier->description << endl
       << "Type: " << itemTypeToString(identifier->type) << endl
       << "Stock: " << stock << endl
       << "Price: RM" << setprecision(2) << fixed << price << endl;

    return os.str();
}

string Item::generateTableRow() const {
    ostringstream os;

    os << identifier->id << '\t' << left << setw(50) << identifier->name << '\t'
       << left << setw(16) << itemTypeToString(identifier->type) << '\t'
       << stock << '\t' << setprecision(2) << fixed << price;

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

Item &Item::operator=(const Item &right) {
    *identifier = *right.identifier;
    stock = right.stock;
    price = right.price;

    return *this;
}

Item &Item::operator=(Item &&right) {
    identifier = right.identifier;
    stock = right.stock;
    price = right.price;

    right.identifier = nullptr;
    right.stock = 0;
    right.price = 0;

    return *this;
}

ostream &operator<<(ostream &os, const Item &item) {
    return os << item.outputToConsole();
}

istream &operator>>(istream &is, Item &item) {
    item.inputData();

    return is;
}
