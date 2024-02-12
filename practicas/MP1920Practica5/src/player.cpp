/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <cassert>
#include <cstring>
#include "player.h"
#include "bag.h"
///@warning complete missing #includes
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos);

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr);

// Main methods

Player::Player() {
    clear();
}

int Player::size() const {
    return strlen(letters);
}

std::string Player::to_string() const {
    string result = "";
    
    result = letters;
    
    return result;
}

void Player::clear() {
    letters[0] = '\0';
}

bool Player::isValid(const std::string s) const {
    int frequency1, frequency2 = 0;
    char word[MAXPLAYER + 1];
    char letter = 'a';
    int i = 0, j = 0;
    bool valid = true;
        
    if(s.length() <= 0 || s.length() > MAXPLAYER){
        valid = false;
    }
    else{
        strcpy(word, s.c_str());

        sortCString(word);        
        
        while(i < strlen(word) && valid == true){
            frequency1 = 0;
            frequency2 = 0;
            
            letter = word[i];
            
            j = i;
            
            while(word[j] == letter && j < strlen(word)){
                frequency1++;
                j++;
            }
            
            for(int k = 0; k < size() && frequency2 <= frequency1; k++)
                if(letter == letters[k])
                    frequency2++;
            
            if(frequency1 > frequency2)
                valid = false;
            
            i++;
        }   
    }
    
    return valid;
}

bool Player::extract(const std::string s) {
    bool correct = true;
    bool end = false;
    
    if(isValid(s)){
        for(int i = 0; i < s.length(); i++){
            end = false;
            for(int j = 0; j < size() && !end; j++)
                if(s[i] == letters[j]){
                    removeCString(letters, j);
                    end = true;
                }
        }
    }
    else{
        correct = false;
    }
    
    return correct;
}

void Player::add(std::string frombag) {
    char cs_frombag[frombag.length()];
    
    if(frombag.length() + size() <= MAXPLAYER) {
        strcpy(cs_frombag, frombag.c_str());
        strcat(letters, cs_frombag);

        sortCString(letters);
    }
}

// Auxiliary functions 

void removeCString(char *cstr, int pos) {
    assert(pos >= 0 && pos < strlen(cstr)); 
    
    for(int i = pos; i < strlen(cstr); i++)
        cstr[i] = cstr[i+1];
    
    cstr[strlen(cstr)] = '\0';

}

void sortCString(char *cstr) {
    char minimo, intercambio = 'a';
    int pos_minimo = 0;
    
    for(int izda = 0; izda < strlen(cstr); izda++) {
        minimo = cstr[izda];
        pos_minimo = izda;
        
        for(int i = izda + 1; i < strlen(cstr); i++) {
            if(cstr[i] < minimo){
                minimo = cstr[i];
                pos_minimo = i;
            }
        }
        
        intercambio = cstr[izda];
        cstr[izda] = cstr[pos_minimo];
        cstr[pos_minimo] = intercambio;
    }
}
