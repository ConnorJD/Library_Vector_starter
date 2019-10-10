#include "../includes_usr/fileIO.h"
#include <fstream>
#include <sstream>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	books.clear();
	ifstream booksStream;
	booksStream.open(filename, ios::in);

	if (!booksStream.is_open())
		return COULD_NOT_OPEN_FILE;
	std::string line;
	while (getline(booksStream, line)) {
		std::string bookid;
		std::string title;
		std::string author;
		std::string state;
		std::string loanedToPatronID;

		stringstream ss(line);
		getline(ss, bookid, ',');
		getline(ss, title, ',');
		getline(ss, author, ',');
		getline(ss, state, ',');
		getline(ss, loanedToPatronID, ',');

		book temp;
		temp.book_id = stoi(bookid, nullptr, 10);
		temp.title = title;
		temp.author = author;
		temp.state = static_cast<book_checkout_state>(stoi(state, nullptr, 10));
		temp.loaned_to_patron_id = stoi(loanedToPatronID, nullptr, 10);
		books.push_back(temp);
	}
	booksStream.close();
	if (books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	if (books.size() != 0) {
		ofstream outputstream(filename);
		if (!outputstream.is_open()) {
			return COULD_NOT_OPEN_FILE;
		}
		for (int i = 0 ; i < books.size() ; i++) {
			outputstream << books[i].book_id << "," << books[i].title << "," << books[i].author << "," << books[i].state << "," << books[i].loaned_to_patron_id << endl;
		}
		outputstream.close();
		return SUCCESS;
	}
	return NO_BOOKS_IN_LIBRARY;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	patrons.clear();
	ifstream patronStream;
	patronStream.open(filename, ios::in);

	if (!patronStream.is_open())
		return COULD_NOT_OPEN_FILE;
	std::string line;
	while (getline(patronStream, line)) {
		std::string patron_id;
		std::string name;
		std::string number_books_checked_out;

		stringstream ss(line);
		getline(ss, patron_id, ',');
		getline(ss, name, ',');
		getline(ss, number_books_checked_out, ',');

		patron temp;
		temp.patron_id = stoi(patron_id, nullptr, 10);
		temp.name = name;
		temp.number_books_checked_out = stoi(number_books_checked_out, nullptr, 10);
		patrons.push_back(temp);
	}
	patronStream.close();
	if (patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	if (patrons.size() != 0) {
		ofstream outputstream(filename);
		if (!outputstream.is_open()) {
			return COULD_NOT_OPEN_FILE;
		}
		for (int i = 0 ; i < patrons.size() ; i++) {
			outputstream << patrons[i].patron_id << "," << patrons[i].name << "," << patrons[i].number_books_checked_out << endl;
		}
		outputstream.close();
		return SUCCESS;
	}
	return NO_PATRONS_IN_LIBRARY;
}
