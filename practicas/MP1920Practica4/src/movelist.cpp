/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 *  */
#include <iostream>
#include <cassert>
#include "movelist.h"
#include "move.h"

using namespace std;

Movelist::Movelist() {
    moves = nullptr;
    nMove = 0;
    allocate(0);
}

Movelist::Movelist(int nmov) {
    moves = nullptr;
    nMove = nmov;
    allocate(nmov);
}

Movelist::Movelist(const Movelist& orig) {
    moves = nullptr;
    nMove = 0;
    copy(orig);
}

Movelist::~Movelist() {
    deallocate();
}


Movelist& Movelist::operator=(const Movelist& orig) {
    if (this != &orig)
        copy(orig);

    return *this;
}

Move Movelist::get(const int p) const {
    assert(p >= 0 && p < size());
    
    return moves[p];
}

void Movelist::set(const int p,const Move& m) {
    assert(p >= 0 && p < size());
    
    moves[p] = m;
}

int Movelist::find(const Move& mov) const {
    bool found = false;
    bool equal_moves = false;
    int pos = -1;
    
    for(int i = 0; i < size() && !found; i++) {
        equal_moves = moves[i].getCol() == mov.getCol() && 
                      moves[i].getRow() == mov.getRow() &&
                      moves[i].getLetters() == mov.getLetters() && 
                      moves[i].isHorizontal() == mov.isHorizontal();
        
        if(equal_moves){
            found = true;
            pos = i;
        }
    }
       
    return pos;
}

void Movelist::add(const Move& mov) {   
    Move *extended_moves = new Move [size()+1];
    
    if(size() == 0)
        extended_moves[0] = mov;
    else{
        for(int i = 0; i < size(); i++)
            extended_moves[i] = moves[i];
        
        extended_moves[size()] = mov;
    }
    
    deallocate();
    moves = extended_moves;
    nMove++;
}

void Movelist::remove(const Move& mov) {   
    int p = 0;
    
    p = find(mov);
            
    if(p != -1)
        remove(p);
}

void Movelist::remove(const int p) { 
    Move *reduced_moves = new Move [size()-1];

    assert(p >= 0 && p < size());

    for(int i = 0; i < p; i++)
        reduced_moves[i] = moves[i];

    for(int j = p; j < size()-1; j++)
        reduced_moves[j] = moves[j+1];


    deallocate();
    moves = reduced_moves;
    nMove--;  
}

void Movelist::zip(const Language& l) { 
    string word = "";
    bool valid = false;
    int i = 0;
    
    while(i < size()) {
        word = moves[i].getLetters();
        valid = word.length() >= 2 && l.query(word);
        
        if(!valid)
            remove(i);
        else
            i++;
    }
}

void Movelist::clear() {    
    deallocate();
    nMove = 0;
}

int Movelist::getScore() const {    
    int final_score = 0;
    int points = 0;
    bool end = false;
    
    
    for(int i = 0; i < size() && !end; i++){
        points = moves[i].getScore();
        
        if(points == -1){
            final_score = -1;
            end = true;
        }    
        else
            final_score += points;
    }
    
    return final_score;
}

bool Movelist::print(std::ostream &os, bool scores) const {
    bool res = true;
    
    for (int i = 0; i < size() && res; i++) {
        get(i).print(os);
        
        if(scores)
            os << " (" << get(i).getScore() << ") - ";
        else
            os << " - ";
        
        if (os.bad())
            res = false;
    }
    
    return res;
}

bool Movelist::read(std::istream &is) { 
    bool res = true;
    Move movement;
    
    while(movement.getLetters() != "@" && res){
        movement.read(is);

        if(is.fail())
            res = false;

        if(movement.getLetters() != "@")
            add(movement);
    }
            
    return res;
}

void Movelist::allocate(const int n) {
    if(moves != nullptr)
        deallocate();
    
    moves = new Move [n];
}

void Movelist::deallocate() { 
    if(moves != nullptr)
        delete[] moves;

    moves = nullptr;
}

void Movelist::copy(const Movelist& ml) {   
    if(moves != nullptr)
        deallocate();
    
    nMove = ml.size();
    allocate(nMove);
    for(int i = 0; i < nMove; i++)
        set(i, ml.get(i));
}