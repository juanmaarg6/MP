#include <iostream>
#include <algorithm>
#include "move.h"
#include "tiles.h"
#include <sstream>
using namespace std;

void Compare (const Tiles &t, const string &s) {
    cout << endl << endl;
    cout << "  "<< t.getHeight()*t.getWidth()<<"="<<s.length()<<endl;
    for (int i=0,r=0; r<t.getHeight(); r++)
        for (int c=0; c<t.getWidth(); c++, i++) 
            cout << "  " <<s[i]<<"="<<t.get(r,c);
    cout << endl;
}

int main() {
    cout << endl <<"%%%OUTPUT"<<endl;
    string s="ONE";
    Move move;
    move.set(1,1,'v',s);

    if (true) {
        cout << "BASE CONSTRUCTOR :"<<endl;
        Tiles base;
        cout << "  0="<<base.getHeight();
        cout << "  0="<<base.getWidth()<<endl;
        cout << "DESTRUCTOR ";
    }
    if (true) {
        cout << endl << endl << "PARAMETER CONSTRUCTOR :"<<endl;
        Tiles base(1,2);
        cout << "  1="<<base.getHeight();
        cout << "  2="<<base.getWidth()<<endl;
        cout << "DESTRUCTOR "<< endl;
    }
    cout <<endl<< endl << "SET/GET::"<<endl;
    Tiles base(2,2);
    cout <<"  " <<  EMPTY<<"="<<base.get(0,0);
    cout <<"  " <<  EMPTY<<"="<<base.get(0,1);
    cout <<"  " <<  EMPTY<<"="<<base.get(1,0);
    cout <<"  " <<  EMPTY<<"="<<base.get(1,1)<<endl;
    base.set(0,0,move.getLetters()[0]);
    base.set(1,1,move.getLetters()[1]);
    cout <<"  " <<  move.getLetters()[0]<<"="<<base.get(0,0);
    cout <<"  " <<  EMPTY<<"="<<base.get(0,1);
    cout <<"  " <<  EMPTY<<"="<<base.get(1,0);
    cout <<"  " <<  move.getLetters()[1]<<"="<<base.get(1,1)<<endl;
    base.set(0,1,move.getLetters()[2]);
    base.set(1,0,move.getLetters()[2]);
    cout <<"  " <<  move.getLetters()[0]<<"="<<base.get(0,0);
    cout <<"  " <<  move.getLetters()[2]<<"="<<base.get(0,1);
    cout <<"  " <<  move.getLetters()[2]<<"="<<base.get(1,0);
    cout <<"  " <<  move.getLetters()[1]<<"="<<base.get(1,1)<<endl;
    if (true) {
        cout << endl <<endl << "COPY CONSTRUCTOR/COPY::"<<endl;
        Tiles other(base);
        cout << "  2="<<other.getHeight();
        cout << "  2="<<other.getWidth()<<endl;
        cout <<"  " <<  move.getLetters()[0]<<"="<<other.get(0,0);
        cout <<"  " <<  move.getLetters()[2]<<"="<<other.get(0,1);
        cout <<"  " <<  move.getLetters()[2]<<"="<<other.get(1,0);
        cout <<"  " <<  move.getLetters()[1]<<"="<<other.get(1,1)<<endl;

        Tiles three=base;
        three.set(0,1,move.getLetters()[1]);
        three.set(1,1,EMPTY);
        string aux = s+EMPTY;
        Compare(three,aux);
        Compare(base,"OEEN");
        cout << "DESTRUCTOR "<< endl;
      
    }
    cout << endl <<endl << "ADD"<<endl;
    Tiles other(4,4);
    other.add(move);
    Compare(other, "O...N...E.......");
    move.setHorizontal('h');
    other.add(move);
    Compare(other, "ONE.N...E.......");
    move.setRow(4);
    move.setCol(3);
    other.add(move);
    Compare(other, "ONE.N...E.....ON");
    cout << endl<<endl<<"READ";
    string stile="4 4\nO N E . \nN . . . \nE . . . \n. . O N \n\n";
    istringstream is(stile);
    Tiles four;
    four.read(is);
    Compare(four, "ONE.N...E.....ON");
    cout << endl<<endl<<"PRINT";
    ostringstream os;
    four.print(os);
    cout << endl << "1="<<(os.str()==stile);
    replace(stile.begin(),stile.end(), '\n','-');
    replace(stile.begin(),stile.end(), ' ','-');
    string final = os.str();
    replace(final.begin(),final.end(), '\n','-');
    replace(final.begin(),final.end(), ' ','-');
    cout <<endl<< "INPUT:  |"<<stile <<"|" << endl<< "OUTPUT: |" << final <<"|" << endl ;
    return 0;
}