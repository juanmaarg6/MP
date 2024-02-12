/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <cassert>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"
#include "movelist.h"
#include "tiles.h"
#include "window.h"
#include "AnsiTerminal.h"
using namespace std;


#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
#define GENERAL_ERROR 4
#define PASSWORD "MPALABRADOS-V1"


ostream & operator<<(ostream & os, const Game & game);

istream & operator>>(istream & is, Game &game);

/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errorinfo);


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
    Move move;
    Game game;
    int w=-1, h=-1, wait=0;
    string sarg="", lang="", ifilematch="", ofilematch="", word;
    ifstream ifile; ofstream ofile;
    bool newGame=false, end=false;
    char c;
    
    /// Check arguments
    
    if(nargs > 5)
        newGame = true;
    
    // Process arguments 
    
    if(newGame) {
        for(int i = 1; i < nargs; i = i+2){
            if(i+1 >= nargs)
                errorBreak(ERROR_ARGUMENTS, "");

            sarg = args[i];

            if(sarg == "-l")
                lang = args[i+1];
            else if(sarg == "-w")
                w = atoi(args[i+1]);
            else if(sarg == "-h")
                h = atoi(args[i+1]);
            else if(sarg == "-r")
                game.random = atoi(args[i+1]);
            else if(sarg == "-save") {
                ofilematch = args[i+1];
                ofile.open(ofilematch);
                if(ofile.fail())
                    errorBreak(ERROR_OPEN, ofilematch);
            }
        }
        
        if(lang == "")
            errorBreak(ERROR_ARGUMENTS, "");
        if(w == 0 || h == 0)
            errorBreak(ERROR_ARGUMENTS, "");
    }
    
    else if(!newGame) {
        for(int i = 1; i < nargs; i = i+2){
            if(i+1 >= nargs)
                errorBreak(ERROR_ARGUMENTS, "");

            sarg = args[i];

            if(sarg == "-open") {
                ifilematch = args[i+1];
                ifile.open(ifilematch);
                if(ifile.fail())
                    errorBreak(ERROR_OPEN, ifilematch);
            }
            else if(sarg == "-save") {
                ofilematch = args[i+1];
                ofile.open(ofilematch);
                if(ofile.fail())
                    errorBreak(ERROR_OPEN, ofilematch);  
            }
        }
        
        if(ifilematch == "")
            errorBreak(ERROR_ARGUMENTS, "");
    }
    
    /// load data from file, if asked to in arguments

    if(newGame){
        game.language.setLanguage(lang);
        if(game.random >= 0)
            game.bag.setRandom(game.random);
        game.bag.define(game.language);
        game.player.add(toISO(game.bag.extract(MAXPLAYER)));
        game.tiles.setSize(h, w);
        game.score = 0;
    }
    else{
        ifile >> game;
        
        if(ifile.eof())
            errorBreak(ERROR_DATA, ifilematch);
        
        ifile.close();    
    }

    // Game's main loop 
    // 1) First set the size of the window according to the size (rows & columns) of
    // the new Tiles
    
    game.setWindowSize();
    game.doPaint();
    game.wait = wait;

    while (!end)  {
        // 2) Given the inner data members, it pretty-prints the screen
        
        game.doPaint();
        setCursorOn();
        
        // 3) Reads the movement from cin
        
        move.read(cin);
        setCursorOff();
        word = move.getLetters();
        
        if(word == "_")
            end = true;
        else if(game.player.isValid(word)) {
            // Checks whether the movement is valid accoring to the letters in player    
            // Finds all the crosswords produced by move and.crossword inform about the reasons of rejection
            
            game.crosswords = game.tiles.findCrosswords(move,game.language);
            
            //Checks that the crosswords are valid, that is either has a positive score
            // or produces at least a cross with other existin letters
                
            if ((game.crosswords.getScore() > 0 && !(game.crosswords.size() == 1 && game.crosswords.get(0).getLetters() == word && game.score > 0)) 
                || (game.crosswords.getScore() > 0 && game.acceptedmovements.size() == 0 && game.crosswords.size() > 0)){
                // Once a valid move is detected, the user is asked to confirm
                // call doConfirmCrosswords()
                
                if(game.doConfirmCrosswords("Accept movement?")) {
                    // the movement. If he/she does (by pressing Y o y) then the movement
                    // is inserted in tiles and its score is calculated,
                    // otherwise, the move is just ignored
            
                    // If valid and accepted, computes the score and adds it
                    // Show crosswords found
                    
                    game.player.extract(word);
                    game.player.add(game.bag.extract(7-game.player.size()));
                    move.setScore(game.crosswords.getScore());
                    game.acceptedmovements.add(move);
                    game.tiles.add(move);
                    game.score +=move.getScore();
                }
            // If it is a bad crosswords
            // call doBadCrosswords()
            }
            else {
                
                game.doBadCrosswords("Bad crosswords found");
                
                if(game.crosswords.size() == 1 && game.crosswords.get(0).getScore() == BOARD_OVERFLOW){
                    move.setScore(BOARD_OVERFLOW);
                }
                else if(game.crosswords.size() == 1 && game.crosswords.get(0).getScore() == NONEXISTENT_WORD){
                    move.setScore(NONEXISTENT_WORD);
                }
                else if(game.crosswords.size() == 1 && game.crosswords.get(0).getScore() == NOT_FREE){
                    move.setScore(NOT_FREE);
                }
                else if(game.crosswords.size() == 0){
                    move.setScore(MISSING_CROSSWORDS);
                }
                
                game.rejectedmovements.add(move);
            } 
        }
        // If not valid w.r.t. player
        // call doBadCrosswords()
        else {
            move.setScore(INFEASIBLE_WORD);
            game.crosswords.clear();
            game.crosswords.add(move);
            game.doBadCrosswords("Infeasible word");
            game.rejectedmovements.add(move);
        }
    }
    
    // End of game
    // Save file or print screen
    
    if(ofilematch == "") {
        cout << endl << "%%%OUTPUT" << endl;
        cout << game;
    }  
    else {
        ofile << PASSWORD << endl;
        ofile << game;  
        
        if(ofile.bad())
            errorBreak(ERROR_DATA, ofilematch);
        
        ofile.close();
    }
    
    return 0;
}

ostream & operator<<(ostream & os, const Game & game)  {
    os << game.score << '\n';
    os << game.language.getLanguage() << '\n';
    game.tiles.print(os);
    os << game.player.size() << " " << toUTF(game.player.to_string()) << '\n';
    os << game.bag.size() << " " << toUTF(game.bag.to_string()) << endl;
    
    return os;
}

istream & operator>>(istream & is, Game &game) {
    string password = "", lang = "", playerString = "", bagString = "";
    int playerSize = 0, bagSize = 0;
        
    is >> password;

    if(password != PASSWORD)
        errorBreak(ERROR_DATA, "");

    is >> game.score;
    is >> lang;
    game.language.setLanguage(lang);
    game.tiles.read(is);
    is >> playerSize;
    is >> playerString;
    game.player.add(toISO(playerString));
    is >> bagSize;
    is >> bagString;
    game.bag.set(toISO(bagString));  

    return is;
}

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use either:"<<endl;
            cerr<< "-l <language> -w <width> -h <height> [-r <randomnumber> -save <matchfile>]"<<endl;
            cerr<< "-open <matchfile> [-save <matchfile>]"<<endl;            
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
        case GENERAL_ERROR:
            cerr<<"Error: "<<errordata << endl;
            break;
    }
    std::exit(1);
}