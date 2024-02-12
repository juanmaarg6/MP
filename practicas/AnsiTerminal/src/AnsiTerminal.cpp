/**
 * @file AnsiTerminal.cpp
 * @author DECSAI
 * @brief Full functional static library of tools to use a coloured terminal (4 bits per pixel),
 * manage cursor position, resize the terminal window according to standard
 * ANSI escape codes. See https://en.wikipedia.org/wiki/ANSI_escape_code for further details
 * @note Fully implemented. No further implementation required.
 */
#include <iostream>
#include <string>
#include <cmath>
#include "AnsiTerminal.h"
using namespace std;

const int bpp=4, bmax = (int) pow(2, bpp), base = bmax-1;
int bg=black, fg=white;

int setColor(double r, double g, double b)  {
    int ir = (int)(r*base)%bmax,
        ig = (int)(g*base)%bmax,
        ib = (int)(b*base)%bmax;
    int res= ir+(ig<<bpp)+(ib<<(2*bpp));
    return res;
}

double getRed(int color) {
    return (color & base)*1.0/base;
}

double getGreen(int color) {
    return ((color & (base<<bpp))>>bpp)*1.0/base;
}

double getBlue(int color) {
    return ((color & (base<<(2*bpp)))>>(2*bpp))*1.0/base;
}

int getText() {
    return fg;
}

int getBackground() {
    return bg;
}
void setCursorXY(int x, int y) {
    cout << ESC << "["<<y<<";"<<x<<"f"; 
}

void clearScreen() {
    cout << ESC << "[2J";
    setCursorXY(1,1);
}

void setBackground(int color) {
    bg=color;
    int r=(int)(255*getRed(color)), 
        g=(int)(255*getGreen(color)), 
        b=(int)(255*getBlue(color));
//    int f=127*(1+(getBackground()&8)>>3),
//        r=f+(getBackground()&1)*127, 
//        g=f+((getBackground()&2)>>1)*127, 
//        b=f+((getBackground()&4)>>2)*127;
    string s = "[48;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m";
    cout << ESC << s;    
}

void setText(int color) {
    fg=color;
    int r=(int)(255*getRed(color)), 
        g=(int)(255*getGreen(color)), 
        b=(int)(255*getBlue(color));
//    int f=127*(1+(getText()&8)>>3),
//        r=f+(getText()&1)*127, 
//        g=f+((getText()&2)>>1)*127, 
//        b=f+((getText()&4)>>2)*127;
    string s = "[38;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m";
    cout << ESC << s;    
}

void setCursorOn() {
    cout << ESC << "[?25h";    
}

void setCursorOff() {
    cout << ESC <<"[?25l";
}

void doRectangle(int x, int y, int w, int h, int color) {
    int oldbg=getBackground();
    setBackground(color);
    for (int i=0; i<w; i++)
        for (int j=0; j<h; j++) {
            setCursorXY(x+i,y+j);
            cout << " ";
        }
    setBackground(oldbg);
}

void pressReturn() {
    cin.ignore(); 
////    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');    
//    if (!cin.eof()) cin.ignore(1);
////    while (cin.get());
//    while (cin.get()!='\n');
////    while (cin.get());
}

void setSize(int r, int c) {
    string command="resize -s "+to_string(r)+" "+to_string(c); 
    system(command.c_str());
}

