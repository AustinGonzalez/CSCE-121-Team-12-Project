//slash_screen.h
/*
1. Start with an attractive splash screen showing (at least) the name of the game, the
team number, and the team members' names. Feel free to add team members'
pictures, play music, etc.
Part 1 developed by Austin Gonzalez for Team 12.
2. Explain the storyline and how to play the game. 
Storyline written by Alexander Hupp and integrated into code architecture. 
Sources:
http://www.dreamincode.net/forums/topic/123080-c-fltk-buttons-tutorial/
*/
#include "GUI.h"
#include "Graph.h"
#include "std_lib_facilities_4.h" 
#include "top_scores.h"
#include "game.h"
using namespace Graph_lib;
//splash screen data structure
struct splash_screen : Graph_lib::Window {
    splash_screen(Point xy, int w, int h, const string& title);
    private: 
    //create objects for the window to be defined in the constructor. 
    Button play_button;
    Button yes_button;
    Button no_button;
    Image screen1;
    Image screen2;
    Image screen3;
    Image screen4;
    Image play_again;
    
    int count = 1; //used to shift screens in switch statement.
    
    static void cb_play(Address,Address pw){
        reference_to<splash_screen>(pw).play();
    }
     
    void play();
    
    static void cb_yes(Address, Address pw){
        reference_to<splash_screen>(pw).yes();
    }
    
    void yes();
    
    static void cb_no(Address, Address pw){
        reference_to<splash_screen>(pw).no();
    }
    
    void no();
    
    
};

