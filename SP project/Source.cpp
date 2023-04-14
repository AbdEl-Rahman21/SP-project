#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>

using namespace std;

struct movie {
	string name = "\0";
	float price = 0;	//Both price and overdueFee are per day
	float overdueFee = 0;
	float rating = 0;	//From 0 to 10
	int timesRented = 0;
	int numberInStock = 5;	//Max of 5
}movies[100];

int numberOfMovies = 0;

struct customer {
	string id = "\0";
	string name = "\0";
	string email = "\0";
	string phoneNumber = "\0";
	string rentedMovies[5] = { "\0" };	//Maybe vector or (get index of movie)/(is max?)/(get index of free)
	int numberOfRentedMovies = 0;	//Max of 5
	tm rentDate[5] = { 0 };	//To display dates add 1 to months and 1900 to years.
	tm returnDate[5] = { 0 };
}customers[100];

int numberOfCustomers = 0;
int factor = 0;

int displayMenu();
int getChoice(int numberOfChoices);
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
void reset(int customerMovieIndex, int customerIndex, int& movieIndex);
void listRentingCustomers();
void listCustomerMovies(int customerIndex);
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
	int customerMovieIndex = 0;
	int customerIndex = 0;
	int movieIndex = 0;
	int rentedDays = 0;
	int overdueDays = 0;
	
	listRentingCustomers();

	customerIndex = getChoice(numberOfCustomers - factor);

	listCustomerMovies(customerIndex);

	customerMovieIndex = getChoice(5 - factor);

	overdueDays = round(difftime(time(NULL), mktime(&customers[customerIndex].returnDate[customerMovieIndex])) / 86400);

	rentedDays = round(difftime(mktime(&customers[customerIndex].returnDate[customerMovieIndex]),
		mktime(&customers[customerIndex].rentDate[customerMovieIndex])) / 86400);

	if (overdueDays < 0) {
		overdueDays = 0;
	}

	reset(customerMovieIndex, customerIndex, movieIndex);

	cout << "Your fee is: " << rentedDays * movies[movieIndex].price + overdueDays * movies[movieIndex].overdueFee << endl;
}

void listRentingCustomers() {
	for (int i = 0; i < numberOfCustomers; ++i) {
		if (customers[i].numberOfRentedMovies != 0) {
			cout << ++i - factor << "- Name: " << customers[i].name << "\tId: " << customers[i].id << endl;
		}
		else {
			++factor;
		}
	}
}

void listCustomerMovies(int customerIndex) {
	for (int i = 0; i < 5; ++i) {
		if (customers[customerIndex].rentedMovies[i] != "\0") {
			cout << ++i - factor << "- " << customers[customerIndex].rentedMovies[i] << endl;
		}
		else {
			++factor;
		}
	}
}

int getChoice(int numberOfChoices) {
	int index = 0;

	while (true) {
		cout << "Enter your choice: ";

		index = getValidNumber();

		if (index > 0 && index <= numberOfChoices) {
			--index + factor;

			break;
		}

		cout << "Error:Choice does not exist." << endl;
	}

	factor = 0;

	return index;
}

float getValidNumber() {
	float number = 0;

	cin >> number;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Enter numbers only : ";
		cin >> number;
	}

	return number;
}

void reset(int customerMovieIndex, int customerIndex, int& movieIndex) {
	for (movieIndex; movieIndex < numberOfMovies; ++movieIndex) {
		if (movies[movieIndex].name == customers[customerIndex].rentedMovies[customerMovieIndex]) {
			--movies[movieIndex].numberInStock;

			break;
		}
	}

	--customers[customerIndex].numberOfRentedMovies;
	customers[customerIndex].rentedMovies[customerMovieIndex] = "\0";
	customers[customerIndex].rentDate[customerMovieIndex] = { 0 };
	customers[customerIndex].returnDate[customerMovieIndex] = { 0 };
}

void rentMovie()
{
	addCustomer();
	int total,rent_index=0;
	cout << " Here is a list of available movies to rent : " << endl << endl;
	for (int i = 0; i < numberOfMovies; i++)
	{

		if (movies[i].numberInStock !=0) 
		{
			rent_index++;
			cout << "  " << i + 1 << ") "
				<< movies[i].name
				<< " |  Price per day :  " << movies[i].price
				<< " |  Overdue Fee :  " << movies[i].overdueFee
				<< " |  Rating :  " << movies[i].rating << "/5" << endl;
		}
	}
	int choice, days;
	cout << endl << " Enter your movie number : ";
	choice = getValidNumber();
	cout << " Enter the number of days : ";
	cin >> days;
	if (choice > 0 && choice <= rent_index)
	{
		for (int j = 0; j < choice; j++)
			total = movies[j].price * (days * 1.0);
		cout << " Your total price is : " << total << endl;
		cout << "\t\t\t\t\t * Your film is rented successfully ! *" << endl;
		movies[choice - 1].timesRented++;
		movies[choice - 1].numberInStock--;
	}
	
}