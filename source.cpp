
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define ll long long int

struct Library{

	ll id, signUp, noOfBooks, capacity, score=0;
	vector<ll> books;
	Library(ll id, ll signUp, ll noOfBooks, ll capacity, vector<ll> books) {
		this->id = id;
		this->signUp = signUp;
		this->noOfBooks = noOfBooks;
		this->capacity = capacity;
		this->books = books;
	}

};

struct Book {

	ll id, score;

	Book(ll id, ll score) {
		this->id = id;
		this->score = score;
	}

};

void readInput(ll& B, ll& L, ll& D, vector<Book>& bookDetails, vector<Library>& libraryDetails, string fileName) {
	
	//Reading the file into a vector<vector<ll>> variable intFile
	vector<ll> singleLine;
	vector<vector<ll>> intFile;
	string line;
	fstream newfile;
	newfile.open(fileName, ios::in);
	if (newfile.is_open()) {
		ll temp;
		while (getline(newfile, line)) {
			stringstream ss(line);
			while (ss >> temp) {
				singleLine.push_back(temp);
			}
			intFile.push_back(singleLine);
			singleLine.clear();
		}
	}

	// Reading B, L, D from intFile
	ll p = 0;
	B = intFile[p][0];
	L = intFile[p][1];
	D = intFile[p][2];
	p++;

	// Reading book scores from intFile into bookDetails vector
	for (int j = 0; j < B; j++) {
		ll id = j;
		ll bookScore = intFile[p][j];
		Book *bk = new Book(id, bookScore);
		bookDetails.push_back(*bk);
	}
	p++;

	// Reading library details from intFile into libraryDetails
	for (int j = 0; j < L; j++) {
		ll id = j;
		ll signUp = intFile[p][1], noOfBooks = intFile[p][0], capacity = intFile[p][2];
		p++;
		vector<ll> books;
		for (int i = 0; i < noOfBooks; i++) {
			books.push_back(intFile[p][i]);
		}
		p++;
		Library* lb = new Library(id, signUp, noOfBooks, capacity, books);
		libraryDetails.push_back(*lb);
	}

}

void calculateScore(vector<Library>& libraryDetails) {
	ll L = libraryDetails.size();
	for (int j = 0; j < L; j++) {
		ll ni = libraryDetails[j].noOfBooks;
		ll mi = libraryDetails[j].capacity;
		ll di = libraryDetails[j].signUp;
		ll si = 0;
		int noOfBooks = (libraryDetails[j].books).size();
		vector<ll> bookArray = libraryDetails[j].books;
		for (int i = 0; i < noOfBooks; i++) {
			si = si + bookArray[i];
		}
		// Formula to calculate the score
		ll libScore = ni * mi * si * di;
		libraryDetails[j].score = libScore;
	}
}

bool sortAscFunction(Library a, Library b) {
	return (a.score < b.score);
}

bool sortDescFunction(Library a, Library b) {
	return (a.score > b.score);
}

bool sortDescBook(pair<ll, ll> a, pair<ll, ll> b) {
	return a.second > b.second;
}

vector<vector<ll>> printOutput(vector<Library>& libraryDetails, ll& D, vector<Book>& book) {

	vector<vector<ll>> output;
	ll day = 0;
	ll libCount = 0;

	for (int j = 0; j < libraryDetails.size(); j++) {

		Library lib = libraryDetails[j];

		// Making a vector of pair book[index][score] and sorting it according to score
		vector<pair<ll, ll>> books;
		for (int k = 0; k < lib.books.size(); k++) {
			books.push_back({lib.books[k], book[lib.books[k]].score});
		}
		sort(books.begin(), books.end(), sortDescBook);

		vector<ll> scannedBooks;

		ll Day = day + lib.signUp;
		day = Day;
		ll p = 0;
		while (Day < D) {
			ll cap = lib.capacity;
			while (cap--) {
				libCount = j;
				if (p >= books.size()) break;
				scannedBooks.push_back(books[p].first);
				p++;
			}
			Day++;
		}

	 output.push_back({ lib.id });
	 output.push_back({ scannedBooks.size() });
	 output.push_back(scannedBooks);
	}

	output.insert(output.begin(), {libCount+1});

	return output;

}

void evaluateResult(vector<vector<ll>>& op, ll D, ll B, vector<Book>& books, ll& totalScore) {

	ll ans = 0;
	vector<bool> check(B, false);
	ll p = 0;
	ll A = op[p][0]; p++;
	for (int j = 0; j < A; j++) {
		ll Y = op[p][0]; p++;
		ll K = op[p][0]; p++;
		for (int i = 0; i < K; i++) {
			if (!check[op[p][i]]) {
				ans = ans + books[op[p][i]].score;
				check[op[p][i]] = true;
			}
		}
		p++;
	}

	cout << ans << endl;

	totalScore = totalScore + ans;

}

// Utility functions

void printv(vector<ll>& v) {
	for (auto x : v) {
		cout << x << " ";
	}
	cout << endl;
}

void printvv(vector<vector<ll>>& v) {
	for (auto x : v) {
		printv(x);
	}
}

void printInitializedVariables(ll& B, ll& L, ll& D, vector<Library>& libraryDetails, vector<Book>& bookDetails) {
	cout << "Verifying read function. Values of B, L, D are ";
	cout << B << " " << L << " " << D << endl;
	cout << "No of libraries read as input is " << libraryDetails.size() << endl;
	cout << "No of books read as input is " << bookDetails.size() << endl;
	cout << "Scores of books are ";
	for (int j = 0; j < B; j++) {
		cout << bookDetails[j].score << " ";
	}
	cout << endl << "Description of libraries: " << endl;

	for (int j = 0; j < L; j++) {
		cout << libraryDetails[j].noOfBooks << " " << libraryDetails[j].signUp << " " << libraryDetails[j].capacity << endl;
		printv(libraryDetails[j].books);
		cout << "Score of library is " << libraryDetails[j].score << endl;
	}

}

void printCalculatedScores(vector<Library>& libraryDetails) {
	cout << "Verifying the calculateScore function. Printing library scores " << endl;
	for (auto x : libraryDetails) {
		cout << x.score << " ";
	}
	cout << endl;
}

void printSortedLibScores(vector<Library>& libraryDetails) {
	cout << "Verifying sorting of Libraries. Printing sorted scores " << endl ;
	for (auto x : libraryDetails) {
		cout << x.score << " ";
	}
	cout << endl;
}

int main() {

	ll B, L, D;
	vector<Book> bookDetails;
	vector<Library> libraryDetails;
	ll noOfFiles = 6;
	ll totalScore = 0;

	for (int j = 0; j < noOfFiles; j++) {
		string fileName;
		if (j == 0) { fileName = "a_example.txt"; }
		else if (j == 1) { fileName = "b_read_on.txt"; }
		else if (j == 2) { fileName = "c_incunabula.txt"; }
		else if (j == 3) { fileName = "d_tough_choices.txt"; }
		else if (j == 4) { fileName = "e_so_many_books.txt"; }
		else if (j == 5) { fileName = "f_libraries_of_the_world.txt"; }

		readInput(B, L, D, bookDetails, libraryDetails, fileName); // Done, Verified.

		if (j==0) printInitializedVariables(B, L, D, libraryDetails, bookDetails); // Verifying the above function

		calculateScore(libraryDetails); // Done, Verified.

		//if (j == 1) printCalculatedScores(libraryDetails); // Verifying above function

		sort(libraryDetails.begin(), libraryDetails.end(), sortDescFunction); // Done, Verified.

		//if (j == 1) printSortedLibScores(libraryDetails); // Verifying above function

		vector<vector<ll>> output = printOutput(libraryDetails, D, bookDetails); // Done

		if (j == 0) cout << endl << "Printing the final output " << endl;
		if (j == 0) printvv(output); // Verifying the printed output
		if (j == 0) cout << endl;

		cout << endl << "Score for fileName " << fileName << " is " ;
		evaluateResult(output, D, B, bookDetails, totalScore);

		bookDetails.clear();
		libraryDetails.clear();

	}

	cout << endl << "Final score is " << totalScore << endl;
	
}