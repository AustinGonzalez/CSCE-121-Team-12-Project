//top_scores.cpp
#include "top_scores.h"
using namespace std;
top_scores::top_scores(Point xy, int w, int h, const string& title)
    :Window{xy,w,h,title},
    input_initials{Point{x_max()-1000,100}, 50,20,"Enter your initials:"},
    winner_1{Point{x_max()-800,200},50,20,"initials:"},
    winner_2{Point{x_max()-800,300},50,20,"initials:"},
    winner_3{Point{x_max()-800,400},50,20,"initials:"},
    winner_4{Point{x_max()-800,500},50,20,"initials:"},
    winner_5{Point{x_max()-800,600},50,20,"initials:"},
    display_score_1{Point{x_max()-1000,200},50,20,"1st"},
    display_score_2{Point{x_max()-1000,300},50,20,"2nd"},
    display_score_3{Point{x_max()-1000,400},50,20,"3rd"},
    display_score_4{Point{x_max()-1000,500},50,20,"4th"},
    display_score_5{Point{x_max()-1000,600},50,20,"5th"},
    next_button{Point{x_max()-150,0},70,20,"Score"       ,cb_next},
    quit_button{Point{x_max()-70,0},70,20, "Next"       ,cb_quit}
    {
        attach(input_initials);
        attach(display_score_1);
        attach(display_score_2);
        attach(display_score_3);
        attach(display_score_4);
        attach(display_score_5);
        attach(winner_1);
        attach(winner_2);
        attach(winner_3);
        attach(winner_4);
        attach(winner_5);
        attach(next_button);
        attach(quit_button);
    }
    
//used to destroy the window but not to quit the game.
void top_scores::quit(){
    hide();
}

//used to sort the list by scores. 
bool Presort(const List &lhs, const List &rhs) { return lhs.score > rhs.score; }

//used to read the txt file into a vector.
//optimized to handle the case when txt file is empty. 
void top_scores::read_file(){
    vector<List> scores(5);
    fstream file( "scores.txt", ios::in); //opens the text file for reading/writing
    if( !file ) cerr << "Cant open" << endl; //error check. 
    while( file >> score >> initials ){
        scores.push_back({score,initials});
    }
    sort(scores.begin(),scores.end(),Presort);
    for(int i = 0; i < scores.size();++i){
        if(i > 5) { scores.erase(scores.begin()+5,scores.end()); }
    }
    file.close();
    ostringstream s1; s1 << scores[0].score; display_score_1.put(s1.str());
    ostringstream s2; s2 << scores[1].score; display_score_2.put(s2.str());
    ostringstream s3; s3 << scores[2].score; display_score_3.put(s3.str());
    ostringstream s4; s4 << scores[3].score; display_score_4.put(s4.str());
    ostringstream s5; s5 << scores[4].score; display_score_5.put(s5.str());
    ostringstream i1; i1 << scores[0].initials; winner_1.put(i1.str());
    ostringstream i2; i2 << scores[1].initials; winner_2.put(i2.str());
    ostringstream i3; i3 << scores[2].initials; winner_3.put(i3.str());
    ostringstream i4; i4 << scores[3].initials; winner_4.put(i4.str());
    ostringstream i5; i5 << scores[4].initials; winner_5.put(i5.str());
}


//takes user input and writes it to a seperate txt file.
void top_scores::write_string(){
    string input = input_initials.get_string();
	ofstream ost {"initials.txt"};                         //opens an ofstream.
	if(!ost) error("can't open input file ","initials.txt");
	ost << input; //stores new initials in txt file. 
	ost.close(); 
}

//implements functions when user clicks score button.
void top_scores::next(){
    read_file();
	write_string(); 
    redraw();
}





