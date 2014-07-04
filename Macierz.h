#include <vector>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <map>

using namespace std;

class Macierz {
private:
    vector < vector <string> > matrix;
    vector < vector <int> > matrix_int;
    unsigned int licz;
    map <string, int> x;
    map<string, int>::iterator it;
    void push_empty_position_as_zero();
public:
    Macierz();
    Macierz(unsigned int row, unsigned int column);
    void show(ostream &str);
    void change_column(unsigned int column1, unsigned int column2);
    void change_row(unsigned int row1, unsigned int row2);
    void add_from_csvfile();
    void save_to_file();
    void serialize_to_csv();
    void serialize_to_html();
    void count_elements();
    void counted_elements_to_txt();
    void plot();
};
ostream & operator<<(ostream &str, Macierz a);
