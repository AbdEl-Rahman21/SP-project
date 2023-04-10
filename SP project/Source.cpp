#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <array>
#include <ctime>

using namespace std;

struct movie {
	string name = "\0";
	float price = 0;		//Per day
	float overdueFee = 0;	//Per day
	float rating = 0;		//From 0 to 5
	bool isRented = false;
	int timesRented = 0;
}movies[100];

int numberOfMovies = 0;

struct customer {
	string name = "\0";
	string rentedMovie = "\0";
	bool isOverdue = false;
	tm rentDate = { 0 };	//To display dates add 1 to months and 1900 to years.
	tm returnDate = { 0 };	//To display dates add 1 to months and 1900 to years.
}customers[100];

int numberOfCustomers = 0;

int displayMenu();
int getCustomerNumber();
void addMovie();
void addCustomer();
void listMovies();
void listCustomers();
void listRentedMovies();
void rentMovie();
void returnMovie();
void listOverdueCustomers();
void listMostRentedMovies();
void save();
void load();
void listMostRatedMovies();
void resetCustomer(int customerIndex, int& movieIndex);
float getValidNumber();

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

void returnMovie() {
	int customerIndex = 0;
	int movieIndex = 0;
	int daysdiff = 0;
	int overdiff = 0;

	listCustomers(); //change to list renting customers

	customerIndex = getCustomerNumber();

	overdiff = difftime(time(NULL), mktime(&customers[customerIndex].returnDate)) / 86400;
	daysdiff = ceil(difftime(mktime(&customers[customerIndex].returnDate), mktime(&customers[customerIndex].rentDate)) / 86400);

	resetCustomer(customerIndex, movieIndex);

	if (overdiff < 0) {
		overdiff = 0;
	}

	cout << "Please pay: " << daysdiff * movies[movieIndex].price + overdiff * movies[movieIndex].overdueFee << endl;
}

int getCustomerNumber() {
	int index = 0;

	while (true) {
		cout << "Enter customer number: ";

		index = getValidNumber();

		if (index > 0 && index <= numberOfCustomers) {
			--index;

			break;
		}

		cout << "Error:Customer does not exist." << endl;
	}

	return index;
}

float getValidNumber() {
	float number = 0;

	cin >> number;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Enter numbers only: ";
		cin >> number;
	}

	return number;
}

void resetCustomer(int customerIndex, int& movieIndex) {
	for (movieIndex; movieIndex < numberOfMovies; ++movieIndex) {
		if (movies[movieIndex].name == customers[customerIndex].rentedMovie) {
			movies[movieIndex].isRented = false;

			break;
		}
	}

	customers[customerIndex].rentedMovie = "\0";
	customers[customerIndex].isOverdue = false;
	customers[customerIndex].rentDate = { 0 };
	customers[customerIndex].returnDate = { 0 };
}
void rentMovie()
{
	addCustomer();
	int total;
	cout << " Here is a list of available movies to rent : " << endl << endl;
	for (int i = 0; i < numberOfMovies; i++)
	{

		if (movies[i].isRented == false)
			cout << "  " << i + 1 << ") "
			<< movies[i].name
			<< " |  Price per day :  " << movies[i].price
			<< " |  Overdue Fee :  " << movies[i].overdueFee
			<< " |  Rating :  " << movies[i].rating << "/5" << endl;
	}
	int choice, days;
	cout << endl << " Enter your movie number : ";
	cin >> choice;
	cout << " Enter the number of days : ";
	cin >> days;
	if (choice > 0 && choice <= numberOfMovies)
	{
		for (int j = 0; j < choice; j++)
			total = movies[j].price * (days * 1.0);
		cout << " Your total price is : " << total << endl;
		cout << "\t\t\t\t\t * Your film is rented successfully !  *" << endl;
		movies[choice - 1].isRented = true;
		movies[choice - 1].timesRented++;
	}
}