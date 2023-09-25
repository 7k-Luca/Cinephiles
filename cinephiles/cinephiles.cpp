/*
Luca Marinelli
02/11/2023
COP2335C
cinephiles.cpp

IPO Chart
  Input:
    - File Name
  Processing:
    - Load number of moves seen by students
    - Calculate average number of movies seen
    - Display the student answers and average
  Output:
    - student answers
    - average number of movies seen
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int* loadMoviesSeen(string filename, int& num_students);
double calcAverage(int* movies_seen, int num_students);
void displayMoviesSeen(int* movies_seen, int num_students);

int main() {
    string filename;
    char repeat;
    int num_students = 0;
    int* movies_seen;
    double average = 0;

    cout << "\nCollege Cinephiles Pathway Stats ... " << endl;

    do {
        cout << "\nPlease Enter Pathway File Name: ";
        cin >> filename;

        movies_seen = loadMoviesSeen(filename, num_students);
        if (movies_seen == nullptr) {
            continue;
        }

        displayMoviesSeen(movies_seen, num_students);

        average = calcAverage(movies_seen, num_students);
        cout << "Average number of movies seen: " << fixed << setprecision(0)
            << average << endl
            << endl;

        // Deallocate the array
        delete[] movies_seen;

        cout << "\nDo you have another file (y/n)? ";
        cin >> repeat;
        if (repeat == 'n') {
            cout << "Good-Bye" << endl;
            break;
        }
    } while (true);

    return 0;
}

int* loadMoviesSeen(string filename, int& num_students) {
    ifstream pathway_file(filename);

    if (!pathway_file) {
        cout << "Error opening file." << endl;
        return nullptr;
    }

    // Skip the first two lines in the file
    string pathway, college;
    getline(pathway_file, college);
    getline(pathway_file, pathway);
    cout << "\nCollege: " << college << endl;
    cout << "Pathway: " << pathway << endl;
    cout << "------------------------------" << endl;

    // Read the number of students
    pathway_file >> num_students;

    // Dynamically allocate the array
    int* movies_seen = new int[num_students];

    // Load the array with the student answers
    for (int i = 0; i < num_students; i++) {
        pathway_file >> movies_seen[i];
    }

    return movies_seen;
}

double calcAverage(int* movies_seen, int num_students) {
    double average = 0;

    for (int i = 0; i < num_students; i++) {
        average += movies_seen[i];
    }

    average /= num_students;
    return average;
}

void displayMoviesSeen(int* movies_seen, int num_students) {
    cout << "\nNumber of movies seen by " << num_students << " students" << endl;
    for (int i = 0; i < num_students; i++) {
        if (i % 10 == 0) {
            cout << endl;
        }
        cout << setw(4) << movies_seen[i];
    }
    cout << endl << endl;
}
