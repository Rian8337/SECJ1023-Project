#include "InventoryBackup.h"
#include "../item/Item.h"
#include "../item/ItemIdentifier.h"
#include "../utils/DynamicArray.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

InventoryBackup::InventoryBackup(const DynamicArray<Item *> &items) {
    creationDate = time(0);

    this->items = items;
}

InventoryBackup::~InventoryBackup() {
    for (Item *item : items) {
        delete item;
    }
}

InventoryBackup InventoryBackup::readBackup(const string &fileName) {
    string dir = "./backups/";
    dir += fileName;

    ifstream file(dir);
    InventoryBackup backup(DynamicArray<Item *>(10));

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

        backup.items.append(item);
        highestId = max(identifier->getID(), highestId);
    }

    // Set the incremental ID so that subsequent item additions have the correct ID.
    ItemIdentifier::resetIncrementalId(highestId);

    return backup;
}

time_t InventoryBackup::getCreationDate() const { return creationDate; }
const DynamicArray<Item *> &InventoryBackup::getItems() const { return items; }

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
    string dir = "./backups/";
    dir += getFilename();

    ofstream file(dir);

    for (const Item *item : items) {
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

    for (const Item *item : backup.items) {
        os << item->generateTableRow() << endl;
    }

    return os;
}
