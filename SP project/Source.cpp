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
	float rating = 0;	//From 1 to 10
	int timesRented = 0;
	int numberInStock = 5;	//Max of 5
	int numberInList = 0;
}movies[100];

int numberOfMovies = 0;

struct customer {
	int id = 0;	//same as array index
	string name = "\0";
	string email = "\0";
	int phoneNumber = 0;
	string rentedMovies[5] = { "\0" };
	int numberOfRentedMovies = 0;	//Max of 5
	int numberInList = 0;
	tm rentDate[5] = { 0 };	//To display dates add 1 to months and 1900 to years.
	tm returnDate[5] = { 0 };
}customers[100];

int numberOfCustomers = 0;

int displayMenu();
int getChoice(int numberOfChoices);
int listRentingCustomers();
int listCustomerMovies(int customerIndex);
int validCustomer();
void addMovie();
void addCustomer();
void listMovies();
void listCustomers();
void listRentedMovies();
void rentMovie();
void returnMovie();
void listOverdueCustomers();
void listMostRentedMovies();
void saveMovies();
void loadMovies();
void saveCustomers();
void loadCustomers();
void listMostRatedMovies();
void reset(int customerMovieIndex, int customerIndex, int& movieIndex);
float getValidNumber();

int main() {
	loadMovies();
	loadCustomers();

	char answer = '\0';

	do {
		system("CLS");

		switch (displayMenu()) {
		case 1:
			addMovie();

			break;
		case 2:
			//addCustomer();

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
			//listMostRentedMovies();

			break;
		case 10:
			//listMostRatedMovies();

			break;
		}

		cout << "Press 'Y' to continue or any other key to exit: ";
		cin >> answer;
	} while (answer == 'Y' || answer == 'y');

	saveMovies();
	saveCustomers();

	return 0;
}

int displayMenu() {
	cout << "\t\t Main Menu" << endl;
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
	cout << "Enter your choice: ";

	return getChoice(10);
}

void addMovie() {
	cout << "Enter movie name: ";

	cin.ignore();
	getline(cin, movies[numberOfMovies].name);

	cout << "Enter movie price: ";
	movies[numberOfMovies].price = getValidNumber();

	cout << "Enter movie overdue fee: ";
	movies[numberOfMovies].overdueFee = getValidNumber();

	cout << "Enter movie rating (max of 10): ";
	movies[numberOfMovies].rating = getChoice(10);

	++numberOfMovies;
}

void returnMovie() {
	int customerMovieIndex = 0;
	int customerIndex = 0;
	int movieIndex = 0;
	int rentedDays = 0;
	int overdueDays = 0;

	customerIndex = listRentingCustomers();

	customerMovieIndex = listCustomerMovies(customerIndex);

	overdueDays = round(difftime(time(NULL), mktime(&customers[customerIndex].returnDate[customerMovieIndex])) / 86400);

	rentedDays = round(difftime(mktime(&customers[customerIndex].returnDate[customerMovieIndex]),
		mktime(&customers[customerIndex].rentDate[customerMovieIndex])) / 86400);

	if (overdueDays < 0)
		overdueDays = 0;

	reset(customerMovieIndex, customerIndex, movieIndex);

	cout << "Total fee: " << rentedDays * movies[movieIndex].price + overdueDays * movies[movieIndex].overdueFee << " L.E" << endl;
}

int listRentingCustomers() {
	int factor = 0;
	int listNumber = 0;
	int choice = 0;

	cout << "Renting customers:-" << endl;

	for (int i = 0; i < numberOfCustomers; ++i) {
		if (customers[i].numberOfRentedMovies != 0) {
			listNumber = i + 1 - factor;

			cout << " " << listNumber << ") Name: " << customers[i].name << " | Id: " << customers[i].id << endl;

			customers[i].numberInList = listNumber;
		}
		else {
			++factor;
		}
	}

	cout << "Enter your choice: ";

	choice = getChoice(numberOfCustomers - factor);

	for (int i = 0; i < numberOfCustomers; ++i)
		if (customers[i].numberInList == choice)
			return i;
}

int listCustomerMovies(int customerIndex) {
	int numberOfMoviesInList[5] = { 0 };
	int listNumber = 0;
	int factor = 0;
	int choice = 0;

	cout << "Customer movies:-" << endl;

	for (int i = 0; i < 5; ++i) {
		if (customers[customerIndex].rentedMovies[i] != "\0") {
			listNumber = i + 1 - factor;

			cout << " " << listNumber << ") " << customers[customerIndex].rentedMovies[i] << endl;

			numberOfMoviesInList[i] = listNumber;
		}
		else {
			++factor;
		}
	}

	cout << "Enter your choice: ";

	choice = getChoice(5 - factor);

	for (int i = 0; i < 5; ++i)
		if (numberOfMoviesInList[i] == choice)
			return i;
}

int getChoice(int numberOfChoices) {
	int choice = 0;

	while (true) {
		choice = getValidNumber();

		if (choice > 0 && choice <= numberOfChoices)
			return choice;

		cout << "Error: Invalid input -- Please re - enter: ";
	}
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

void reset(int customerMovieIndex, int customerIndex, int& movieIndex) {
	for (movieIndex; movieIndex < numberOfMovies; ++movieIndex) {
		if (movies[movieIndex].name == customers[customerIndex].rentedMovies[customerMovieIndex]) {
			++movies[movieIndex].numberInStock;

			break;
		}
	}

	--customers[customerIndex].numberOfRentedMovies;
	customers[customerIndex].rentedMovies[customerMovieIndex] = "\0";
	customers[customerIndex].rentDate[customerMovieIndex] = { 0 };
	customers[customerIndex].returnDate[customerMovieIndex] = { 0 };
}

void rentMovie() {
	int days = 0;
	int movieIndex = 0;
	int customerIndex = 0;
	int freeMovieIndex = 0;
	char choice = '\0';
	time_t currentDate = time(NULL);

	cout << "Add a new customer? (Press 'Y' for yes or any other key for no): ";
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		//addCustomer();
		customerIndex = numberOfCustomers - 1;
	}
	else {
		customerIndex = validCustomer();
	}

	if (customerIndex == -1)
		return;

	for (int i = 0; i < 5; ++i) {
		if (customers[customerIndex].rentedMovies[i] == "\0") {
			freeMovieIndex = i;

			break;
		}
	}

	localtime_s(&customers[customerIndex].rentDate[freeMovieIndex], &currentDate);

	cout << "List of available movies:-" << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		if (movies[i].numberInStock != 0) {
			cout << " " << i << ") " << movies[i].name;
			cout << " | Price: " << movies[i].price;
			cout << " | Overdue fee: " << movies[i].overdueFee;
			cout << " | Rating: " << movies[i].rating << "/10" << endl;
		}
	}

	while (true) {
		cout << "Enter movie number: ";
		cin >> movieIndex;

		if (movies[movieIndex].numberInStock != 0)
			break;
		else
			cout << "Error: Invalid choice." << endl;
	}

	cout << "Enter number of days: ";
	days = getValidNumber();

	customers[customerIndex].returnDate[freeMovieIndex] = customers[customerIndex].rentDate[freeMovieIndex];
	customers[customerIndex].returnDate[freeMovieIndex].tm_mday += days;

	cout << "Total fee: " << movies[movieIndex].price * days << endl;

	currentDate = mktime(&customers[customerIndex].returnDate[freeMovieIndex]);
	localtime_s(&customers[customerIndex].returnDate[freeMovieIndex], &currentDate);

	cout << "Deadline is: " << customers[customerIndex].returnDate[freeMovieIndex].tm_mday;
	cout << "/" << customers[customerIndex].returnDate[freeMovieIndex].tm_mon + 1;
	cout << "/" << customers[customerIndex].returnDate[freeMovieIndex].tm_year + 1900 << endl;

	++movies[movieIndex].timesRented;
	--movies[movieIndex].numberInStock;
	++customers[customerIndex].numberOfRentedMovies;
	customers[customerIndex].rentedMovies[freeMovieIndex] = movies[movieIndex].name;
}

int validCustomer() {
	bool validId = false;
	bool validQuota = false;
	int id = 0;

	while (true) {
		cout << "Enter customer id: ";
		id = getValidNumber();

		for (int i = 0; i < numberOfCustomers; ++i) {
			if (customers[i].id == id) {
				validId = true;

				if (customers[i].numberOfRentedMovies < 5) {
					validQuota = true;

					return i;
				}
			}
		}

		if (validId && validQuota == false) {
			cout << "Error: Customer reached there max limit." << endl;

			return -1;
		}
		else if (validId == false) {
			cout << "Error: Invalid id." << endl;
		}
	}
}

void saveMovies() {
	ofstream moviefile;

	moviefile.open("movies.txt", ios::out | ios::trunc);

	moviefile << numberOfMovies << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		moviefile << movies[i].name << endl;
		moviefile << movies[i].price << "\t";
		moviefile << movies[i].overdueFee << "\t";
		moviefile << movies[i].rating << "\t";
		moviefile << movies[i].timesRented << "\t";
		moviefile << movies[i].numberInStock << endl;
	}

	moviefile.close();
}

void loadMovies() {
	ifstream moviefile;

	moviefile.open("movies.txt", ios::in);

	moviefile >> numberOfMovies;

	for (int i = 0; i < numberOfMovies; ++i) {
		moviefile.ignore();
		getline(moviefile, movies[i].name);

		moviefile >> movies[i].price;
		moviefile >> movies[i].overdueFee;
		moviefile >> movies[i].rating;
		moviefile >> movies[i].timesRented;
		moviefile >> movies[i].numberInStock;
	}

	moviefile.close();
}

void saveCustomers() {
	ofstream customerfile;

	customerfile.open("customers.txt", ios::out | ios::trunc);

	customerfile << numberOfCustomers << endl;

	for (int i = 0; i < numberOfCustomers; ++i) {
		customerfile << customers[i].name << endl;
		customerfile << customers[i].id << "\t";
		customerfile << customers[i].email << "\t";
		customerfile << customers[i].phoneNumber << "\t";
		customerfile << customers[i].numberOfRentedMovies << endl;

		for (int j = 0; j < 5; ++j) {
			if (customers[i].rentedMovies[j] != "\0") {
				customerfile << customers[i].rentedMovies[j] << endl;

				customerfile << customers[i].rentDate[j].tm_hour << "\t";
				customerfile << customers[i].rentDate[j].tm_mday << "\t";
				customerfile << customers[i].rentDate[j].tm_mon << "\t";
				customerfile << customers[i].rentDate[j].tm_year << "\t";
				customerfile << customers[i].rentDate[j].tm_isdst << "\t";

				customerfile << customers[i].returnDate[j].tm_hour << "\t";
				customerfile << customers[i].returnDate[j].tm_mday << "\t";
				customerfile << customers[i].returnDate[j].tm_mon << "\t";
				customerfile << customers[i].returnDate[j].tm_year << "\t";
				customerfile << customers[i].returnDate[j].tm_isdst << endl;
			}
		}
	}

	customerfile.close();
}

void loadCustomers() {
	ifstream customerfile;
	
	customerfile.open("customers.txt", ios::in);

	customerfile >> numberOfCustomers;

	for (int i = 0; i < numberOfCustomers; ++i) {
		customerfile.ignore();
		getline(customerfile, customers[i].name);

		customerfile >> customers[i].id;
		customerfile >> customers[i].email;
		customerfile >> customers[i].phoneNumber;
		customerfile >> customers[i].numberOfRentedMovies;

		for (int j = 0; j < customers[i].numberOfRentedMovies; ++j) {
			customerfile.ignore();
			getline(customerfile, customers[i].rentedMovies[j]);

			customerfile >> customers[i].rentDate[j].tm_hour;
			customerfile >> customers[i].rentDate[j].tm_mday;
			customerfile >> customers[i].rentDate[j].tm_mon;
			customerfile >> customers[i].rentDate[j].tm_year;
			customerfile >> customers[i].rentDate[j].tm_isdst;

			customerfile >> customers[i].returnDate[j].tm_hour;
			customerfile >> customers[i].returnDate[j].tm_mday;
			customerfile >> customers[i].returnDate[j].tm_mon;
			customerfile >> customers[i].returnDate[j].tm_year;
			customerfile >> customers[i].returnDate[j].tm_isdst;
		}
	}

	customerfile.close();
}

void listOverdueCustomers() {
	int overdueDays = 0;
	int rentedDays = 0;

	for (int i = 0; i < numberOfCustomers; ++i) {
		bool isOverdue = false;

		for (int j = 0; j < 5; ++j) {
			if (customers[i].rentedMovies[j] != "\0") {
				overdueDays = round(difftime(time(NULL), mktime(&customers[i].returnDate[j])) / 86400);
				rentedDays = round(difftime(mktime(&customers[i].returnDate[j]),
					mktime(&customers[i].rentDate[j])) / 86400);

				if (overdueDays > 0) {
					if (!isOverdue) {
						cout << "Name: " << customers[i].name << endl;
						cout << "Id: " << customers[i].id << endl;
						cout << "Email: " << customers[i].email << endl;
						cout << "Phone number: " << customers[i].phoneNumber << endl;

						isOverdue = true;
					}

					cout << "Movie name: " << customers[i].rentedMovies[j] << endl;
					cout << "The customer is overdue by: " << overdueDays << endl;

					for (int z = 0; z < numberOfMovies; ++z) {
						if (customers[i].rentedMovies[j] == movies[z].name) {
							cout << "Total fee: " << rentedDays * movies[z].price + overdueDays * movies[z].overdueFee << endl;

							break;
						}
					}
				}
			}
		}

		if (isOverdue)
			cout << "-------------------------------------" << endl;
	}
}

void listMovies() {
	cout << "List of movies:-" << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		cout << " Name:" << movies[i].name << endl;
		cout << " Number In Stock: " << movies[i].numberInStock << endl;
		cout << " Price: " << movies[i].price << endl;
		cout << " Overdue fee: " << movies[i].overdueFee << endl;
		cout << " Times rented: " << movies[i].timesRented << endl;
		cout << " Rating: " << movies[i].rating << "/10" << endl;
		cout << " ---------------------------------------------" << endl;
	}
}

void listCustomers() {
	cout << "List of customer:-" << endl;

	for (int i = 0; i < numberOfCustomers; ++i) {
		cout << " Name: " << customers[i].name << endl;
		cout << " Id: " << customers[i].id << endl;
		cout << " Email: " << customers[i].email << endl;
		cout << " Phone number: " << customers[i].phoneNumber << endl;
		cout << " ---------------------------------------------" << endl;
	}
}

void listRentedMovies() {
	cout << "List of rented movies:-" << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		if (movies[i].timesRented > 0) {
			cout << " Name:" << movies[i].name << endl;
			cout << " Number In Stock: " << movies[i].numberInStock << endl;
			cout << " Price: " << movies[i].price << endl;
			cout << " Overdue fee: " << movies[i].overdueFee << endl;
			cout << " Times rented: " << movies[i].timesRented << endl;
			cout << " Rating: " << movies[i].rating << "/10" << endl;
			cout << " ---------------------------------------------" << endl;
		}
	}
}