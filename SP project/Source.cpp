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

struct customer {
	string name;
	string rentedMovie;
	bool isOverdue;
	tm rentDate;
	tm returnDate;
}customers[100];

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
	int option;
	cout << " Main Menu" << endl;
	cout << "***********   " << endl;
	cout << "Press" << endl;
	cin >> option;
	cout << "1) Add Movie" << endl << "2) Add customer" << endl << "3) List all customers" << endl << "4) List all movies" << endl << "5) List all rented movies" << endl <<
		"6) Rent Movie" << endl << "7) Summary of overdue customers" << endl << "8) List most rented movies" << endl << "9) List the highest rated movies" << endl << "10) Return Movie" <<endl;

	switch (option)
	{
	case 1: addMovie(); break;
	case 2:addCustomer(); break;
	case 3:listCustomers(); break;
	case 4:listMovies(); break;
	case 5:listRentedMovies(); break;
	case 6:rentMovie(); break;
	case 7:listOverdueCustomers(); break;
	case 8:listMostRentedMovies(); break;
	case 9:listMostRatedMovies(); break;
	case 10:returnMovie(); break;
	default: cout << "Invalid Input"; // lazm hena nzbt eno yrg3 lel options tani

	}
	return 0;
}