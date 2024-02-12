/**
 * @file main.cpp
 * @author @warning Fill in your full name
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <iostream>
#include <string>
#include "language.h"
#include "bag.h"
///@warning Fill missing #include

using namespace std;


/**
 * @brief Shows final data in a form detectable by autovalidation scripts
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param nwords Number of words found
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b,
        int nwords, const string &result);

/**
 * @brief Main function. 
 * @return 
 */
int main() {
    Language language;
    Bag bag;
    string word, lang, result = "";
    int random, count = 0;
    
    /// @warning Read language
    cout << "TYPE LANGUAGE: ";
    cin >> lang;
    language.setLanguage(lang);
    
    /// @warning Show allowed letters
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) << "\n";
    
    
    /// @warning Read random and define bag
    cout << "TYPE SEED (>0 RANDOM): ";
    cin >> random;
    
    if(random >= 0)
        bag.setRandom(random);
    
    bag.define(language);
        
    cout << "BAG (" << random << "-" << bag.size() << ") : " << toUTF(bag.to_string()) << "\n";

    /// @warning Extract a 5-letter word from the bag
    /// check whether it is in the dictionary or not
    /// if it is, count a new word, and aggregate the 
    /// word to result ... result = result + word +" - ";
    

    while(bag.size() > 0){
        word = bag.extract(5);

        if(language.query(word)){
            count++;
            result += word + " - ";
            cout << toUTF(word) << "***" << "\n";
        }
        else{
            cout << toUTF(word) << "\n";
        }
            
    }
   
    /// @warning Finish when the bag is empty and show results
    /// thru HallOfFame(...))
    HallOfFame(language,random, bag,count,result);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b,  
        int nwords, const string &result) {
    cout << endl <<"%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << nwords << " words found "<<endl << 
            toUTF(result) << endl;    
}


