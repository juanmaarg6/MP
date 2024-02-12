/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <iostream>
#include <string>
#include "language.h"
#include "move.h"

using namespace std;

Move::Move() {
    set(0, 0, 'H', "");
    setScore(0);
}

void Move::set(int r, int c, char h, const std::string  &l) {
    setRow(r);
    setCol(c);
    setHorizontal(h);
    setLetters(l);
}

void Move::setRow(int r) {
    row = r;
}

void Move::setCol(int c) {
    column = c;
}

void Move::setHorizontal(char h) {
    if(toupper(h) == 'H')
        ishorizontal = true;
    else
        ishorizontal = false;
}

void Move::setLetters(const std::string &l) {
    letters = l;
}

int Move::findScore(const Language &l) const {
    string word = getLetters();
    int score = 0;
    
    if(l.query(word))
        for(int i = 0; i < word.length(); i++)
            score += l.getScore(word[i]);
    else
        score = -1; 
    
    return score;
}

void Move::setScore(int s) {
    score = s;
}

int Move::getScore() const {
    return score;
}

int Move::getRow() const {
    return row;
}

int Move::getCol() const {
    return column;
}

bool Move::isHorizontal() const {
    return ishorizontal;
}

std::string Move::getLetters() const {
    return letters;
}

void Move::print(std::ostream &os) const {
    char orientation = 'V';
    
    if(ishorizontal)
        orientation = 'H';
    
    os << orientation << " " << row << " " << column << " " << letters;
}

void Move::read(std::istream &is) {
    char orientation = 'V';
    
    if(ishorizontal)
        orientation = 'H';
    
    is >> orientation >> row >> column >> letters;
}