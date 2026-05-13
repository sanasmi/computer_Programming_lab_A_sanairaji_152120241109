#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Sensor {
    int sensor_id;
    float sicaklik;
};

int main() {
    int studentID;
    cout << "Enter your Student ID: ";
    cin >> studentID;
    int N = studentID % 50;
    int E = studentID % 100;
    
    fstream file("sensors.bin", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "Error opening sensors.bin file!" << endl;
        return 1;
    }
    file.seekg(N * sizeof(Sensor), ios::beg);

    Sensor tempSensor;
    file.read(reinterpret_cast<char*>(&tempSensor), sizeof(Sensor));

    if (!file) {
        cout << "Error reading record!" << endl;
        file.close();
        return 1;
    }
    float oldTemperature = tempSensor.sicaklik;
    tempSensor.sicaklik = E;
    file.seekp(N * sizeof(Sensor), ios::beg);
    file.write(reinterpret_cast<char*>(&tempSensor), sizeof(Sensor));

    if (!file) {
        cout << "Error writing record!" << endl;
        file.close();
        return 1;
    }

    file.close();
    string fileName = to_string(studentID) + "_Quiz5.txt";

    ofstream reportFile(fileName, ios::out);

    if (!reportFile) {
        cout << "Error creating report file!" << endl;
        return 1;
    }
    reportFile << "\"Number: [" << studentID << "]\"" << endl;
    reportFile << "\"Sensor Index Used in the Process: [" << N << "]\"" << endl;
    reportFile << "\"First Temperature: [" << oldTemperature
               << "] -> New Temperature: [" << tempSensor.sicaklik << "]\""
               << endl;

    reportFile.close();

    cout << "Process completed successfully!" << endl;
    cout << "Report file created: " << fileName << endl;

    return 0;
}



    
