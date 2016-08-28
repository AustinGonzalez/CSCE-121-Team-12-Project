//top_scores.h
/*
3. Ask for the player's initials and display the top 5 scores read in from the disk (see
item 6 below) followed by the player's initials. The top scores file starts out
empty. 
Developed by Austin Gonzalez for Team 12.
*/
#include "GUI.h"
#include "std_lib_facilities_4.h"
using namespace Graph_lib;
struct List{  //data structure for a list of scores and initials
    int score;
    string initials;
};
struct top_scores : Graph_lib::Window
{
    top_scores(Point xy, int w, int h, const string& title);
    int score; string initials;
    void read_file();
    
    void write_string();
    
    private:
    In_box input_initials;
    Out_box winner_1;
    Out_box winner_2;
    Out_box winner_3;
    Out_box winner_4;
    Out_box winner_5;
    Out_box display_score_1;
    Out_box display_score_2;
    Out_box display_score_3;
    Out_box display_score_4;
    Out_box display_score_5;
    Button next_button;
    Button quit_button;
    
    static void cb_next(Address,Address pw){
        reference_to<top_scores>(pw).next();
    }
    
    static void cb_quit(Address,Address pw){
        reference_to<top_scores>(pw).quit();
    }
    
    void next();   
    void quit();
};


