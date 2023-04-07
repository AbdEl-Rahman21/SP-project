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

int main() {}