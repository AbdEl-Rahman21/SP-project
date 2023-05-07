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
	int numberInStock = 0;	//Max of 5
	int numberInList = 0;
};

struct customer {
	string name = "\0";
	string email = "\0";
	string rentedMovies[5] = { "\0" };
	int id = 0;	//Same as array index
	int phoneNumber = 0;
	int numberOfRentedMovies = 0;	//Max of 5
	int numberInList = 0;
	tm rentDate[5] = { 0 };	//To display dates add 1 to months and 1900 to years.
	tm returnDate[5] = { 0 };
};

tm getCurrentTime();
int displayMenu();
int getChoice(int numberOfChoices);
int listRentingCustomers(customer customers[], int numberOfCustomers);
int listCustomerMovies(customer customers[], int customerIndex);
int validCustomer(customer customers[], int numberOfCustomers);
void addMovie(movie movies[], int& numberOfMovies);
void addCustomer(customer customers[], int& numberOfCustomers);
void listMovies(movie movies[], int numberOfMovies);
void listCustomers(customer customers[], int numberOfCustomers);
void listRentedMovies(movie movies[], int numberOfMovies);
void rentMovie(movie movies[], customer customers[], int numberOfMovies, int& numberOfCustomers);
void returnMovie(movie movies[], customer customers[], int numberOfMovies, int numberOfCustomers);
void listOverdueCustomers(movie movies[], customer customers[], int numberOfMovies, int numberOfCustomers);
void listMostRentedMovies(movie movies[], int numberOfMovies);
void saveMovies(movie movies[], int numberOfMovies);
void loadMovies(movie movies[], int& numberOfMovies);
void saveCustomers(customer customers[], int numberOfCustomers);
void loadCustomers(customer customers[], int& numberOfCustomers);
void listMostRatedMovies(movie movies[], int numberOfMovies);
void reset(movie movies[], customer customers[], int numberOfMovies, int customerMovieIndex, int customerIndex, int& movieIndex);
float getValidNumber();

int main() {
	int numberOfMovies = 0;
	int numberOfCustomers = 0;
	char answer = '\0';
	movie movies[50];
	customer customers[50];

	loadMovies(movies, numberOfMovies);
	loadCustomers(customers, numberOfCustomers);

	do {
		system("CLS");

		switch (displayMenu()) {
		case 1:
			addMovie(movies, numberOfMovies);

			break;
		case 2:
			addCustomer(customers, numberOfCustomers);

			break;
		case 3:
			listMovies(movies, numberOfMovies);

			break;
		case 4:
			listCustomers(customers, numberOfCustomers);

			break;
		case 5:
			listRentedMovies(movies, numberOfMovies);

			break;
		case 6:
			rentMovie(movies, customers, numberOfMovies, numberOfCustomers);

			break;
		case 7:
			returnMovie(movies, customers, numberOfMovies, numberOfCustomers);

			break;
		case 8:
			listOverdueCustomers(movies, customers, numberOfMovies, numberOfCustomers);

			break;
		case 9:
			listMostRentedMovies(movies, numberOfMovies);

			break;
		case 10:
			listMostRatedMovies(movies, numberOfMovies);

			break;
		}

		cout << "Press 'Y' to continue or any other key to exit: ";
		cin >> answer;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (answer == 'Y' || answer == 'y');

	saveMovies(movies, numberOfMovies);
	saveCustomers(customers, numberOfCustomers);

	return 0;
}

void loadMovies(movie movies[], int& numberOfMovies) {
	ifstream movieFile;

	movieFile.open("movies.txt", ios::in);

	movieFile >> numberOfMovies;

	for (int i = 0; i < numberOfMovies; ++i) {
		movieFile.ignore();
		getline(movieFile, movies[i].name);

		movieFile >> movies[i].price;
		movieFile >> movies[i].overdueFee;
		movieFile >> movies[i].rating;
		movieFile >> movies[i].timesRented;
		movieFile >> movies[i].numberInStock;
	}

	movieFile.close();
}

void loadCustomers(customer customers[], int& numberOfCustomers) {
	ifstream customerFile;

	customerFile.open("customers.txt", ios::in);

	customerFile >> numberOfCustomers;

	for (int i = 0; i < numberOfCustomers; ++i) {
		customerFile.ignore();
		getline(customerFile, customers[i].name);

		customerFile >> customers[i].id;
		customerFile >> customers[i].email;
		customerFile >> customers[i].phoneNumber;
		customerFile >> customers[i].numberOfRentedMovies;

		for (int j = 0; j < customers[i].numberOfRentedMovies; ++j) {
			customerFile.ignore();
			getline(customerFile, customers[i].rentedMovies[j]);

			customerFile >> customers[i].rentDate[j].tm_mday;
			customerFile >> customers[i].rentDate[j].tm_mon;
			customerFile >> customers[i].rentDate[j].tm_year;
			customerFile >> customers[i].rentDate[j].tm_isdst;

			customerFile >> customers[i].returnDate[j].tm_mday;
			customerFile >> customers[i].returnDate[j].tm_mon;
			customerFile >> customers[i].returnDate[j].tm_year;
			customerFile >> customers[i].returnDate[j].tm_isdst;
		}
	}

	customerFile.close();
}

int displayMenu() {
	cout << "\t\t Main Menu" << endl;
	cout << "\t\t***********" << endl;
	cout << "Press:-" << endl;
	cout << "1) Add Movie" << endl;
	cout << "2) Add customer" << endl;
	cout << "3) List all movies" << endl;
	cout << "4) List all customers" << endl;
	cout << "5) List all rented movies" << endl;
	cout << "6) Rent Movie" << endl;
	cout << "7) Return Movie" << endl;
	cout << "8) Summary of overdue customers" << endl;
	cout << "9) List most rented movies" << endl;
	cout << "10) List the highest rated movies" << endl;
	cout << "Enter your choice: ";

	return getChoice(10);
}

void addMovie(movie movies[], int& numberOfMovies) {
	cout << "Enter movie name: ";
	getline(cin, movies[numberOfMovies].name);

	cout << "Enter movie price: ";
	movies[numberOfMovies].price = getValidNumber();

	cout << "Enter movie overdue fee: ";
	movies[numberOfMovies].overdueFee = getValidNumber();

	cout << "Enter movie rating (max of 10): ";
	movies[numberOfMovies].rating = getChoice(10);

	movies[numberOfMovies].numberInStock = 5;
	++numberOfMovies;
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

int getChoice(int numberOfChoices) {
	int choice = 0;

	while (true) {
		choice = getValidNumber();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choice > 0 && choice <= numberOfChoices)
			return choice;

		cout << "Error: Invalid input -- Please re - enter: ";
	}
}

void addCustomer(customer customers[], int& numberOfCustomers) {
	cout << "Enter customer name: ";
	getline(cin, customers[numberOfCustomers].name);

	cout << "Enter customer email: ";
	cin >> customers[numberOfCustomers].email;

	cout << "Enter customer phone number: ";
	customers[numberOfCustomers].phoneNumber = getValidNumber();
	customers[numberOfCustomers].id = numberOfCustomers;
	cout << " Customer ID : " << customers[numberOfCustomers].id << endl;
	cout << "\t\t\t * Customer is added * " << endl;
	++numberOfCustomers;
}

void listMovies(movie movies[], int numberOfMovies) {
	cout << "List of movies:-" << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		cout << " Name: " << movies[i].name << endl;
		cout << " Number In Stock: " << movies[i].numberInStock << endl;
		cout << " Price: " << movies[i].price << endl;
		cout << " Overdue fee: " << movies[i].overdueFee << endl;
		cout << " Times rented: " << movies[i].timesRented << endl;
		cout << " Rating: " << movies[i].rating << "/10" << endl;
		cout << " ________________________________________" << endl;
	}
}

void listCustomers(customer customers[], int numberOfCustomers) {
	cout << "List of customer:-" << endl;

	for (int i = 0; i < numberOfCustomers; ++i) {
		cout << " Name: " << customers[i].name << endl;
		cout << " Id: " << customers[i].id << endl;
		cout << " Email: " << customers[i].email << endl;
		cout << " Phone number: " << customers[i].phoneNumber << endl;
		cout << " ___________________________________________" << endl;
	}
}

void listRentedMovies(movie movies[], int numberOfMovies) {
	cout << "List of rented movies:-" << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		if (movies[i].numberInStock < 5) {
			cout << " Name: " << movies[i].name << endl;
			cout << " Number In Stock: " << movies[i].numberInStock << endl;
			cout << " Price: " << movies[i].price << endl;
			cout << " Overdue fee: " << movies[i].overdueFee << endl;
			cout << " Times rented: " << movies[i].timesRented << endl;
			cout << " Rating: " << movies[i].rating << "/10" << endl;
			cout << " ___________________________________________" << endl;
		}
	}
}

void rentMovie(movie movies[], customer customers[], int numberOfMovies, int& numberOfCustomers) {
	int days = 0;
	int movieIndex = 0;	
	int customerIndex = 0;
	int freeMovieIndex = 0;
	char choice = '\0';
	time_t temp = 0;

	cout << "Add a new customer? (Press 'Y' for yes or any other key for no): ";
	cin >> choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (choice == 'y' || choice == 'Y') {
		addCustomer(customers, numberOfCustomers);

		customerIndex = numberOfCustomers - 1;
	}
	else {
		customerIndex = validCustomer(customers, numberOfCustomers);
	}

	if (customerIndex == -1)
		return;

	for (int i = 0; i < 5; ++i) {
		if (customers[customerIndex].rentedMovies[i] == "\0") {
			freeMovieIndex = i;

			break;
		}
	}

	customers[customerIndex].rentDate[freeMovieIndex] = getCurrentTime();
	cout << "List of available movies:-" << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		bool isRented = false;

		if (movies[i].numberInStock != 0) {
			for (int j = 0; j < 5; ++j) {
				if (customers[customerIndex].rentedMovies[j] == movies[i].name) {
					isRented = true;

					break;
				}
			}

			if (!isRented) {
				cout << " " << i << ") " << movies[i].name;
				cout << " | Price: " << movies[i].price;
				cout << " | Overdue fee: " << movies[i].overdueFee;
				cout << " | Rating: " << movies[i].rating << "/10" << endl;
			}
		}
	}

	while (true) {
		bool isRented = false;
		cout << "Enter movie number: ";

		movieIndex = getValidNumber();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (movies[movieIndex].numberInStock != 0) {
			for (int i = 0; i < 5; ++i) {
				if (customers[customerIndex].rentedMovies[i] == movies[movieIndex].name) {
					isRented = true;

					cout << "Error: Invalid choice." << endl;

					break;
				}
			}

			if (!isRented)
				break;
		}
		else {
			cout << "Error: Invalid choice." << endl;
		}
	}

	while (true) {
		cout << "Enter number of days: ";

		days = getValidNumber();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (days < 1)
			cout << "Error: Invalid number of days.";
		else
			break;
	}

	customers[customerIndex].returnDate[freeMovieIndex] = customers[customerIndex].rentDate[freeMovieIndex];
	customers[customerIndex].returnDate[freeMovieIndex].tm_mday += days;

	cout << "Total fee: " << movies[movieIndex].price * days << " L.E" << endl;

	temp = mktime(&customers[customerIndex].returnDate[freeMovieIndex]);
	localtime_s(&customers[customerIndex].returnDate[freeMovieIndex], &temp);

	cout << "Deadline is: " << customers[customerIndex].returnDate[freeMovieIndex].tm_mday;
	cout << "/" << customers[customerIndex].returnDate[freeMovieIndex].tm_mon + 1;
	cout << "/" << customers[customerIndex].returnDate[freeMovieIndex].tm_year + 1900 << endl;
	cout << "\t\t\t\t\tMovie Rented Successfully!" << endl;

	++movies[movieIndex].timesRented;
	--movies[movieIndex].numberInStock;
	++customers[customerIndex].numberOfRentedMovies;
	customers[customerIndex].rentedMovies[freeMovieIndex] = movies[movieIndex].name;
}

int validCustomer(customer customers[], int numberOfCustomers) {
	int id = 0;

	while (true) {
		cout << "Enter customer id: ";
		id = getValidNumber();

		for (int i = 0; i < numberOfCustomers; ++i) {
			if (customers[i].id == id) {
				if (customers[i].numberOfRentedMovies == 5) {
					cout << "Error: Customer reached there max limit." << endl;

					return -1;
				}
				else {
					return i;
				}
			}
		}

		cout << "Error: Invalid id." << endl;
	}
}

tm getCurrentTime() {
	time_t temp1 = time(NULL);
	tm temp2 = { 0 };

	localtime_s(&temp2, &temp1);

	temp2.tm_hour = 0;

	return temp2;
}

void returnMovie(movie movies[], customer customers[], int numberOfMovies, int numberOfCustomers) {
	int customerMovieIndex = 0;
	int customerIndex = 0;
	int movieIndex = 0;
	int rentedDays = 0;
	int overdueDays = 0;
	tm temp = getCurrentTime();

	customerIndex = listRentingCustomers(customers, numberOfCustomers);

	customerMovieIndex = listCustomerMovies(customers, customerIndex);

	overdueDays = round(difftime(mktime(&temp), mktime(&customers[customerIndex].returnDate[customerMovieIndex])) / 86400);

	rentedDays = difftime(mktime(&customers[customerIndex].returnDate[customerMovieIndex]),
		mktime(&customers[customerIndex].rentDate[customerMovieIndex])) / 86400;

	if (overdueDays < 0)
		overdueDays = 0;

	reset(movies, customers, numberOfMovies, customerMovieIndex, customerIndex, movieIndex);

	cout << "Total fee: " << rentedDays * movies[movieIndex].price + overdueDays * movies[movieIndex].overdueFee << " L.E" << endl;
}

int listRentingCustomers(customer customers[], int numberOfCustomers) {
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

int listCustomerMovies(customer customers[], int customerIndex) {
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

void reset(movie movies[], customer customers[], int numberOfMovies, int customerMovieIndex, int customerIndex, int& movieIndex) {
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

void listOverdueCustomers(movie movies[], customer customers[], int numberOfMovies, int numberOfCustomers) {
	int overdueDays = 0;
	int rentedDays = 0;
	tm temp = getCurrentTime();

	for (int i = 0; i < numberOfCustomers; ++i) {
		bool isOverdue = false;

		for (int j = 0; j < 5; ++j) {
			if (customers[i].rentedMovies[j] != "\0") {
				overdueDays = round(difftime(mktime(&temp), mktime(&customers[i].returnDate[j])) / 86400);
				rentedDays = difftime(mktime(&customers[i].returnDate[j]),
					mktime(&customers[i].rentDate[j])) / 86400;

				if (overdueDays > 0) {
					if (!isOverdue) {
						cout << "Name: " << customers[i].name << endl;
						cout << "Id: " << customers[i].id << endl;
						cout << "Email: " << customers[i].email << endl;
						cout << "Phone number: " << customers[i].phoneNumber << endl;

						isOverdue = true;
					}

					cout << "Movie name: " << customers[i].rentedMovies[j] << endl;
					cout << "The customer is overdue by: " << overdueDays << " days" << endl;

					for (int z = 0; z < numberOfMovies; ++z) {
						if (customers[i].rentedMovies[j] == movies[z].name) {
							cout << "Total fee: " << rentedDays * movies[z].price + overdueDays * movies[z].overdueFee << " L.E" << endl;

							break;
						}
					}
				}
			}
		}

		if (isOverdue)
			cout << "________________________________________" << endl;
	}
}

void listMostRentedMovies(movie movies[], int numberOfMovies) {
	int maxTimesRented[3] = { 0 };
	int movieIndex[3] = { 0 };

	for (int i = 0; i < numberOfMovies; ++i) {
		if (movies[i].timesRented > maxTimesRented[0]) {
			maxTimesRented[0] = movies[i].timesRented;
			movieIndex[0] = i;
		}
		else if (movies[i].timesRented > maxTimesRented[1]) {
			maxTimesRented[1] = movies[i].timesRented;
			movieIndex[1] = i;
		}
		else if (movies[i].timesRented > maxTimesRented[2]) {
			maxTimesRented[2] = movies[i].timesRented;
			movieIndex[2] = i;
		}
	}

	cout << "Top 3 rented movies:-" << endl;

	for (int i = 0; i < 3; ++i) {
		cout << " Name: " << movies[movieIndex[i]].name << endl;
		cout << " Times rented: " << movies[movieIndex[i]].timesRented << endl;
		cout << "______________________________________________" << endl;
	}
}

void listMostRatedMovies(movie movies[], int numberOfMovies) {
	int temp[3][2] = { 0 };

	for (int i = 0; i < numberOfMovies; ++i) {
		if (temp[0][0] < movies[i].rating) {
			//shift elements from 2 to 3
			temp[2][0] = temp[1][0];
			temp[2][1] = temp[1][1];
			//shift elements from 1 to 2
			temp[1][0] = temp[0][0];
			temp[1][1] = temp[0][1];
			//new element in 1
			temp[0][0] = movies[i].rating;
			temp[0][1] = i;
		}
		else if (temp[1][0] < movies[i].rating) {
			//shift elements from 2 to 3
			temp[2][0] = temp[1][0];
			temp[2][1] = temp[1][1];
			//new element in 2
			temp[1][0] = movies[i].rating;
			temp[1][1] = i;
		}
		else if (temp[2][0] < movies[i].rating) {
			temp[2][0] = movies[i].rating;
			temp[2][1] = i;
		}
	}

	cout << "Top 3 rated movies:-" << endl;

	for (int i = 0; i < 3; ++i) {
		cout << " Name: " << movies[temp[i][1]].name << endl;
		cout << " Rating: " << movies[temp[i][1]].rating << endl;
		cout << "______________________________________________" << endl;
	}
}

void saveMovies(movie movies[], int numberOfMovies) {
	ofstream movieFile;

	movieFile.open("movies.txt", ios::out | ios::trunc);

	movieFile << numberOfMovies << endl;

	for (int i = 0; i < numberOfMovies; ++i) {
		movieFile << movies[i].name << endl;
		movieFile << movies[i].price << "\t";
		movieFile << movies[i].overdueFee << "\t";
		movieFile << movies[i].rating << "\t";
		movieFile << movies[i].timesRented << "\t";
		movieFile << movies[i].numberInStock << endl;
	}

	movieFile.close();
}

void saveCustomers(customer customers[], int numberOfCustomers) {
	ofstream customerFile;

	customerFile.open("customers.txt", ios::out | ios::trunc);

	customerFile << numberOfCustomers << endl;

	for (int i = 0; i < numberOfCustomers; ++i) {
		customerFile << customers[i].name << endl;
		customerFile << customers[i].id << "\t";
		customerFile << customers[i].email << "\t";
		customerFile << customers[i].phoneNumber << "\t";
		customerFile << customers[i].numberOfRentedMovies << endl;

		for (int j = 0; j < 5; ++j) {
			if (customers[i].rentedMovies[j] != "\0") {
				customerFile << customers[i].rentedMovies[j] << endl;

				customerFile << customers[i].rentDate[j].tm_mday << "\t";
				customerFile << customers[i].rentDate[j].tm_mon << "\t";
				customerFile << customers[i].rentDate[j].tm_year << "\t";
				customerFile << customers[i].rentDate[j].tm_isdst << "\t";

				customerFile << customers[i].returnDate[j].tm_mday << "\t";
				customerFile << customers[i].returnDate[j].tm_mon << "\t";
				customerFile << customers[i].returnDate[j].tm_year << "\t";
				customerFile << customers[i].returnDate[j].tm_isdst << endl;
			}
		}
	}

	customerFile.close();
}