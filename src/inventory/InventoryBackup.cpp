#include "InventoryBackup.h"
#include "../item/Item.h"
#include "../item/ItemIdentifier.h"
#include "../utils/ArrayUtils.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace ArrayUtils;
using namespace std;

InventoryBackup::InventoryBackup(Item **items, const size_t numItems) {
    creationDate = time(0);

    this->items = items;
    this->numItems = numItems;
}

InventoryBackup::~InventoryBackup() {
    for (size_t i = 0; i < numItems; ++i) {
        delete items[i];
    }

    delete[] items;
}

InventoryBackup InventoryBackup::readBackup(const string &fileName) {
    string dir = "../backups/";
    dir += fileName;

    ifstream file(dir);

    size_t itemSize = 10;
    InventoryBackup backup(new Item *[itemSize], 0);

    if (!file.is_open()) {
        return backup;
    }

    auto extractDataFromLine = [](string &line) {
        size_t sepIdx = line.find(',');
        string substr = line.substr(0, sepIdx);
        line.erase(0, sepIdx + 1);

        return substr;
    };

    string line;
    size_t highestId = 0;

    while (!file.eof()) {
        getline(file, line);

        if (line.empty()) {
            break;
        }

        Item *item = new Item();
        ItemIdentifier *identifier = item->getIdentifier();

        identifier->setID(stoul(extractDataFromLine(line)));
        identifier->setName(extractDataFromLine(line));
        identifier->setDescription(extractDataFromLine(line));
        identifier->setType(
            parseItemType((short)stoi(extractDataFromLine(line))));
        item->setStock(stoul(extractDataFromLine(line)));
        item->setPrice(stof(extractDataFromLine(line)));

        addElement(backup.items, item, backup.numItems, itemSize, false);

        highestId = max(identifier->getID(), highestId);
    }

    // Set the incremental ID so that subsequent item additions have the correct ID.
    ItemIdentifier::resetIncrementalId(highestId);

    return backup;
}

time_t InventoryBackup::getCreationDate() const { return creationDate; }
size_t InventoryBackup::getNumItems() const { return numItems; }
Item **InventoryBackup::getItems() const { return items; }

string InventoryBackup::getFilename() const {
    string name = asctime(gmtime(&creationDate));

    // Remove the newline character.
    name.pop_back();

    // In Windows, \r may also be present.
    if (name.back() == '\r') {
        name.pop_back();
    }

    name += ".backup";

    return name;
}

bool InventoryBackup::saveToFile() {
    string dir = "../backups/";
    dir += getFilename();

    ofstream file(dir);

    for (size_t i = 0; i < numItems; ++i) {
        const Item *item = items[i];
        const ItemIdentifier *identifier = item->getIdentifier();

        file << identifier->getID() << ',' << identifier->getName() << ','
             << identifier->getDescription() << ',' << identifier->getType()
             << ',' << item->getStock() << ',' << item->getPrice() << endl;
    }

    file.close();

    return !file.fail();
}

ostream &operator<<(ostream &os, const InventoryBackup &backup) {
    string dateStr(asctime(gmtime(&backup.creationDate)));

    // Remove the newline character.
    dateStr.pop_back();

    // In Windows, \r may also be present.
    if (dateStr.back() == '\r') {
        dateStr.pop_back();
    }

    os << "Inventory report as of " << dateStr << " UTC" << endl
       << endl
       << "ID" << '\t' << "Name" << string(50, ' ') << '\t' << "Type"
       << string(16, ' ') << '\t' << "Stock" << '\t' << "Price (RM)" << endl;

    for (size_t i = 0; i < backup.numItems; ++i) {
        os << backup.items[i]->generateTableRow() << endl;
    }

    return os;
}
