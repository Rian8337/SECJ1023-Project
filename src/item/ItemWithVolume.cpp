#include "ItemWithVolume.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

using namespace std;

ItemWithVolume::ItemWithVolume(float volume) { setVolume(volume); }

ItemWithVolume::ItemWithVolume(const ItemWithVolume &copy) { *this = copy; }

ItemWithVolume::ItemWithVolume(ItemWithVolume &&other) { *this = move(other); }

float ItemWithVolume::getVolume() const { return volume; }

void ItemWithVolume::setVolume(float volume) {
    if (volume < 0) {
        throw invalid_argument(
            "The volume of an item must be more than or equal to zero.");
    }

    this->volume = volume;
}

string ItemWithVolume::outputToConsole() const {
    ostringstream os;

    os << "Volume: " << setprecision(2) << fixed << volume << "mL" << endl;

    return os.str();
}

void ItemWithVolume::inputData() {
    while (true) {
        string volume;
        cout << "Enter item volume in mL (currently " << setprecision(2)
             << fixed << this->volume << "): ";
        getline(cin, volume);

        try {
            setVolume(stof(volume));
            break;
        } catch (const exception &ignored) {
            cout << "Invalid volume." << endl;
        }
    }
}

ItemWithVolume &ItemWithVolume::operator=(const ItemWithVolume &right) {
    volume = right.volume;

    return *this;
}

ItemWithVolume &ItemWithVolume::operator=(ItemWithVolume &&right) {
    volume = right.volume;
    right.volume = 0;

    return *this;
}
