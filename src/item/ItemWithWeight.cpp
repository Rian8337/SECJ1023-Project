#include "ItemWithWeight.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

ItemWithWeight::ItemWithWeight(float weight) { setWeight(weight); }

ItemWithWeight::ItemWithWeight(const ItemWithWeight &copy) { *this = copy; }

ItemWithWeight::ItemWithWeight(ItemWithWeight &&other) { *this = move(other); }

float ItemWithWeight::getWeight() const { return weight; }

void ItemWithWeight::setWeight(float weight) {
    if (weight < 0) {
        throw invalid_argument(
            "The weight of an item must be more than or equal to zero.");
    }

    this->weight = weight;
}

string ItemWithWeight::outputToConsole() const {
    ostringstream os;

    os << "Weight: " << setprecision(2) << fixed << weight << 'g' << endl;

    return os.str();
}

void ItemWithWeight::inputData() {
    while (true) {
        string weight;
        cout << "Enter item weight in g (currently " << setprecision(2) << fixed
             << this->weight << "): ";
        getline(cin, weight);

        try {
            setWeight(stof(weight));
            break;
        } catch (const exception &ignored) {
            cout << "Invalid weight." << endl;
        }
    }
}

ItemWithWeight &ItemWithWeight::operator=(const ItemWithWeight &right) {
    weight = right.weight;

    return *this;
}

ItemWithWeight &ItemWithWeight::operator=(ItemWithWeight &&right) {
    weight = right.weight;
    right.weight = 0;

    return *this;
}
