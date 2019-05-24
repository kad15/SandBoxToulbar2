/*
 * tb2files.cpp
 *
 *  Created on: 24 mai 2019
 *      Author: kad abeldjilali
 */

#include "tb2files.hpp"


using namespace std;

void tb2files::write_file(const string fic, const string text)
{
 ofstream file(fic);
 if(file)  // if ok
    {

        file << text;
    }
    else
    {
        cout << "File error "<<  fic << endl;
    }
    file.close();
}


void tb2files::read_file(const string & fic)
{


    ifstream file(fic,ios::in);

    if(file)
    {
        string ligne; //Une variable pour stocker les lignes lues

        while(getline(file, ligne))
        {

        }
        cout <<endl;
        cout<< "File "<<fic<<" has been read : "<<endl;

    }
    else
    {
        cout << "ERREUR: no file" << endl;
    }
    return ;

}

tb2files::tb2files() {
	// TODO Auto-generated constructor stub

}

tb2files::~tb2files() {
	// TODO Auto-generated destructor stub
}

