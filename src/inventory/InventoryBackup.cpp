#include "InventoryBackup.h"
#include "../item/BreakfastSpreadItem.h"
#include "../item/CosmeticItem.h"
#include "../item/FoodItem.h"
#include "../item/FruitItem.h"
#include "../item/Item.h"
#include "../item/ItemIdentifier.h"
#include "../item/ItemType.h"
#include "../item/ItemWithVolume.h"
#include "../item/ItemWithWeight.h"
#include "../item/KitchenwareItem.h"
#include "../item/NoodlesItem.h"
#include "../item/SoftDrinksItem.h"
#include "../item/VegetableItem.h"
#include "../item/WashingItem.h"
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

    string line;
    size_t highestId = 0;

    auto extractDataFromLine = [&]() {
        size_t sepIdx = line.find(',');
        string substr = line.substr(0, sepIdx);
        line.erase(0, sepIdx + 1);

        return substr;
    };

    while (!file.eof()) {
        getline(file, line);

        if (line.empty()) {
            break;
        }

        size_t id = stoul(extractDataFromLine());
        string name = extractDataFromLine();
        string description = extractDataFromLine();
        ItemType type = parseItemType((short)stoi(extractDataFromLine()));

        Item *item;

        switch (type) {
        case ItemType::cosmetic:
            item = new CosmeticItem(id);
            break;
        case ItemType::kitchenware:
            item = new KitchenwareItem(id);
            break;
        case ItemType::softDrinks:
            item = new SoftDrinksItem(id);
            break;
        case ItemType::breakfastSpread:
            item = new BreakfastSpreadItem(id);
            break;
        case ItemType::noodles:
            item = new NoodlesItem(id);
            break;
        case ItemType::washing:
            item = new WashingItem(id);
            break;
        case ItemType::fruit:
            item = new FruitItem(id);
            break;
        case ItemType::vegetables:
            item = new VegetableItem(id);
            break;
        default:
            throw invalid_argument("Unable to infer item type from backup");
        }

        ItemIdentifier *identifier = item->getIdentifier();

        identifier->setName(name);
        identifier->setDescription(description);
        item->setStock(stoul(extractDataFromLine()));
        item->setPrice(stof(extractDataFromLine()));

        // Extract additional data.
        if (FoodItem *foodItem = dynamic_cast<FoodItem *>(item)) {
            foodItem->setCalories(stof(extractDataFromLine()));
        }

        if (ItemWithVolume *volumeItem = dynamic_cast<ItemWithVolume *>(item)) {
            volumeItem->setVolume(stof(extractDataFromLine()));
        }

        if (ItemWithWeight *weightItem = dynamic_cast<ItemWithWeight *>(item)) {
            weightItem->setWeight(stof(extractDataFromLine()));
        }

        // Finally, insert the data and save the highest item ID.
        backup.items.append(item);
        highestId = max(id, highestId);
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

    for (Item *item : items) {
        const ItemIdentifier *identifier = item->getIdentifier();

        file << identifier->getID() << ',' << identifier->getName() << ','
             << identifier->getDescription() << ',' << identifier->getType()
             << ',' << item->getStock() << ',' << item->getPrice();

        // Store additional data.
        if (FoodItem *foodItem = dynamic_cast<FoodItem *>(item)) {
            file << ',' << foodItem->getCalories();
        }

        if (ItemWithVolume *volumeItem = dynamic_cast<ItemWithVolume *>(item)) {
            file << ',' << volumeItem->getVolume();
        }

        if (ItemWithWeight *weightItem = dynamic_cast<ItemWithWeight *>(item)) {
            file << ',' << weightItem->getWeight();
        }

        file << endl;
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
