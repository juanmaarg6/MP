/**
 * @file tiles.cpp
 * @author DECSAI
 * @note To be implemented by students
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
    
    // Movimiento Horizontal
    if(m.isHorizontal())
        // Añadimos al tablero la palabra del movimiento letra a letra
        for(int i = 0, j = 0; i < m.getLetters().size(); i++) {
            
            // Contamos el número de casillas del tablero que no están vacías
            // respecto a la casilla en la que debería de colocarse realmente la letra
            while(get(m.getRow()-1, m.getCol()+i+j-1) != EMPTY) {
                j++;
            }
            
            assert(m.getRow() > 1 || m.getCol() > 1 || m.getRow() < rows || m.getCol()+i+j < columns);
                
            // Colocamos la letra en una casilla vacía y así no sobreescribimos
            // las letras del tablero
            set(m.getRow()-1, m.getCol()+i+j-1, m.getLetters()[i]);
        }
    // Movimiento Vertical
    else        
        // Añadimos al tablero la palabra del movimiento letra a letra
        for(int i = 0, j = 0; i < m.getLetters().size(); i++) {
            
            // Contamos el número de casillas del tablero que no están vacías
            // respecto a la casilla en la que debería de colocarse realmente la letra
            while(get(m.getRow()+i+j-1, m.getCol()-1) != EMPTY) {
                j++;
            }
            
            assert(m.getRow() > 1 || m.getCol() > 1 || m.getRow()+i+j < rows || m.getCol() < columns);
                   
            // Colocamos la letra en una casilla vacía y así no sobreescribimos
            // las letras del tablero
            set(m.getRow()+i+j-1, m.getCol()-1, m.getLetters()[i]);
        }
}

Move Tiles::findMaxWord(int r, int c, bool hrz) const {
    Move move;
    string word = "";
    int x = c, initial_x = c, final_x = c, y = r, initial_y = r, final_y = r;
    int i = 0;
    
    // Movimiento Horizontal
    if(hrz) {
        // Columna inicial del máximo número de letras consecutivas
        do {
            initial_x--;
            i++;
        }while(x-i >= 0 && get(y, initial_x) != EMPTY);
        initial_x++;
        
        i = 0;
        
        // Columna final del máximo número de letras consecutivas
        do {
            final_x++;
            i++;
        }while(x+i < columns && get(y, final_x) != EMPTY);
        final_x--;
        
        // Palabra formada por dichas letras consecutivas
        for(int i = initial_x; i <= final_x; i++)
            word += get(y, i);
        
        move.set(y+1, initial_x+1, 'H', word);
    }
    // Movimiento Vertical
    else {
        // Fila inicial del máximo número de letras consecutivas
        do {
            initial_y--;
            i++;
        }while(y-i >= 0 && get(initial_y, x) != EMPTY);
        initial_y++;
        
        i = 0;
        
        // Fila final del máximo número de letras consecutivas
        do {
            final_y++;
            i++;
        }while(y+i < rows && get(final_y, x) != EMPTY);
        final_y--;
        
        // Palabra formada por dichas letras consecutivas
        for(int i = initial_y; i <= final_y; i++)
            word += get(i, x);
        
        move.set(initial_y+1, x+1, 'V', word);
    }
    
    return move;
}


Movelist Tiles::findCrosswords(const Move& m, const Language& l) const {
    Tiles tiles(*this);
    Movelist movelist;
    Move move;
    int displacement = 0;    
    
    // Comprobamos si el movimiento se sale del tablero
    if(m.getRow()< 1 || m.getCol() < 1 || m.getRow() > rows || m.getCol() > columns){
        move = m;
        move.setScore(BOARD_OVERFLOW);
        movelist.add(move);
        return movelist;
    }
    
    // Comprobamos si está ocupada la posición donde 
    // queremos colocar la primera letra de nuestro movimiento
    if(get(m.getRow()-1, m.getCol()-1) != EMPTY){
        move = m;
        move.setScore(NOT_FREE);
        movelist.add(move);
        return movelist;
    }
    
    // Añadimos el movimiento a la copia del tablero. No usamos el método add de la clase Tiles
    // para poder comprobar si alguna/s de las letras de nuestro movimiento
    // se sale del tablero
    
    // Movimiento Horizontal
    if(m.isHorizontal())
        // Añadimos al tablero la palabra del movimiento letra a letra
        for(int i = 0, j = 0; i < m.getLetters().size(); i++) {
            
            // Comprobamos si está ocupada la posición donde 
            // queremos colocar la primera letra de nuestro movimiento
            if(m.getRow() < 1 || m.getCol() < 1 || m.getRow() > rows || m.getCol()+i+j > columns){
                move = m;
                move.setScore(BOARD_OVERFLOW);
                movelist.add(move);
                return movelist;
            }
            
            // Contamos el número de casillas del tablero que no están vacías
            // respecto a la casilla en la que debería de colocarse realmente la letra
            while(tiles.get(m.getRow()-1, m.getCol()+i+j-1) != EMPTY) {
                j++;
                
                // Comprobamos si la letra correspondiente se sale del tablero
                if(m.getRow() < 1 || m.getCol() < 1 || m.getRow() > rows || m.getCol()+i+j > columns){
                    move = m;
                    move.setScore(BOARD_OVERFLOW);
                    movelist.add(move);
                    return movelist;
                }
            }
            
            // Colocamos la letra en una casilla vacía y así no sobreescribimos
            // las letras del tablero
            tiles.set(m.getRow()-1, m.getCol()+i+j-1, m.getLetters()[i]);
        }
    
    // Movimiento Vertical
    else
        // Añadimos al tablero la palabra del movimiento letra a letra
        for(int i = 0, j = 0; i < m.getLetters().size(); i++) {
            
            // Comprobamos si está ocupada la posición donde 
            // queremos colocar la primera letra de nuestro movimiento
            if(m.getRow() < 1 || m.getCol() < 1 || m.getRow()+i+j > rows || m.getCol() > columns){
                move = m;
                move.setScore(BOARD_OVERFLOW);
                movelist.add(move);
                return movelist;
            }
                        
            // Contamos el número de casillas del tablero que no están vacías
            // respecto a la casilla en la que debería de colocarse realmente la letra
            while(tiles.get(m.getRow()+i+j-1, m.getCol()-1) != EMPTY) {
                j++;
                
                // Comprobamos si la letra correspondiente se sale del tablero
                if(m.getRow() < 1 || m.getCol() < 1 || m.getRow()+i+j > rows || m.getCol() > columns){
                    move = m;
                    move.setScore(BOARD_OVERFLOW);
                    movelist.add(move);
                    return movelist;
                }
            }
            
            // Colocamos la letra en una casilla vacía y así no sobreescribimos
            // las letras del tablero
            tiles.set(m.getRow()+i+j-1, m.getCol()-1, m.getLetters()[i]);
        }
    
    // Buscamos los cruces que se formarían  
    // a partir de nuestro movimiento y el resto de movimientos que ya 
    // estaban en el tablero
        
    // Movimiento Horizontal
    if(m.isHorizontal()){
        // Buscamos la palabra que se formaría a partir nuestro movimiento
        move = tiles.findMaxWord(m.getRow()-1, m.getCol()-1, true);
        move.setScore(move.findScore(l));
        
        // Comprobamos si la palabra formada no está en el diccionario
        if(move.getScore() == -1){
            move.setScore(NONEXISTENT_WORD);
            movelist.add(move);
            return movelist;
        }
        
        // Añadimos el movimiento a la lista
        movelist.add(move);
        
        // Comprobamos las palabras verticales que se formarían en el tablero
        // a partir de nuestro movimiento
        
        displacement = 0; 
        
        for(int i = 0;  i < m.getLetters().size(); i++){
            while(get(m.getRow()-1, m.getCol()+i+displacement-1) != EMPTY) {
                displacement++;
            }
            
            move = tiles.findMaxWord(m.getRow()-1, m.getCol()+i+displacement-1, false);
            
            // Consideramos un cruce si la palabra que se forma en dicho cruce
            // tiene más de 1 letra
            if(move.getLetters().size() > 1){
                move.setScore(move.findScore(l));
                
                // Comprobamos si la palabra formada no está en el diccionario
                if(move.getScore() == -1){
                    move.setScore(NONEXISTENT_WORD);
                    movelist.add(move);
                    return movelist;
                }
                
                movelist.add(move);
            }
        }
    }
    // Movimiento Vertical
    else {
        // Buscamos la palabra que se formaría a partir nuestro movimiento
        move = tiles.findMaxWord(m.getRow()-1, m.getCol()-1, false);
        move.setScore(move.findScore(l));
        
        // Comprobamos si la palabra formada no está en el diccionario
        if(move.getScore() == -1){
            move.setScore(NONEXISTENT_WORD);
            movelist.add(move);
            return movelist;
        }
        
        // Añadimos el movimiento a la lista
        movelist.add(move);
        
        // Comprobamos las palabras horizontales que se formarían en el tablero
        // a partir de nuestro movimiento
        
        displacement = 0;
        
        for(int i = 0;  i < m.getLetters().size(); i++){
            while(get(m.getRow()+i+displacement-1, m.getCol()-1) != EMPTY) {
                displacement++;
            }
            
            move = tiles.findMaxWord(m.getRow()+i+displacement-1, m.getCol()-1, true);
            
            // Consideramos un cruce si la palabra que se forma en dicho cruce
            // tiene más de 1 letra
            if(move.getLetters().size() > 1){
                move.setScore(move.findScore(l));
                
                // Comprobamos si la palabra formada no está en el diccionario
                if(move.getScore() == -1){
                    move.setScore(NONEXISTENT_WORD);
                    movelist.add(move);
                    return movelist;
                }
                
                movelist.add(move);
            }
        }
    }
    
    return movelist;
}

void Tiles::print(std::ostream & os) const{
    os << rows << " " << columns << "\n";
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++)
            os << toUTF(get(i, j)) << " ";
        
        os << "\n";
    }
    
    os << "\n";
}

bool Tiles::read(std::istream& is) {
    bool res = true;
    int r = 0;
    int c = 0;
    string s = "";
    
    is >> r >> c;
    allocate(r, c);
    
    for(int i = 0; i < getHeight() && res; i++){
        for(int j = 0; j < getWidth() && res; j++){
            is >> s;
            
            if(is.fail())
                res = false;
            
            set(i, j, toISO(s)[0]);
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