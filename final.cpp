#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
//file headers

//allows for std:: to not be used
using namespace std;

//planet class
class Planet {
    
private:
    string name;
    double diameter;
    double mass;

public:
    Planet(string name, double diameter, double mass)
        : name(name), diameter(diameter), mass(mass) {}

    //accessors for private members
    const string& getName() const {
        return name;
    }
    //accessors for private members
    double getDiameter() const {
        return diameter;
    }
    //accessors for private members
    double getMass() const {
        return mass;
    }
    //formula for surface area
    double surfaceArea() const {
        return (4 * M_PI * pow((diameter/2), 2));
    }
    //formula for density
    double density() const {
        return (mass / ((1.333 * M_PI * pow(((diameter * 1000) / 2), 3))));
    }
    //formula for acceleration due to gravity
    double accelerationDueToGravity() const {
        return ((6.674e-11 * mass) / pow(((diameter * 1000) / 2), 2));
    }
    //what will be displayed when user searches for planet
    void printDetails() const {
        cout << "Name: " << name << endl;
        cout << scientific << setprecision(3);
        cout << "Diameter: " << diameter << " km" << endl;
        cout << "Mass: " << mass << " kg" << endl;
        cout << "Surface Area: " << surfaceArea() << " km^2" << endl;
        cout << "Density: " << density() << " kg/m^3" << endl;
        cout << "Acceleration Due To Gravity: " << accelerationDueToGravity() << " m/s^2" << endl;
    }
};


//function to add planet
void addPlanet(vector<Planet>& planets) {
    string name;
    double diameter, mass;

    cout << "Enter Planet Name: ";
    cin >> name;
    cout << "Enter Diameter (km): ";
    cin >> diameter;
    cout << "Enter Mass In Scientific Notation (kg), ex: 3.4e10: ";
    cin >> scientific >> mass;

    planets.push_back(Planet(name, diameter, mass));
}


//function to delete planet
void deletePlanet(vector<Planet>& planets) {
    string name;
    cout << "Enter Planet Name To Delete: ";
    cin >> name;

    auto it = find_if(planets.begin(), planets.end(), [&name](const Planet& p) { return p.getName() == name; });
    if (it != planets.end()) {
        planets.erase(it);
        cout << "Planet " << name << " Was Deleted Successfully.\n";
    } else {
        cout << "ERROE: PLANET NOT FOUND\n";
    }
}


//function to find planet
void findPlanet(const vector<Planet>& planets) {
    string name;
    cout << "Enter Planet Name To Find: ";
    cin >> name;

    auto it = find_if(planets.begin(), planets.end(), [&name](const Planet& p) { return p.getName() == name; });
    if (it != planets.end()) {
        it->printDetails();
    } else {
        cout << "ERROR: PLANET NOT FOUND\n";
    }
}

//function to display all planets
void showAllPlanets(const vector<Planet>& planets) {
    if (planets.empty()) {
        cout << "ERROR: NO PLANETS ENTERED IN SYSTEM\n";
    } else {
        for (const auto& planet : planets) {
            planet.printDetails();
            cout << "-----------------------\n";
        }
    }
}

//insertion function to sort planets
void sortPlanets(vector<Planet>& planets) {
    int n = planets.size();
    for (int i = 1; i < n; ++i) {
        Planet key = planets[i];
        int j = i - 1;

        //moves elements of planets[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && planets[j].getName() > key.getName()) {
            planets[j + 1] = planets[j];
            j = j - 1;
        }
        planets[j + 1] = key;
    }
}

//function that stores a planets information as a vector
void writeToFile(const vector<Planet>& planets) {
    ofstream outfile("planet_data.txt");
    if (outfile.is_open()) {
        for (const auto& planet : planets) {
            outfile << planet.getName() << " " << planet.getDiameter() << " " << planet.getMass() << "\n";
        }
        outfile.close();
        cout << "Data Written To File Successfully.\n";
    } else {
        cout << "ERROR: UNABLE TO OPEN FILE\n";
    }
}


//function that reads the file from planet_data.txt
void readFromFile(vector<Planet>& planets) {
    ifstream infile("planet_data.txt");
    if (infile.is_open()) {
        string name;
        double diameter, mass;
        while (infile >> name >> diameter >> mass) {
            planets.push_back(Planet(name, diameter, mass));
        }
        infile.close();
        cout << "(Data Read From File Successfully)";
    } else {
        cout << "(No Previous Data Found)";
    }
}


//beginning of main function
int main() {
    vector<Planet> planets;

    //reads data from file if available
    readFromFile(planets);

    int choice;
    do {
    //beginning of do loop
        cout << "\n\nPlanet Tracker!\n\n";
        cout << "1. Add Planet\n";
        cout << "2. Delete Planet\n";
        cout << "3. Find Planet\n";
        cout << "4. List All\n";
        cout << "5. Sort Planets\n";
        cout << "6. Quit \n";
        cout << "Enter Choice: ";
        cin >> choice;
        cout << "\n";

        // Validate user input
        while (choice < 1 || choice > 6 || cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "ERROR: ENTER NUMBER IN THE RANGE 1-6: ";
            cin >> choice;
            cout << "\n";
        }

        switch (choice) {
        //beginning of switch
                
            //add planet
            case 1:
                addPlanet(planets);
                break;
                
            //delete planet
            case 2:
                deletePlanet(planets);
                break;
                
            //find planet
            case 3:
                findPlanet(planets);
                break;
                
            //displays all planets
            case 4:
                showAllPlanets(planets);
                break;
                
            //sorts planets alphabetically
            case 5:
                sortPlanets(planets);
                cout << "Planets Sorted Alphabetically.\n";
                break;
                
            //program will save data when user quits program
            case 6:
                writeToFile(planets);
                cout << "Exiting Program. Data saved.\n";
                break;
            //default:
               // cout << "Invalid Choice. Try again.\n";
                break;
        //end of switch
        }
        
    //Do loop will keep running until the user inputs #6 (quit); end of do loop
    } while (choice != 6);
    
    //program executed successfully
    return 0;
    
//end of main function
}
