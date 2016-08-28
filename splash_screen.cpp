//splash_screen.cpp
#include "splash_screen.h"
using namespace std; //used for debugging 
//initialize objects in constructor 
splash_screen::splash_screen(Point xy, int w, int h, const string& title) 
    :Window{xy,w,h,title},
    screen1{Point{0,20},"screen1.jpg"},
    screen2{Point{0,20},"Storyline.jpg"},
    screen3{Point{0,20},"game_instructions.jpg"},
    screen4{Point{0,20},"screen4.jpg"},
    play_again{Point{x_max()-762,200},"task6.jpg"},
    play_button{Point{x_max()-70,0},70,20,"Next", cb_play}, 
    yes_button{Point{x_max()-762,300},100,100,"Yes",cb_yes},
    no_button{Point{x_max()-462,300},100,100,"No",cb_no} 
{
        attach(play_button);
        attach(screen1); //default screen
}
void splash_screen::yes(){
    count = 0; //resets count to 0 to implement a user loop.
    detach(yes_button);
    detach(no_button);
    detach(play_again);
    play();
}

void splash_screen::no(){
    hide();
}


void splash_screen::play(){
    count++; //move to next screen 
     switch(count) {  //switches when the play button is clicked. 
            case 1: {attach(screen1); break;};
            case 2: {detach(screen1);attach(screen2);break;};
            case 3: {detach(screen2);attach(screen3);break;};
            case 4: {
                detach(screen3);
                top_scores* window = new top_scores(Point{100,100},1125,750,"top_scores"); //runs top_scores window. 
                window -> show();
                break;
            };
            case 5: {
                game* game_window = new game(Point{100,100},1125,750,"What A Lovely Day");
                game_window -> show();
                break;
            };
            case 6: { attach(yes_button); attach(no_button); attach(play_again); break;};
            default: {attach(screen1);};
    }
    redraw(); //redraws screen after every switch made in the case structure. 
}





