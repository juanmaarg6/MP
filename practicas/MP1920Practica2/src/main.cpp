/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <iostream>
#include "language.h"
#include "bag.h"
#include "player.h"
///@warning complete missing #includes

using namespace std;
/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param nwords Number of words found
 * @param score Number of letters found
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result);

/**
 * @brief Main function. 
 * @return 
 */
int main() {
    int Id;             /// To be used in bag.setRandom())
    Bag bag;            /// Bag of letters
    Player player;      /// Player set of letters
    Language language;  /// Language to be loaded from disk
    string result = "";      /// String that contains all the words found
    string lang = "";        /// String that contains the language 
    string word = "";       /// String that contains a word
    int nletters = 0;          /// Number of letters found
    int nwords = 0;          /// Number of words found
    
    /// @warning; complete code
    /*
	1. Leer un string con el ID del lenguaje, según el estándar ISO639-
	2. Crear una instancia de la clase Language con el anterior ID y
	mostrar el conjunto de caracteres permitido para ese lenguaje.
	3. Pedir un número entero, si este número es mayor o igual a ce-
	ro, iniciar el generador de números aleatorios con el número
	anterior con el método setRandom(), en otro caso, no se lla-
	ma a setRadndom() para dejar deja una inicialización aleato-
	ria. Definir el contenido de bag en base al lenguaje que se ha
	declarado anteriormente (método define()).
	4. Crear una instancia de la clase Player y llenarla por comple-
	to con caracteres de la bolsa. Este objeto player deberá estar
	siempre ordenado de la A a la Z.
	5. Pedir una palabra por teclado (en letras mayúsculas). Si esta
	palabra no es una tirada válida según el contenido de player se
	debe indicar como "INVALID!" . Si, por el contrario, la palabra
	leı́da es compatible con el contenido de player, se debe extraer
	de player de forma definitiva y volver a rellenar player con más
	letras de bag. En este caso, si esta palabra está en el diccio-
	nario elegido, indicarlo como "FOUND!" en otro caso, indicarlo
	como "NOT REGISTERED!"
	5Metodologı́a de la Programación
	MPALABRADOS (player)
	6. El programa debe terminar cuando se lea cualquier palabra de
	longitud inferior a dos caracteres.
    */
    
    cout << "TYPE LANGUAGE: ";
    cin >> lang;
    
    language.setLanguage(lang);
    
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) << "\n";
    
    cout << "TYPE SEED (>0 RANDOM): ";
    cin >> Id;
    
    if(Id >= 0)
        bag.setRandom(Id);
    
    bag.define(language);
    
    cout << "BAG (" << Id << "-" << bag.size() << "): " << toUTF(bag.to_string()) << "\n";
        
    player.add(bag.extract(7));
    
    do{
        cout << "\nPLAYER: " << toUTF(player.to_string()) << " BAG (" << bag.size() << ")";
        cout << "\nINPUT A WORD: ";
        cin >> word;
        
        if(!player.isValid(word)){
            cout << "\n" << toUTF(word) << " INVALID!\n";
        }
        else{
            if(language.query(word)){
                cout << "\n" << toUTF(word) << " FOUND!\n";
                result += word + " - ";
                nwords++;
                nletters += word.length();
                player.extract(word);
                player.add(bag.extract(word.length()));
            }
            else{
                cout << "\n" << toUTF(word) << " NOT REGISTERED!\n";
                player.extract(word);
                player.add(bag.extract(word.length()));            }
        }
    }while(word.length() >= 2);
    
    HallOfFame(language,Id,bag,player, nwords, nletters, result);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout << endl << "%%%OUTPUT\nLANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " letters found" << endl << 
            toUTF(result) << endl;    
}


