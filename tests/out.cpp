/*
 * Creates a new text file programmatically.
 */
/*
 * Creating Records with Structures
 * 1. Fixed-Length records can be stored in files using structures.
 * 2. Use sizeof to find the length.
 * 3. Use binary files.
 */
#include <fstream> // Step 1
#include <iostream>
//#include <string>
#define SIZE 3
#define MAX 100
using namespace std;

struct Movie // Movie is a struct type
{
  char title[MAX];    // Title of the movie
  int year;           // Year of release
  char director[MAX]; // Director of the movie
  char genre[MAX];    // Genre of the movie
};

int main()
{
  /* Creation of a txt file - working
    ofstream outputFile;                  // Step 2. Declare an output file stream variable.
    outputFile.open("output.txt");        // Step 3. Open the file to write to.
    outputFile << "Hello world!" << endl; // Step 4 Write to the file.
    outputFile.close();                   // Step 5. Close the file.
  */

  /* Creation of a binary file - working
    // Writing a struct to a binary file
    Movie movie = {"The Godfather", 1972, "Francis Ford Coppola", "Crime"};
    fstream binaryOutputFile;
    binaryOutputFile.open("records.dat", ios::out | ios::binary); // opening to writing in binary mode
    if (binaryOutputFile.is_open())
    {
      binaryOutputFile.write(reinterpret_cast<char *>(&movie), sizeof(Movie)); // 2 args: source of the data you wanna write to the file and the size of the structure
      // reinterpret_cast<char *>(&movie), sizeof(Movie)) treats the address of the movie as a char address
      binaryOutputFile.close();
    }
    else
    {
      cout << "Error opening the file." << endl; // Error message
    }

    // Reading a struct from a binary file
    Movie newMovie;

    binaryOutputFile.open("records.dat", ios::in | ios::binary);
    if (binaryOutputFile.is_open())
    {
      binaryOutputFile.read(reinterpret_cast<char *>(&newMovie), sizeof(Movie));
      binaryOutputFile.close();
    }
    else
    {
      cout << "Error opening the file." << endl; // Error message
    }

    // Displaying the contents of the newMovie struct, from the binary file
    cout << "Title: " << newMovie.title << endl;
    cout << "Year: " << newMovie.year << endl;
    cout << "Director: " << newMovie.director << endl;
    cout << "Genre: " << newMovie.genre << endl;
  */

  Movie old_movies[SIZE] = {
      {"The Godfather", 1972, "Francis Ford Coppola", "Crime"},
      {"The Shawshank Redemption", 1994, "Frank Darabont", "Drama"},
      {"The Dark Knight", 2008, "Christopher Nolan", "Action"}}; // Array of structures

  fstream binaryOutputFile;
  binaryOutputFile.open("records.dat", ios::out | ios::binary); // opening to writing in binary mode
  if (binaryOutputFile.is_open())
  {
    for (int i = 0; i < SIZE; i++)
    {
      binaryOutputFile.write(reinterpret_cast<char *>(old_movies), SIZE * sizeof(Movie)); // 2 args: source of the data you wanna write to the file and the size of the structure
      // reinterpret_cast<char *>(old_movies), SIZE * sizeof(Movie)) don't need to use the address of the movie as a char address, because the array is already a char array.
    }
    binaryOutputFile.close();
  }
  else
  {
    cout << "Error opening the file." << endl; // Error message
  }

  Movie new_movies[SIZE];

  binaryOutputFile.open("records.dat", ios::in | ios::binary);

  if (binaryOutputFile.is_open())
  {
    binaryOutputFile.read(reinterpret_cast<char *>(new_movies), SIZE * sizeof(Movie));
    binaryOutputFile.close();
  }
  else
  {
    cout << "Error opening the file." << endl; // Error message
  }

  for (Movie &m : new_movies)
  {
    cout << "Title: " << m.title << endl;
    cout << "Year: " << m.year << endl;
    cout << "Director: " << m.director << endl;
    cout << "Genre: " << m.genre << endl;
  }
  return 0;
}