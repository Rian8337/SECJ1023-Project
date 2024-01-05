#include "./inventory/InventoryBackup.h"
#include "./inventory/InventoryManager.h"
#include "./inventory/search/InventorySearchQuery.h"
#include "./inventory/search/InventorySearchResult.h"
#include "./inventory/search/ItemFilterMethod.h"
#include "./inventory/search/ItemSortMethod.h"
#include "./item/BreakfastSpreadItem.h"
#include "./item/CosmeticItem.h"
#include "./item/FruitItem.h"
#include "./item/Item.h"
#include "./item/ItemType.h"
#include "./item/KitchenwareItem.h"
#include "./item/NoodlesItem.h"
#include "./item/SoftDrinksItem.h"
#include "./item/VegetableItem.h"
#include "./item/WashingItem.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

short getSelection(short lowest, short highest, bool allowGoingBack = true) {
    short selection = 0;

    while (true) {
        string input;
        cout << "Enter your selection (" << lowest << '-' << highest << ')';

        if (allowGoingBack) {
            cout << ", -1 to go back";
        }

        cout << ": ";

        getline(cin, input);

        try {
            selection = (short)stoi(input);
        } catch (const exception &ignored) {
            cout << "Invalid selection." << endl;
            continue;
        }

        if ((!allowGoingBack || selection != -1) &&
            (selection < lowest || selection > highest)) {
            cout << "Invalid selection." << endl;
            continue;
        }

        break;
    }

    return selection;
}

void addItem(InventoryManager &manager) {
    listItemTypes();
    cout << endl;

    ItemType itemType;

    while (true) {
        short selection = getSelection(1, itemTypeHighest, true);
        if (selection == -1) {
            return;
        }

        try {
            itemType = parseItemType(selection);
            cout << endl;

            break;
        } catch (const exception &ignored) {
            cout << "Invalid item type." << endl;
        }
    }

    Item *item;

    switch (itemType) {
    case ItemType::cosmetic:
        item = new CosmeticItem();
        break;
    case ItemType::kitchenware:
        item = new KitchenwareItem();
        break;
    case ItemType::softDrinks:
        item = new SoftDrinksItem();
        break;
    case ItemType::breakfastSpread:
        item = new BreakfastSpreadItem();
        break;
    case ItemType::noodles:
        item = new NoodlesItem();
        break;
    case ItemType::washing:
        item = new WashingItem();
        break;
    case ItemType::fruit:
        item = new FruitItem();
        break;
    case ItemType::vegetables:
        item = new VegetableItem();
        break;
    default:
        throw invalid_argument("Unable to infer item type from backup");
    }

    cin >> *item;

    manager.addItem(item);

    cout << endl << "Item added." << endl;
}

void removeItem(InventoryManager &manager) {
    if (manager.getItems().empty()) {
        cout << "No items are in the inventory manager." << endl;
        return;
    }

    size_t id;

    while (true) {
        string input;
        cout << "Enter the ID of the item: ";
        getline(cin, input);

        try {
            id = stoul(input);
            cout << endl;

            break;
        } catch (const exception &ignored) {
            cout << "Invalid ID" << endl;
        }
    }

    cout << "Item " << id << ' '
         << (manager.removeItem(id) ? "has been removed" : "was not present")
         << '.' << endl;
}

void editItem(InventoryManager &manager) {
    if (manager.getItems().empty()) {
        cout << "No items are in the inventory manager." << endl;
        return;
    }

    size_t id;
    Item *item = nullptr;

    while (true) {
        string input;
        cout << "Enter the ID of the item: ";
        getline(cin, input);

        try {
            id = stoul(input);
            cout << endl;
        } catch (const exception &ignored) {
            cout << "Invalid ID" << endl;
            continue;
        }

        item = manager.getItem(id);

        if (item == nullptr || item->getIdentifier()->getID() != id) {
            cout << "No item with ID " << id
                 << " was found in the inventory manager." << endl;
            continue;
        }

        break;
    }

    cin >> *item;
}

void displayItemDetails(InventoryManager &manager) {
    if (manager.getItems().empty()) {
        cout << "No items are in the inventory manager." << endl;
        return;
    }

    size_t id;
    Item *item = nullptr;

    while (true) {
        string input;
        cout << "Enter the ID of the item: ";
        getline(cin, input);

        try {
            id = stoul(input);
            cout << endl;
        } catch (const exception &ignored) {
            cout << "Invalid ID" << endl;
            continue;
        }

        item = manager.getItem(id);

        if (item == nullptr || item->getIdentifier()->getID() != id) {
            cout << "No item with ID " << id
                 << " was found in the inventory manager." << endl;
            continue;
        }

        break;
    }

    cout << *item;
}

void listItems(const InventoryManager &manager) {
    if (manager.getItems().empty()) {
        cout << "No items are in the inventory manager." << endl;
        return;
    }

    cout << manager.createSheet();
}

void searchItems(InventoryManager &manager) {
    if (manager.getItems().empty()) {
        cout << "No items are in the inventory manager." << endl;
        return;
    }

    static const string line = string(17, '=');
    InventorySearchQuery searchQuery;

    while (true) {
        cout << "Search Items Menu" << endl
             << line << endl
             << "1. Set sorting method" << endl
             << "2. Set filtering method" << endl
             << "3. Input search terms" << endl
             << "4. Add item type filter" << endl
             << "5. Remove item type filter" << endl
             << "6. Remove all item type filters" << endl
             << "7. Display search information" << endl
             << "8. Search items" << endl
             << "9. Return to main menu" << endl
             << endl;

        short selection = getSelection(1, 9, false);

        if (selection == 9) {
            // Short-circuit to prevent printing lines.
            return;
        }

        cout << endl << line << endl << endl;

        switch (selection) {
        case 1:
            listSortMethods();
            cout << endl;

            while (true) {
                try {
                    short s = getSelection(1, itemSortHighest);
                    cout << endl;

                    if (s == -1) {
                        break;
                    }

                    ItemSortMethod method = parseSortMethod(s);
                    searchQuery.setSortMethod(method);

                    cout << "Successfully set item sorting method to "
                         << itemSortMethodToString(method) << '.' << endl;

                    break;
                } catch (const exception &ignored) {
                    cout << "Invalid selection." << endl;
                }
            }

            break;
        case 2:
            listFilterMethods();
            cout << endl;

            while (true) {
                try {
                    short s = getSelection(1, itemFilterHighest);
                    cout << endl;

                    if (s == -1) {
                        break;
                    }

                    ItemFilterMethod method = parseFilterMethod(s);
                    searchQuery.setFilterMethod(method);

                    cout << "Successfully set item filtering method to "
                         << itemFilterMethodToString(method) << '.' << endl;

                    break;
                } catch (const exception &ignored) {
                    cout << "Invalid selection." << endl;
                }
            }

            break;
        case 3: {
            string query;
            cout << "Enter search term: ";
            getline(cin, query);

            searchQuery.setQuery(query);

            cout << endl
                 << "Successfully set the search term to "
                 << (!query.empty() ? query : "None") << '.';

            break;
        }
        case 4:
            listItemTypes();
            cout << endl;

            while (true) {
                try {
                    short s = getSelection(1, itemTypeHighest);
                    cout << endl;

                    if (s == -1) {
                        break;
                    }

                    ItemType type = parseItemType(s);
                    searchQuery.addItemType(type);

                    cout << "Added item type " << itemTypeToString(type)
                         << " from the filter." << endl;

                    break;
                } catch (const exception &ignored) {
                    cout << "Invalid selection." << endl;
                }
            }

            break;
        case 5:
            listItemTypes();
            cout << endl;

            while (true) {
                try {
                    short s = getSelection(1, itemTypeHighest);
                    if (s == -1) {
                        cout << endl;
                        break;
                    }

                    ItemType type = parseItemType(s);
                    searchQuery.removeItemType(type);

                    cout << "Removed item type " << itemTypeToString(type)
                         << " from the filter." << endl;

                    break;
                } catch (const exception &ignored) {
                    cout << "Invalid selection." << endl;
                }
            }

            break;
        case 6:
            searchQuery.emptyItemTypes();
            cout << "Item type filters have been deleted." << endl;
            break;
        case 7:
            cout << searchQuery;
            break;
        case 8: {
            InventorySearchResult result = manager.searchItems(searchQuery);

            if (result.getItems().empty()) {
                cout << "No items were found.";
                break;
            }

            cout << result << endl
                 << "Existing search settings will be saved as long as this "
                    "menu is active."
                 << endl;
            break;
        }
        }

        cout << endl;
    }
}

void backupItems(const InventoryManager &manager) {
    if (manager.getItems().empty()) {
        cout << "No items are in the inventory manager." << endl;
        return;
    }

    InventoryBackup backup = manager.createBackup();

    if (backup.saveToFile()) {
        cout << "Backup saved as " << backup.getFilename() << '.';
    } else {
        cout << "Failed to save backup.";
    }

    cout << endl;
}

void loadBackup(InventoryManager &manager) {
    string filename;

    cout << "Enter the name of the backup file: ";
    getline(cin, filename);
    cout << endl;

    InventoryBackup backup = InventoryBackup::readBackup(filename);

    if (backup.getItems().empty()) {
        cout << "No items were found in the backup file." << endl;
        return;
    }

    if (manager.loadBackup(backup)) {
        cout << "Loaded backup into the inventory manager.";
    } else {
        cout << "Failed to load backup.";
    }

    cout << endl;
}

int main() {
    InventoryManager manager;
    const string line = string(35, '=');
    const string mainMenuLine = string(9, '=');

    cout << "Inventory Management System" << endl << line << endl;

    while (true) {
        cout << endl
             << "Main Menu" << endl
             << mainMenuLine << endl
             << "1. Add item" << endl
             << "2. Remove item" << endl
             << "3. Edit item" << endl
             << "4. Display item details" << endl
             << "5. List items" << endl
             << "6. Search items" << endl
             << "7. Backup items" << endl
             << "8. Load backup" << endl
             << "9. Exit" << endl
             << endl;

        short selection = getSelection(1, 9, false);

        cout << endl << line << endl << endl;

        switch (selection) {
        case 1:
            addItem(manager);
            break;
        case 2:
            removeItem(manager);
            break;
        case 3:
            editItem(manager);
            break;
        case 4:
            displayItemDetails(manager);
            break;
        case 5:
            listItems(manager);
            break;
        case 6:
            searchItems(manager);
            break;
        case 7:
            backupItems(manager);
            break;
        case 8:
            loadBackup(manager);
            break;
        case 9:
            cout << "Thank you for using the inventory management system!"
                 << endl;

            return 0;
        }

        cout << endl << line << endl;
    }
}
