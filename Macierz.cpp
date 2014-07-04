#include "Macierz.h"


Macierz::Macierz()
{
       // cout << "Tworze macierz i inicjalizuje ja 0!" << endl;
        vector <string> v;
        v.push_back("0");
        matrix.push_back(v);
        licz = v.size();
}
Macierz::Macierz(unsigned int row, unsigned int column)
{
        assert(row > 0 || column > 0);
        for(unsigned int i = 0; i < row; i++)
        {
            vector <int> v;
            for(unsigned int j = 0; j<column; j++)
            {
                v.push_back(rand()%1000); //INICJALIZACJA WARTOSCIAMI LOSOWYMI
            }
            matrix_int.push_back(v);
        }

}
void Macierz::show(ostream &str)
{
    for(unsigned int i = 0; i<matrix.size(); i++)
    {
        assert(licz >= matrix[i].size());
        for(unsigned int j = 0; j<licz; j++)
        {
            str << matrix[i][j] << "\t";
        }
        str << endl;
    }
}
void Macierz::push_empty_position_as_zero()
{
    for(unsigned int i = 0; i<matrix.size(); i++)
    {
        while(licz-matrix[i].size()>0)
        {
            matrix[i].push_back("0");
        }
    }
}
void Macierz::change_column(unsigned int column1, unsigned int column2)
{
    if((column1 < licz && column1 >= 0) && (column2 < licz && column2 >= 0))
    {
        vector <string> tmp;
        tmp.resize(matrix.size());
        for(unsigned int i=0; i<matrix.size(); i++)
        {
            tmp[i] = matrix[i][column1];
            matrix[i][column1]=matrix[i][column2];
            matrix[i][column2]=tmp[i];
        }

    }
    else
        cout << "nie te kolumny!" << endl;
}
void Macierz::change_row(unsigned int row1, unsigned int row2)
{
    if((row1 < matrix.size() && row1 >= 0) && (row2 < matrix.size() && row2 >= 0))
    {
        vector <string> tmp;
        tmp.resize(licz);
        for(unsigned int i=0; i<licz; i++)
        {
            tmp[i] = matrix[row1][i];
            matrix[row1][i]=matrix[row2][i];
            matrix[row2][i]=tmp[i];
        }
    }
    else
        cout << "nie te wiersze!" << endl;

}
void Macierz::add_from_csvfile()
{
    matrix.clear();
    ifstream f;
    string l;
    size_t pos = 0;
    string delimiter = ";";
    f.open("csv.txt");
    while(f.good())
    {
        getline(f, l);
        if(l.length()>0)
        {
            vector <string> v;  //dla kazdej iteracji tworzymy nowy wektor

            while((pos = l.find(delimiter)) != string::npos)
            {
                v.push_back(l.substr(0,pos));
                l.erase(0,pos + delimiter.length());
            }
            if(l.length()>0)    //jezeli wiersz nie konczy sie "delimiterem" to dopisujemy ten ciag na ostatnie miejsce wektora
                v.push_back(l);
            if(v.size()>licz)
                    licz = v.size();    //zliczamy liczbe elementow w danym wektorze i zapamietujemy najwieksza liczbe
            matrix.push_back(v);    // wpisujemy wektor v do wektora matrix
        }
    }
    push_empty_position_as_zero();
    f.close();
}
void Macierz::save_to_file()
{
    ofstream f;
    f.open("nowy.txt");
    f << *this;
    f.close();
}
void Macierz::serialize_to_csv()
{
    ofstream f;
    f.open("nowycsv.txt");
    for(unsigned int i=0; i<matrix.size(); i++)
    {
        for(unsigned int j=0; j<licz; j++)
        {
            f << matrix[i][j] << ";";
        }
        f << endl;
    }
    f.close();
}
void Macierz::serialize_to_html()
{
    ofstream f;
    f.open("nowyhtml.html");
    f << "<html><body><table border==\"1\">" << endl;
    f << "<prev>";
    for(unsigned int i=0; i<matrix.size(); i++)
    {
        f << "<tr>" << endl;
        if(i==0)
        {
            for(unsigned int j=0; j<licz; j++)
            {
                f << "<th>" << matrix[i][j] << "</th>";
            }
        }
        else
        {
            for(unsigned int j=0; j<licz; j++)
            {
                if(j==0)
                {
                    f << "<th>" << matrix[i][j] << "</th>";
                }
                else
                {
                    f << "<td title=\"" << matrix[0][j] << matrix[i][0] << "\">" << matrix[i][j] << "</td>";
                }
            }
        }
        f << "</tr>" << endl;
    }
    f << "</prev>";
    f << "</html></body></table>" << endl;
    f.close();
}
void Macierz::count_elements()
{
        for(unsigned int i=0; i<matrix.size(); i++)
        {
            for(unsigned int j=0; j<licz; j++)
                ++x[matrix.at(i).at(j)];
        }
        for(it=x.begin(); it!=x.end(); ++it)
            cout << it->first << " " << it->second << endl;
}
void Macierz::counted_elements_to_txt()
{
    ofstream f;
    f.open("zliczone.dat");
    for(it=x.begin(); it!=x.end(); ++it)
            f << it->first << " " << it->second << endl;
    f.close();
}
void Macierz::plot()
{
    system("gnuplot -p ~/Desktop/CSV/skrypt.gp");
}


///PRZECIAZENIE OPERATORA <<
ostream & operator<<(ostream &str, Macierz a)
{
    a.show(str);
    return str;

}
///-----------------------------------------------
