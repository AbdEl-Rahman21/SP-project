#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <ctime>

using namespace std;

struct movie {
	string name;
	float price;
	float overdueFee;
	float rating; //From 0 to 5
	bool isRented;
	int timesRented;
}movies[100];

int numberOfMovies = 0;

struct customer {
	string name;
	string rentedMovie;
	bool isOverdue;
	tm rentDate;
	tm returnDate;
}customers[100];

int numberOfCustomers = 0;

int displayMenu();
void addMovie();
void addCustomer();
void listMovies();
void listCustomers();
void listRentedMovies();
void rentMovie();
void returnMovie();
float calcOverdueFees();
void listOverdueCustomers();
void listMostRentedMovies();
void save();
void load();
void listMostRatedMovies();

int main() {
	char answer = '\0';

	do {
		switch (displayMenu()) {
		case 1:
			addMovie();

			break;
		case 2:
			addCustomer();

			break;
		case 3:
			listCustomers();

			break;
		case 4:
			listMovies();

			break;
		case 5:
			listRentedMovies();

			break;
		case 6:
			rentMovie();

			break;
		case 7:
			returnMovie();

			break;
		case 8:
			listOverdueCustomers();

			break;
		case 9:
			listMostRentedMovies();

			break;
		case 10:
			listMostRatedMovies();

			break;
		default: 
			cout << "Invalid choice!" << endl;
			cout << "Please re - enter the correct one." << endl;

			answer = 'y';

			continue;
		}

		cout << "Press 'Y' to continue or any other key to exit: ";
		cin >> answer;
	} while (answer == 'Y' || answer == 'y');

	return 0;
}

int displayMenu() {
	int option = 0;

	cout << "\t\tMain Menu" << endl;
	cout << "\t\t***********" << endl;
	cout << "Press:-" << endl;
	cout << "1) Add Movie" << endl;
	cout << "2) Add customer" << endl;
	cout << "3) List all customers" << endl;
	cout << "4) List all movies" << endl;
	cout << "5) List all rented movies" << endl;
	cout << "6) Rent Movie" << endl;
	cout << "7) Return Movie" << endl;
	cout << "8) Summary of overdue customers" << endl;
	cout << "9) List most rented movies" << endl;
	cout << "10) List the highest rated movies" << endl;
	cin >> option;

	return option;
}