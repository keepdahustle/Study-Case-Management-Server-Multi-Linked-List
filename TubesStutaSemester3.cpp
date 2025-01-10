// Multi Linked List Implementation in C++
#include <iostream>
#include <string>
#include <limits> // Fix for numeric_limits
using namespace std;

// Node structure for Child (Folder)
struct ChildNode {
    string folderName;
    ChildNode* nextChild;
};

// Node structure for Relation (Division)
struct RelationNode {
    string divisionName;
    ChildNode* folder;
    RelationNode* nextRelation;
};

// Node structure for Parent (Floor)
struct ParentNode {
    string floorName;
    RelationNode* relations;
    ParentNode* nextParent;
};

// Main Multi Linked List Class
class MultiLinkedList {
private:
    ParentNode* head;

public:
    MultiLinkedList() : head(nullptr) {
        // Initialize the structure based on the given case study
        addFloor("Lantai1");
        addRelation("Lantai1", "DivisiHumanResource");
        addChild("Lantai1", "DivisiHumanResource", "FolderDataKaryawan");
        addRelation("Lantai1", "DivisiCreative");
        addChild("Lantai1", "DivisiCreative", "FolderGraphic");
        addRelation("Lantai1", "DivisiFinance");
        addChild("Lantai1", "DivisiFinance", "FolderFinance");

        addFloor("Lantai2");
        addRelation("Lantai2", "DivisiSosialMedia");
        addChild("Lantai2", "DivisiSosialMedia", "FolderGraphic");

        addFloor("Lantai3");

        addFloor("Lantai4");
        addRelation("Lantai4", "DivisiDeveloper");
        addChild("Lantai4", "DivisiDeveloper", "FolderDevResource");
        addRelation("Lantai4", "DivisiDataAnalyst");
        addChild("Lantai4", "DivisiDataAnalyst", "FolderDataResource");
    }

    // Function to Add Floor (Parent) with Validation
// Function to Add Floor (Parent) with Validation
void addFloor(const string& floorName) {
    if (findFloor(floorName)) {
        cout << "Floor '" << floorName << "' already exists.\n";
        return;
    }
    head = new ParentNode{floorName, nullptr, head};
}

    // Function to Add Relation (Division) without Folder
void addRelation(const string& floorName, const string& divisionName) {
    ParentNode* parent = findFloor(floorName);
    if (!parent) {
        cout << "Floor '" << floorName << "' not found.\n";
        return;
    }

    RelationNode* relation = parent->relations;
    while (relation) {
        if (relation->divisionName == divisionName) {
            cout << "Division '" << divisionName << "' already exists on Floor '" << floorName << "'.\n";
            return;
        }
        relation = relation->nextRelation;
    }

    parent->relations = new RelationNode{divisionName, nullptr, parent->relations};
}

    // Function to Add Child (Folder) to a Division
void addChild(const string& floorName, const string& divisionName, const string& folderName) {
    ParentNode* parent = findFloor(floorName);
    if (!parent) {
        cout << "Floor '" << floorName << "' not found.\n";
        return;
    }

    RelationNode* relation = parent->relations;
    while (relation) {
        if (relation->divisionName == divisionName) {
            ChildNode* child = relation->folder;
            while (child) {
                if (child->folderName == folderName) {
                    cout << "Folder '" << folderName << "' already exists in Division '" << divisionName << "' on Floor '" << floorName << "'.\n";
                    return;
                }
                child = child->nextChild;
            }

            relation->folder = new ChildNode{folderName, relation->folder};
            return;
        }
        relation = relation->nextRelation;
    }
}

    // Function to Display All Floors (Parents)
    void displayFloors() {
        if (!head) {
            cout << "No floors available.\n";
            return;
        }
        cout << "Available Floors:\n";
        for (ParentNode* current = head; current; current = current->nextParent)
            cout << "- " << current->floorName << "\n";
    }

    // Function to Display All Relations for a Floor
    void displayRelations(const string& floorName) {
        ParentNode* parent = findFloor(floorName);
        if (!parent) {
            cout << "Floor '" << floorName << "' not found.\n";
            return;
        }
        if (!parent->relations) {
            cout << "No relations available for Floor '" << floorName << "'.\n";
            return;
        }
        cout << "Available Relations for Floor '" << floorName << "':\n";
        for (RelationNode* current = parent->relations; current; current = current->nextRelation)
            cout << "- " << current->divisionName << "\n";
    }

    // Function to Display All Children for a Relation
    void displayChildren(const string& floorName, const string& divisionName) {
        ParentNode* parent = findFloor(floorName);
        if (!parent) {
            cout << "Floor '" << floorName << "' not found.\n";
            return;
        }

        for (RelationNode* relation = parent->relations; relation; relation = relation->nextRelation) {
            if (relation->divisionName == divisionName) {
                if (!relation->folder) {
                    cout << "No folders available for Division '" << divisionName << "' on Floor '" << floorName << "'.\n";
                    return;
                }
                cout << "Available Folders for Division '" << divisionName << "' on Floor '" << floorName << "':\n";
                for (ChildNode* current = relation->folder; current; current = current->nextChild)
                    cout << "- " << current->folderName << "\n";
                return;
            }
        }
        cout << "Division '" << divisionName << "' not found on Floor '" << floorName << "'.\n";
    }

    // Function to Delete Floor (Parent) along with its Relations and Children
    void deleteFloor(const string& floorName) {
        displayFloors();
        ParentNode* current = head;
        ParentNode* prev = nullptr;

        while (current) {
            if (current->floorName == floorName) {
                if (prev) prev->nextParent = current->nextParent;
                else head = current->nextParent;

                // Delete all relations under the floor
                while (current->relations) {
                    RelationNode* tempRelation = current->relations;
                    current->relations = current->relations->nextRelation;

                    // Delete all children under the relation
                    while (tempRelation->folder) {
                        ChildNode* tempChild = tempRelation->folder;
                        tempRelation->folder = tempRelation->folder->nextChild;
                        delete tempChild;
                    }
                    delete tempRelation;
                }
                delete current;
                cout << "Floor '" << floorName << "' and all its relations and folders deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->nextParent;
        }
        cout << "Floor '" << floorName << "' not found.\n";
    }

    // Function to Delete Relation (Division)
    void deleteRelation(const string& floorName, const string& divisionName) {
        displayRelations(floorName);
        ParentNode* parent = findFloor(floorName);
        if (!parent) {
            cout << "Floor '" << floorName << "' not found.\n";
            return;
        }

        RelationNode* current = parent->relations;
        RelationNode* prev = nullptr;

        while (current) {
            if (current->divisionName == divisionName) {
                if (prev) prev->nextRelation = current->nextRelation;
                else parent->relations = current->nextRelation;

                // Delete all children under the relation
                while (current->folder) {
                    ChildNode* tempChild = current->folder;
                    current->folder = current->folder->nextChild;
                    delete tempChild;
                }
                delete current;
                cout << "Division '" << divisionName << "' deleted successfully from Floor '" << floorName << "'.\n";
                return;
            }
            prev = current;
            current = current->nextRelation;
        }
        cout << "Division '" << divisionName << "' not found on Floor '" << floorName << "'.\n";
    }

    // Function to Delete Child (Folder)
    void deleteChild(const string& floorName, const string& divisionName, const string& folderName) {
        displayChildren(floorName, divisionName);
        ParentNode* parent = findFloor(floorName);
        if (!parent) {
            cout << "Floor '" << floorName << "' not found.\n";
            return;
        }

        for (RelationNode* relation = parent->relations; relation; relation = relation->nextRelation) {
            if (relation->divisionName == divisionName) {
                ChildNode* current = relation->folder;
                ChildNode* prev = nullptr;

                while (current) {
                    if (current->folderName == folderName) {
                        if (prev) prev->nextChild = current->nextChild;
                        else relation->folder = current->nextChild;

                        delete current;
                        cout << "Folder '" << folderName << "' deleted successfully from Division '" << divisionName << "' on Floor '" << floorName << "'.\n";
                        return;
                    }
                    prev = current;
                    current = current->nextChild;
                }
                cout << "Folder '" << folderName << "' not found in Division '" << divisionName << "' on Floor '" << floorName << "'.\n";
                return;
            }
        }
        cout << "Division '" << divisionName << "' not found on Floor '" << floorName << "'.\n";
    }

    // Function to Find Floor (Parent)
    ParentNode* findFloor(const string& floorName) {
        for (ParentNode* current = head; current; current = current->nextParent)
            if (current->floorName == floorName) return current;
        return nullptr;
    }

    // Function to Find Relation (Division)
    RelationNode* findRelation(const string& floorName, const string& divisionName) {
        ParentNode* parent = findFloor(floorName);
        if (!parent) return nullptr;

        for (RelationNode* relation = parent->relations; relation; relation = relation->nextRelation)
            if (relation->divisionName == divisionName) return relation;
        return nullptr;
    }

    // Function to Find Child (Folder)
    ChildNode* findChild(const string& floorName, const string& divisionName, const string& folderName) {
        RelationNode* relation = findRelation(floorName, divisionName);
        if (!relation) return nullptr;

        for (ChildNode* child = relation->folder; child; child = child->nextChild)
            if (child->folderName == folderName) return child;
        return nullptr;
    }

    // Function to Display All Data
    void display() {
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent) {
            cout << "Floor: " << currentParent->floorName << "\n";
            for (RelationNode* currentRelation = currentParent->relations; currentRelation; currentRelation = currentRelation->nextRelation) {
                cout << "  Division: " << currentRelation->divisionName << "\n";
                for (ChildNode* currentChild = currentRelation->folder; currentChild; currentChild = currentChild->nextChild)
                    cout << "    Folder: " << currentChild->folderName << "\n";
            }
        }
    }

    // Function to Display All Data in List Parent
    void displayAllParents() {
        displayFloors();
    }

    // Function to Display All Data in List Relations
    void displayAllRelations() {
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent)
            displayRelations(currentParent->floorName);
    }

    // Function to Display All Data in List Child
    void displayAllChildren() {
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent)
            for (RelationNode* currentRelation = currentParent->relations; currentRelation; currentRelation = currentRelation->nextRelation)
                displayChildren(currentParent->floorName, currentRelation->divisionName);
    }

    // Function to Display Children of a Specific Parent
    void displayChildrenOfParent(const string& floorName) {
        ParentNode* parent = findFloor(floorName);
        if (!parent) {
            cout << "Floor '" << floorName << "' not found.\n";
            return;
        }
        for (RelationNode* currentRelation = parent->relations; currentRelation; currentRelation = currentRelation->nextRelation)
            displayChildren(floorName, currentRelation->divisionName);
    }

    // Function to Display Each Parent with Related Children
    void displayParentsWithChildren() {
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent) {
            cout << "Floor: " << currentParent->floorName << "\n";
            displayChildrenOfParent(currentParent->floorName);
        }
    }

    // Function to Display Each Child with Related Parent
    void displayChildrenWithParents() {
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent)
            for (RelationNode* currentRelation = currentParent->relations; currentRelation; currentRelation = currentRelation->nextRelation)
                for (ChildNode* currentChild = currentRelation->folder; currentChild; currentChild = currentChild->nextChild)
                    cout << "Folder: " << currentChild->folderName << " (Parent: " << currentParent->floorName << ")\n";
    }

    // Function to Display Parents Related to a Specific Child
    void displayParentsOfChild(const string& folderName) {
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent)
            for (RelationNode* currentRelation = currentParent->relations; currentRelation; currentRelation = currentRelation->nextRelation)
                for (ChildNode* currentChild = currentRelation->folder; currentChild; currentChild = currentChild->nextChild)
                    if (currentChild->folderName == folderName)
                        cout << "Folder: " << folderName << " (Parent: " << currentParent->floorName << ")\n";
    }

    // Function to Count Relations for Each Parent
    int countRelationsForParent(const string& floorName) {
        ParentNode* parent = findFloor(floorName);
        if (!parent) return 0;

        int count = 0;
        for (RelationNode* relation = parent->relations; relation; relation = relation->nextRelation)
            count++;
        return count;
    }

    // Function to Count Relations for a Specific Child
    int countRelationsForChild(const string& folderName) {
        int count = 0;
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent)
            for (RelationNode* currentRelation = currentParent->relations; currentRelation; currentRelation = currentRelation->nextRelation)
                for (ChildNode* currentChild = currentRelation->folder; currentChild; currentChild = currentChild->nextChild)
                    if (currentChild->folderName == folderName)
                        count++;
        return count;
    }

    // Function to Count Children without Relations
    int countChildrenWithoutRelations() {
        int count = 0;
        for (ParentNode* currentParent = head; currentParent; currentParent = currentParent->nextParent)
            for (RelationNode* currentRelation = currentParent->relations; currentRelation; currentRelation = currentRelation->nextRelation)
                if (!currentRelation->folder)
                    count++;
        return count;
    }

    // Function to Edit Relation (Division)
    void editRelation(const string& floorName, const string& oldDivisionName, const string& newDivisionName) {
        ParentNode* parent = findFloor(floorName);
        if (!parent) {
            cout << "Floor '" << floorName << "' not found.\n";
            return;
        }

        for (RelationNode* relation = parent->relations; relation; relation = relation->nextRelation) {
            if (relation->divisionName == oldDivisionName) {
                relation->divisionName = newDivisionName;
                cout << "Division '" << oldDivisionName << "' on Floor '" << floorName << "' changed to '" << newDivisionName << "'.\n";
                return;
            }
        }
        cout << "Division '" << oldDivisionName << "' not found on Floor '" << floorName << "'.\n";
    }

    // Function to Edit Child (Folder)
    void editChild(const string& floorName, const string& divisionName, const string& oldFolderName, const string& newFolderName) {
        ParentNode* parent = findFloor(floorName);
        if (!parent) {
            cout << "Floor '" << floorName << "' not found.\n";
            return;
        }

        for (RelationNode* relation = parent->relations; relation; relation = relation->nextRelation) {
            if (relation->divisionName == divisionName) {
                for (ChildNode* child = relation->folder; child; child = child->nextChild) {
                    if (child->folderName == oldFolderName) {
                        child->folderName = newFolderName;
                        cout << "Folder '" << oldFolderName << "' in Division '" << divisionName << "' on Floor '" << floorName << "' changed to '" << newFolderName << "'.\n";
                        return;
                    }
                }
                cout << "Folder '" << oldFolderName << "' not found in Division '" << divisionName << "' on Floor '" << floorName << "'.\n";
                return;
            }
        }
        cout << "Division '" << divisionName << "' not found on Floor '" << floorName << "'.\n";
    }
};

// Function to Display Insert Menu
void displayInsertMenu() {
    cout << "\n--- Insert Element Menu ---\n";
    cout << "1. Insert Parent (Floor)\n";
    cout << "2. Insert Relations (Division)\n";
    cout << "3. Insert Child (Folder)\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to Handle Insert Menu
void handleInsertMenu(MultiLinkedList& mll) {
    int choice;
    string floorName, divisionName, folderName;
    do {
        displayInsertMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid choice.\n";
            choice = -1; // Ensure it stays in the loop
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter floor name: ";
            cin >> floorName;
            mll.addFloor(floorName);
            break;
        case 2:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Enter division name: ";
            cin >> divisionName;
            mll.addRelation(floorName, divisionName);
            break;
        case 3:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Enter division name: ";
            cin >> divisionName;
            cout << "Enter folder name: ";
            cin >> folderName;
            mll.addChild(floorName, divisionName, folderName);
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            choice = -1; // Ensure it stays in the loop for invalid numeric inputs
        }
    } while (choice != 0);
}

// Function to Display Delete Menu
void displayDeleteMenu() {
    cout << "\n--- Delete Element Menu ---\n";
    cout << "1. Delete Parent (Floor)\n";
    cout << "2. Delete Relation (Division)\n";
    cout << "3. Delete Child (Folder)\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to Handle Delete Menu
void handleDeleteMenu(MultiLinkedList& mll) {
    int choice;
    string floorName, divisionName, folderName;
    do {
        displayDeleteMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            mll.displayFloors();
            cout << "Enter floor name to delete: ";
            cin >> floorName;
            mll.deleteFloor(floorName);
            break;
        case 2:
            cout << "Enter floor name: ";
            cin >> floorName;
            mll.displayRelations(floorName);
            cout << "Enter division name to delete: ";
            cin >> divisionName;
            mll.deleteRelation(floorName, divisionName);
            break;
        case 3:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Enter division name: ";
            cin >> divisionName;
            mll.displayChildren(floorName, divisionName);
            cout << "Enter folder name to delete: ";
            cin >> folderName;
            mll.deleteChild(floorName, divisionName, folderName);
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function to Display Show Menu
void displayShowMenu() {
    cout << "\n--- Show Element Menu ---\n";
    cout << "1. Show All Element\n";
    cout << "2. Show all data only in List Parent\n";
    cout << "3. Show all data only in List Relations\n";
    cout << "4. Show all data only in List Child\n";
    cout << "5. Show data child dari parent tertentu\n";
    cout << "6. Show setiap data parent beserta data child yang berelasi dengannya\n";
    cout << "7. Show data child beserta data parent yang masing-masing child miliki\n";
    cout << "8. Show data parent yang berelasi dengan child tertentu\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to Handle Show Menu
void handleShowMenu(MultiLinkedList& mll) {
    int choice;
    string floorName, folderName;
    do {
        displayShowMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            mll.display();
            break;
        case 2:
            mll.displayAllParents();
            break;
        case 3:
            mll.displayAllRelations();
            break;
        case 4:
            mll.displayAllChildren();
            break;
        case 5:
            cout << "Enter floor name: ";
            cin >> floorName;
            mll.displayChildrenOfParent(floorName);
            break;
        case 6:
            mll.displayParentsWithChildren();
            break;
        case 7:
            mll.displayChildrenWithParents();
            break;
        case 8:
            cout << "Enter folder name: ";
            cin >> folderName;
            mll.displayParentsOfChild(folderName);
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            choice = -1;
        }
    } while (choice != 0);
}

// Function to Display Find Menu
void displayFindMenu() {
    cout << "\n--- Find Element Menu ---\n";
    cout << "1. Find Element Parent\n";
    cout << "2. Find Element Relations\n";
    cout << "3. Find Element Child\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to Handle Find Menu
void handleFindMenu(MultiLinkedList& mll) {
    int choice;
    string floorName, divisionName, folderName;
    do {
        displayFindMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter floor name to find: ";
            cin >> floorName;
            if (mll.findFloor(floorName)) {
                cout << "Floor '" << floorName << "' found.\n";
            } else {
                cout << "Floor '" << floorName << "' not found.\n";
            }
            break;
        case 2:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Enter division name to find: ";
            cin >> divisionName;
            if (mll.findRelation(floorName, divisionName)) {
                cout << "Division '" << divisionName << "' found on Floor '" << floorName << "'.\n";
            } else {
                cout << "Division '" << divisionName << "' not found on Floor '" << floorName << "'.\n";
            }
            break;
        case 3:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Enter division name: ";
            cin >> divisionName;
            cout << "Enter folder name to find: ";
            cin >> folderName;
            if (mll.findChild(floorName, divisionName, folderName)) {
                cout << "Folder '" << folderName << "' found in Division '" << divisionName << "' on Floor '" << floorName << "'.\n";
            } else {
                cout << "Folder '" << folderName << "' not found in Division '" << divisionName << "' on Floor '" << floorName << "'.\n";
            }
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            choice = -1;
        }
    } while (choice != 0);
}

// Function to Display Count Menu
void displayCountMenu() {
    cout << "\n--- Count Element Menu ---\n";
    cout << "1. Count relation dari setiap element parent\n";
    cout << "2. Count relation yang dimiliki oleh child tertentu\n";
    cout << "3. Count element child yang tidak memiliki relasi\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to Handle Count Menu
void handleCountMenu(MultiLinkedList& mll) {
    int choice;
    string floorName, folderName;
    do {
        displayCountMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Number of relations for floor '" << floorName << "': " << mll.countRelationsForParent(floorName) << "\n";
            break;
        case 2:
            cout << "Enter folder name: ";
            cin >> folderName;
            cout << "Number of relations for folder '" << folderName << "': " << mll.countRelationsForChild(folderName) << "\n";
            break;
        case 3:
            cout << "Number of children without relations: " << mll.countChildrenWithoutRelations() << "\n";
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            choice = -1;
        }
    } while (choice != 0);
}

// Function to Display Edit Menu
void displayEditMenu() {
    cout << "\n--- Edit Element Menu ---\n";
    cout << "1. Edit Relasi\n";
    cout << "2. Edit Child\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to Handle Edit Menu
void handleEditMenu(MultiLinkedList& mll) {
    int choice;
    string floorName, oldDivisionName, newDivisionName, divisionName, oldFolderName, newFolderName;
    do {
        displayEditMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Enter old division name: ";
            cin >> oldDivisionName;
            cout << "Enter new division name: ";
            cin >> newDivisionName;
            mll.editRelation(floorName, oldDivisionName, newDivisionName);
            break;
        case 2:
            cout << "Enter floor name: ";
            cin >> floorName;
            cout << "Enter division name: ";
            cin >> divisionName;
            cout << "Enter old folder name: ";
            cin >> oldFolderName;
            cout << "Enter new folder name: ";
            cin >> newFolderName;
            mll.editChild(floorName, divisionName, oldFolderName, newFolderName);
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            choice = -1;
        }
    } while (choice != 0);
}

int main() {
    MultiLinkedList mll;
    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Insert Element\n";
        cout << "2. Delete Element\n";
        cout << "3. Find Element\n";
        cout << "4. Show Element\n";
        cout << "5. Count Element\n";
        cout << "6. Edit Element\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            handleInsertMenu(mll);
            break;
        case 2:
            handleDeleteMenu(mll);
            break;
        case 3:
            handleFindMenu(mll);
            break;
        case 4:
            handleShowMenu(mll);
            break;
        case 5:
            handleCountMenu(mll);
            break;
        case 6:
            handleEditMenu(mll);
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}