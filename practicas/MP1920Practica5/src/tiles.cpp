/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <cassert>
#include "move.h"
#include "movelist.h"
#include "tiles.h"

using namespace std;

Tiles::Tiles(){
    cell = nullptr;
    rows = 0;
    columns = 0;
}

Tiles::Tiles(int r, int c){
    cell = nullptr;
    allocate(r, c);
}

Tiles::Tiles(const Tiles& orig){
    cell = nullptr;
    copy(orig);
}

Tiles::~Tiles(){
    deallocate();
}

void Tiles::setSize(int r, int c){
    if(cell != nullptr)
        deallocate();
    
    allocate(r, c);
}

Tiles& Tiles::operator =(const Tiles& orig){
    if(this != &orig){
        copy(orig);
    }
    return *this;
}

int Tiles::getWidth() const{
    return columns;
}

int Tiles::getHeight() const{
    return rows;
}

char Tiles::get(int r, int c) const{
    assert(r >= 0 && r < getHeight());
    assert(c >= 0 && c < getWidth());
    
    return cell[r][c];
}

void Tiles::set(int r, int c, char l){
    assert(r >= 0 && r < getHeight());
    assert(c >= 0 && c < getWidth());
    
    cell[r][c] = l;
}

void Tiles::add(const Move& m){
    if(m.isHorizontal())
        for(int j = 0; j < m.getLetters().size(); j++)
            if(m.getRow() >= 1 && m.getRow() < getHeight()+1)
                if(m.getCol()+j >= 1 && m.getCol()+j < getWidth()+1)
                    set(m.getRow()-1, m.getCol()+j-1, m.getLetters()[j]);
    
    if(!m.isHorizontal())
        for(int i = 0; i < m.getLetters().size(); i++)
            if(m.getRow()+i >= 1 && m.getRow()+i < getHeight()+1)
                if(m.getCol() >= 1 && m.getCol() < getWidth()+1)
                    set(m.getRow()+i-1, m.getCol()-1, m.getLetters()[i]);
}

void Tiles::print(std::ostream & os) const{
    os << rows << " " << columns << "\n";
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++)
            os << get(i, j) << " ";
        
        os << "\n";
    }
    
    os << "\n";
}

bool Tiles::read(std::istream& is) {
    bool res = true;
    int r = 0;
    int c = 0;
    char l = 'a';
    
    is >> r >> c;
    allocate(r, c);
    
    for(int i = 0; i < getHeight() && res; i++){
        for(int j = 0; j < getWidth() && res; j++){
            is >> l;
            
            if(is.fail())
                res = false;
            
            set(i, j, l);
        }
    }
    return res;
}

void Tiles::allocate(int r, int c){
    if(cell != nullptr)
        deallocate();
    
    rows = r;
    columns = c;
    cell = new char* [r];
    for(int i = 0; i < r; i++)
        cell[i] = new char[c];
        
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            cell[i][j] = EMPTY;
}

void Tiles::deallocate(){
    if(cell != nullptr){
        for(int i = 0; i < getHeight(); i++)
            delete[] cell[i];

        delete[] cell;
    }
}

void Tiles::copy(const Tiles& t){
    if(cell != nullptr)
        deallocate();
    
    allocate(t.getHeight(), t.getWidth());

    for(int i = 0; i < t.getHeight(); i++)
        for(int j = 0; j < t.getWidth(); j++)
            set(i, j, t.get(i, j));
}