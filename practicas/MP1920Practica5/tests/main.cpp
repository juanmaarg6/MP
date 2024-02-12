/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */


#include <iostream>
#include <string>
#include <fstream>
#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"
#include "movelist.h"
#include "tiles.h"

using namespace std;


#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
#define PASSWORD "MPALABRADOS-V1"
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
    Language language;
    Bag bag;
    Player player;
    Move move;
    Movelist originalmovements, legalmovements, 
             acceptedmovements, rejectedmovements;
    Tiles tiles;
    int width = 0, height = 0, id = 0, score = 0, bagSize = 0, playerSize = 0;
    string sarg = "", password= "", word = "", lang = "", ifilename = "", 
           ofilename = "", matchfilename = "", bagString = "", 
           playerString = "";
    bool newGame = false;
    ifstream ifile, matchfile;
    ofstream ofile;
    istream *input_ifile, *input_matchfile;
    ostream *output = &cout;
/*

 * 1) El main() recibe múltiples parámetros de entrada, distinguiendo
entre dos modos de funcionamiento.

    * a) Empezar una partida nueva. Para ello los parámetros de
llamada serán
-l <lang> -w <int> -h <int> -p <pfile> [-r <int> -save <matchfile>]
especificando el diccionario, el ancho y alto del tablero de
juego, el fichero de movimientos registrados y, opcional-
mente, el número aleatorio y la posibilidad de salvar la la
jugada en un fichero con extensión .match con la opción
-save . En caso de que no se indique esta última opción,
entonces deberá mostrar el estado final de la partida con el
mismo formato (ver Sección ??).

     * b) Continuar una partida existente. Para ello los parámetros
de llamada serán
5Metodologı́a de la Programación
MPALABRADOS (tiles-1)
-open <matchfile> -p <playfile> [-save <matchfile>]
indicando la apertura de un fichero .match desde el que
se restaura el estado anterior de la partida, y un fichero
de movimientos. Opcionalmente, se podrá grabar la partida
final si se indica el parámetro -save comentado antes.

 * 2. Crear una instancia de la clase Language con el ID indicado.

 * 3. Crear una instancia de la clase Bag, si es una partida nueva,
inicializar la bolsa, en otro caso, cargarla directamente desde el
fichero .match

 * 4. Crear una instancia de la clase Player y inicializarla por com-
pleto con caracteres de la bolsa o bien leerla del fichero .match.

 * 5. Crear una instancia de la clase Tiles y dimensionarla según
los parámetros leı́dos, bien desde la lı́nea de comandos, bien
desde el fichero .match.

 * 6. Crear una instancia de la clase bf Movelist llamada original
y leer todos los movimientos desde el fichero indicado en el
parámetro -p usando operador sobrecargado >>

 * 7. Crear una instancia de Movelist llamada legal que contenga
sólo los movimientos de original que están en el diccionario
del lenguaje elegido. Usar, para ello, el método zip(...)

 * 8. Crear dos instancias adicionales de Movelist y llamarlas accepted
y rejected

 * 9. Recorrer toda la lista de movimientos leı́da y, por cada uno de
ellos.

     * a) Si el movimiento está en el diccionario, añadir la palabra a
la lista accepted , calcular su puntuación, según el idioma
y acumularla. A continuación, se deberá colocar cada mo-
vimiento en su posición correspondiente en la instancia de
Tiles creada anteriormente, ignorando aquellos caracteres
que caigan fuera de las dimensiones permitidas y sobrees-
cribiendo los caracteres que se crucen.

     * b) En otro caso añadirla a la lista rejected .

 * 10. Terminar mostrando el estado de la partida en pantalla o guardándo-
lo en disco según la presencia o no de -save .
11. Si en cualquier momento se presenta un error en los argumen-
tos, en la apertura de ficheros o en la lectura de datos del fiche-
ro, se debe usar la función errorBreak(...) para notificar el error
y parar el programa 
 */
        
    if(nargs > 7)
        newGame = true; 
    
    if(newGame) {
        for(int i = 1; i < nargs; i = i+2){
            if(i+1 >= nargs)
                errorBreak(ERROR_ARGUMENTS, "");

            sarg = args[i];

            if(sarg == "-l")
                lang = args[i+1];
            else if(sarg == "-w")
                width = atoi(args[i+1]);
            else if(sarg == "-h")
                height = atoi(args[i+1]);
            else if(sarg == "-p") {
                ifilename = args[i+1];
                ifile.open(ifilename.c_str());
                if(ifile.fail())
                    errorBreak(ERROR_OPEN, ifilename);
                input_ifile = &ifile;
            }
            else if(sarg == "-r")
                id = atoi(args[i+1]);
            else if(sarg == "-save") {
                ofilename = args[i+1];
                ofile.open(ofilename.c_str());
                if(ofile.fail())
                    errorBreak(ERROR_OPEN, ofilename);
                output = &ofile;    
            }
        }
        
        if(lang == "" || ifilename == "")
            errorBreak(ERROR_ARGUMENTS, "");
        if(width == 0 || height == 0)
            errorBreak(ERROR_ARGUMENTS, "");
        
        if(output != &ofile)
            output = &cout;
    }
    
    else if(!newGame) {
        for(int i = 1; i < nargs; i = i+2){
            if(i+1 >= nargs)
                errorBreak(ERROR_ARGUMENTS, "");

            sarg = args[i];

            if(sarg == "-open") {
                matchfilename = args[i+1];
                matchfile.open(matchfilename.c_str());
                if(matchfile.fail())
                    errorBreak(ERROR_OPEN, matchfilename);
                input_matchfile = &matchfile;
            }
            else if(sarg == "-p") {
                ifilename = args[i+1];
                ifile.open(ifilename.c_str());
                if(ifile.fail())
                    errorBreak(ERROR_OPEN, ifilename);
                input_ifile = &ifile;
            }
            else if(sarg == "-save") {
                ofilename = args[i+1];
                ofile.open(ofilename.c_str());
                if(ofile.fail())
                    errorBreak(ERROR_OPEN, ofilename);
                output = &ofile;    
            }
        }
        
        if(matchfilename == "" || ifilename == "")
            errorBreak(ERROR_ARGUMENTS, "");
        
        if(output != &ofile)
            output = &cout;
    }
    
    if(newGame) {
        language.setLanguage(lang);
        if(id >= 0)
            bag.setRandom(id);
        bag.define(language);
        player.add(bag.extract(MAXPLAYER));
        tiles.setSize(height, width);
    }
    else {
        matchfile >> password;
        
        if(password != PASSWORD)
            errorBreak(ERROR_DATA, matchfilename);
        
        matchfile >> score;
        matchfile >> lang;
        
        if(matchfile.eof())
            errorBreak(ERROR_DATA, matchfilename);
        
        language.setLanguage(lang);
        tiles.read(*input_matchfile);
        matchfile >> playerSize;
        matchfile >> playerString;
        player.add(toISO(playerString));
        
        if(matchfile.eof())
            errorBreak(ERROR_DATA, matchfilename);
        
        matchfile >> bagSize;
        matchfile >> bagString;
        bag.set(toISO(bagString));
    }
    
    originalmovements.read(*input_ifile);
    if(ifile.eof())
        errorBreak(ERROR_DATA, ifilename);    
    
    legalmovements = originalmovements;
    legalmovements.zip(language);
    
    for(int i = 0; i < legalmovements.size(); i++){        
        move = legalmovements.get(i);
        word = legalmovements.get(i).getLetters();

        if(!player.isValid(word))
            rejectedmovements.add(move);
        else{
            player.extract(word);
            player.add(bag.extract(word.length()));
            
            move.setScore(move.findScore(language));
            
            acceptedmovements.add(move);
            
            tiles.add(move);
        }         
    }    
    
    if(newGame)
        score = acceptedmovements.getScore();
    else
        score = score + acceptedmovements.getScore();
                
    
    if(ofilename == "") {
        cout << endl << "%%%OUTPUT" << endl;
        cout << score << endl;
        cout << lang << endl;
        tiles.print(*output);
        cout << player.size() << " " << toUTF(player.to_string()) << endl;
        cout << bag.size() << " " << toUTF(bag.to_string()) << endl;
    }  
    else {
        ofile << PASSWORD << endl;
        ofile << score << endl;
        ofile << lang << endl;
        tiles.print(*output);
        ofile << player.size() << " " << toUTF(player.to_string()) << endl;
        ofile << bag.size() << " " << toUTF(bag.to_string()) << endl;    
    }
        
    ifile.close();
            
    if(ofilename != "")
        ofile.close();
    
    if(!newGame)
        matchfile.close();
    
    return 0;
}


void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use either:"<<endl;
            cerr<< "-l <language> -w <width> -h <height> -p <playfile> [-r <randomnumber> -save <matchfile>]"<<endl;
            cerr<< "-open <matchfile> -p <playfile> [-save <matchfile>]"<<endl;            
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
    }
    std::exit(1);
}