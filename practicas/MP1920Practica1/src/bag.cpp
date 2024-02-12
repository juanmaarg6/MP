/**
 * @file bag.cpp
 * @author DECSAI
 * @note To be implemented by students except function shuffle()
 */
#include <cassert>
#include <random>
#include <algorithm>
#include <string>
#include <cstring>
#include "language.h"
#include "bag.h"

///@warning Fill missing #include

using namespace std;

/**
 * @brief Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @author DECSAI
 */
void shuffleVector(char *s, int n, int id);

/**
 * @brief Removes a position from a vector and compacts the remaining positions, 
 * thus reducing its size
 * @param s Vector of char
 * @param n Number of chars
 * @param p Position to remove
 * @warning TO BE FULLY IMPLEMENTED. 
 * @warning Check parameters const/&/* and their types
 */
void removeVector(char *s, int &n, int p);


// Main methods

char Bag::get(int p) const{
    if(p > 0 && p < nletters)
        return letters[p];
}		

void Bag::set(int p, char c) {
    if(p > 0 && p < nletters)
        letters[p] = c;
}
        
Bag::Bag() {
    nletters = 0;
    id = time(NULL);
}

void Bag::setRandom(int _id) {
    id = _id;
}

void Bag::define(const Language &l) {
    string aux_letters;
    int frequency;
    
    aux_letters = l.getLetterSet();
        
    for(int i = 0; i < aux_letters.size(); i++){
        frequency = l.getFrequency(aux_letters[i]);
        
        for(int j = 0; j < frequency; j++){
            letters[nletters] = aux_letters[i];
            nletters++;
        }
    }
       
    shuffleVector(letters, nletters, id);
}

int Bag::size() const {
    return nletters;
}

std::string Bag::to_string() const {
    string _letters = "";
    
    for(int i = 0; i < nletters; i++)
        _letters.push_back(letters[i]);
    
    return _letters;
}

void Bag::set(const std::string &s) {
    strcpy (letters, s.c_str());
    
    shuffleVector(letters, nletters, id);
}

std::string Bag::extract(const int n) {
    
    string extracted_letters = "";
    char cs_extracted_letters[MAXBAG];

    if(size() > n){
        for(int i = 0; i < n; i++)
            cs_extracted_letters[i] = letters[i];
        
        extracted_letters = cs_extracted_letters; 
        
        for(int i = 0; i < n; i++)
            removeVector(letters, nletters, 0);
    }
    else{ 
        while(size() != 0){
            extracted_letters.push_back(letters[0]);
            removeVector(letters, nletters, 0);
        }
    }
    
    return extracted_letters;
}



///@warning Implement all the methods

// Auxiliary functions 

void shuffleVector(char *s, int n, int id) {
    vector <char> aux(s, s+n);
    unsigned seed = id;
    std::shuffle(aux.begin(), aux.end(), std::default_random_engine(seed));
    for (int i=0; i<n; i++)
        s[i] = aux[i];    
}

void removeVector(char *s, int &n, int p) {
    if(p >= 0 && p < n){
        int tope = n - 1;
        
        for(int i = p; i < tope; i++){
            s[i] = s[i+1];
        }
        
        n--;
    }
}



