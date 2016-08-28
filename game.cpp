//game.cpp
#include "game.h"
using namespace std;
game::game(Point xy, int w, int h, const string& title)
    :Window{xy,w,h,title},
    world_map{Point{0,0},"world.jpg"},
	seed_set(false),
    splat1(Point{ x[0] , y[0] },10),
    splat2(Point{ x[1] , y[1] },10),
    splat3(Point{ x[2] , y[2] },10),
    splat4(Point{ x[3] , y[3] },10),
    splat5(Point{ x[4] , y[4] },10),
    splat6(Point{ x[5] , y[5] },10),
    splat7(Point{ x[6] , y[6] },10),
    splat8(Point{ x[7] , y[7] },10),
    North{Point{x_max()-1000, 650},50,50,"North",cb_north},
    South{Point{x_max()-1000, 700},50,50,"South",cb_south},
    East{Point{x_max()-950,700},50,50,"East",cb_east},
    West{Point{x_max()-1050,700},50,50,"West",cb_west},
    total_score{Point{x_max()-250,0},70,20,"Score:"},
    moves_left{Point{x_max()-240,50},60,20,"Moves Left:"},
    show_hint{Point{x_max()-240,100},60,20,"Move Splat:"},
    show_time{Point{x_max()-240,150},60,20,"Time Left:"},
    select_splat1{Point{x_max()-70,200},70,20, "Splat1",cb_splat1},
    select_splat2{Point{x_max()-70,220},70,20, "Splat2",cb_splat2},
    select_splat3{Point{x_max()-70,240},70,20, "Splat3",cb_splat3},
    select_splat4{Point{x_max()-70,260},70,20, "Splat4",cb_splat4},
    select_splat5{Point{x_max()-70,280},70,20, "Splat5",cb_splat5},
    select_splat6{Point{x_max()-70,300},70,20, "Splat6",cb_splat6},
    select_splat7{Point{x_max()-70,320},70,20, "Splat7",cb_splat7},
    select_splat8{Point{x_max()-70,340},70,20, "Splat8",cb_splat8},
    rect1{Point{x_max()-140,200},50,20},
    rect2{Point{x_max()-140,220},50,20},
    rect3{Point{x_max()-140,240},50,20},
    rect4{Point{x_max()-140,260},50,20},
    rect5{Point{x_max()-140,280},50,20},
    rect6{Point{x_max()-140,300},50,20},
    rect7{Point{x_max()-140,320},50,20},
    rect8{Point{x_max()-140,340},50,20},
    level_menu{Point{x_max()-70,30},70,20,Menu::vertical,"Level"},
    menu_button{Point{x_max()-80,30},80,20,"Select Level:", cb_menu},
    next_button{Point{x_max()-150,0},70,20,"Play"       ,cb_next},
    hint_button{Point{x_max()-150,30},50,20,"Hint:", cb_hint},
    quit_button{Point{x_max()-70,0},70,20, "Quit"       ,cb_quit}
    
    {
        attach(world_map);
        attach(next_button);
        attach(quit_button);
        attach(hint_button);
        attach(North);
        attach(South);
        attach(East);
        attach(West);
        attach(total_score);
        attach(moves_left);
        attach(show_hint);
        attach(show_time);
        level_menu.attach(new Button{Point{0,0},0,0,"level 2",cb_level2});
        level_menu.attach(new Button{Point{0,0},0,0,"level 3",cb_level3});
        level_menu.attach(new Button{Point{0,0},0,0,"level 4",cb_level4});
        level_menu.attach(new Button{Point{0,0},0,0,"level 5",cb_level5});
        level_menu.attach(new Button{Point{0,0},0,0,"level 6",cb_level6});
        level_menu.attach(new Button{Point{0,0},0,0,"level 7",cb_level7});
        level_menu.attach(new Button{Point{0,0},0,0,"level 8",cb_level8});
        attach(level_menu);
        level_menu.hide();
        attach(menu_button);
    }
    
//buttons level 2 - 8 attach 2 - 8 splats ontp thw window when pressed.
void game::level2(){
    level = 2;
    attach(splat1);
	attach(splat2);
	splat1.set_fill_color(Color::red);
	splat2.set_fill_color(Color::blue);
    attach(rect1);
    attach(rect2);
    rect1.set_fill_color(Color::red);
    rect2.set_fill_color(Color::blue);
    redraw();
    hide_menu();
}
void game::level3(){
    level = 3;
    attach(splat1);
	attach(splat2);
	attach(splat3);
	splat1.set_fill_color(Color::red);
	splat2.set_fill_color(Color::blue);
	splat3.set_fill_color(Color::green);
    attach(rect1);
    attach(rect2);
    attach(rect3);
    rect1.set_fill_color(Color::red);
    rect2.set_fill_color(Color::blue);
    rect3.set_fill_color(Color::green);
    redraw();
    hide_menu();
}
void game::level4(){
    level = 4;
    attach(splat1);
	attach(splat2);
	attach(splat3);
	attach(splat4);
	splat1.set_fill_color(Color::red);
	splat2.set_fill_color(Color::blue);
	splat3.set_fill_color(Color::green);
	splat4.set_fill_color(Color::yellow);
    attach(rect1);
    attach(rect2);
    attach(rect3);
    attach(rect4);
    rect1.set_fill_color(Color::red);
    rect2.set_fill_color(Color::blue);
    rect3.set_fill_color(Color::green);
    rect4.set_fill_color(Color::yellow);
    redraw();
    hide_menu();
}
void game::level5(){
    level = 5;
    attach(splat1); attach(splat2); attach(splat3);
	attach(splat4); attach(splat5);
	splat1.set_fill_color(Color::red);
	splat2.set_fill_color(Color::blue);
	splat3.set_fill_color(Color::green);
	splat4.set_fill_color(Color::yellow);
	splat5.set_fill_color(Color::dark_magenta);
    attach(rect1); attach(rect2); attach(rect3);
    attach(rect4); attach(rect5);
    rect1.set_fill_color(Color::red);
    rect2.set_fill_color(Color::blue);
    rect3.set_fill_color(Color::green);
    rect4.set_fill_color(Color::yellow);
    rect5.set_fill_color(Color::dark_magenta);
    redraw();
    hide_menu();
}
void game::level6(){
    level = 6;
    attach(splat1); attach(splat2);
	attach(splat3); attach(splat4);
	attach(splat5); attach(splat6);
	splat1.set_fill_color(Color::red);
	splat2.set_fill_color(Color::blue);
	splat3.set_fill_color(Color::green);
	splat4.set_fill_color(Color::yellow);
	splat5.set_fill_color(Color::dark_magenta);
	splat6.set_fill_color(Color::cyan);
    attach(rect1); attach(rect2);
    attach(rect3); attach(rect4);
    attach(rect5); attach(rect6);
    rect1.set_fill_color(Color::red);
    rect2.set_fill_color(Color::blue);
    rect3.set_fill_color(Color::green);
    rect4.set_fill_color(Color::yellow);
    rect5.set_fill_color(Color::dark_magenta);
    rect6.set_fill_color(Color::cyan);
    redraw();
    hide_menu();
}
void game::level7(){
    level = 7;
    attach(splat1); attach(splat2); attach(splat3); attach(splat4); attach(splat5); attach(splat6); attach(splat7);
	splat1.set_fill_color(Color::red);
	splat2.set_fill_color(Color::blue);
	splat3.set_fill_color(Color::green);
	splat4.set_fill_color(Color::yellow);
	splat5.set_fill_color(Color::dark_magenta);
	splat6.set_fill_color(Color::cyan);
	splat7.set_fill_color(Color::dark_red);
    attach(rect1); attach(rect2); attach(rect3); attach(rect4); attach(rect5); attach(rect6); attach(rect7);
    rect1.set_fill_color(Color::red);
    rect2.set_fill_color(Color::blue);
    rect3.set_fill_color(Color::green);
    rect4.set_fill_color(Color::yellow);
    rect5.set_fill_color(Color::dark_magenta);
    rect6.set_fill_color(Color::cyan);
    rect7.set_fill_color(Color::dark_red);
    redraw();
    hide_menu();
}
void game::level8(){
    level = 8;
    attach(splat1); attach(splat2); attach(splat3); attach(splat4); attach(splat5); attach(splat6); attach(splat7); 
    attach(splat8);
	splat1.set_fill_color(Color::red);
	splat2.set_fill_color(Color::blue);
	splat3.set_fill_color(Color::green);
	splat4.set_fill_color(Color::yellow);
	splat5.set_fill_color(Color::dark_magenta);
	splat6.set_fill_color(Color::cyan);
	splat7.set_fill_color(Color::dark_red);
	splat8.set_fill_color(Color::dark_green);
    attach(rect1); attach(rect2); attach(rect3); attach(rect4); attach(rect5); attach(rect6); attach(rect7); attach(rect8);
    rect1.set_fill_color(Color::red);
    rect2.set_fill_color(Color::blue);
    rect3.set_fill_color(Color::green);
    rect4.set_fill_color(Color::yellow);
    rect5.set_fill_color(Color::dark_magenta);
    rect6.set_fill_color(Color::cyan);
    rect7.set_fill_color(Color::dark_red);
    rect8.set_fill_color(Color::dark_green);
    redraw(); hide_menu();
}

void game::next(){
    for(int i = 0; i < 8; ++i){
        lambda_array[i] = get_lambda(x[i]);
        phi_array[i] = get_phi(y[i]);
    }
    for(int i = 0; i < 8; ++i){ for(int j = 0; j < 8; ++j){ sigma_array[i][j] = 2.0 * PI;}}
    switch(level){
        case 2: { attach(select_splat1); attach(select_splat2); redraw(); break;};
        case 3: { attach(select_splat1); attach(select_splat2); attach(select_splat3); redraw(); break;};
        case 4: { attach(select_splat1); attach(select_splat2); attach(select_splat3); attach(select_splat4); 
        redraw(); break;};
        case 5: { attach(select_splat1); attach(select_splat2); attach(select_splat3); attach(select_splat4);
            attach(select_splat5); redraw(); break;};
        case 6: { attach(select_splat1); attach(select_splat2); attach(select_splat3); attach(select_splat4);
            attach(select_splat5); attach(select_splat6); redraw(); break;};
        case 7: { attach(select_splat1); attach(select_splat2); attach(select_splat3); attach(select_splat4);
            attach(select_splat5); attach(select_splat6); attach(select_splat7); redraw(); break;};
        case 8: { attach(select_splat1); attach(select_splat2); attach(select_splat3); attach(select_splat4);
            attach(select_splat5); attach(select_splat6); attach(select_splat7); attach(select_splat8); redraw(); break;};
        default: {attach(select_splat1); attach(select_splat2);};
    }
    seconds = 30 * level; Fl::add_timeout(1.0,cb_countdown, (void*)this);
}

//countdown callback
void game::cb_countdown(Address pw){
    reference_to<game>(pw).countdown(pw);
}

//uses seconds variable to creat a countdown using the FL::timer.
void game::countdown(Address pw){
    --seconds;
    if (seconds <= 0) quit();
    ostringstream t;
    t << seconds;
    show_time.put(t.str());
	redraw();
    Fl::repeat_timeout(1.0,cb_countdown,pw);
}

//executes file_io code, removes the timer and quits the game.
void game::quit(){  
    file_io();
    Fl::remove_timeout(cb_countdown,0);
    hide();
}


// Calculate minimum arc angle in sigma_array and calculate the score
// Score = min( sigma_array[i][j] ) * level * R, where R = 4000 miles which represents the radius of the earth and sigma_array is in radians
void game::score_calc(){
    int min_i = 0 , min_j = 0;// variables that hold the current location i,j of the min in sigma and when the for loop ends, they hold the absolute min
    double min_sigma = 2.0 * PI;   // varialbe that holds the current min of sigma and when the for loop ends, it holds the absolut min
    for (int i = 0; i < level; ++i) {
        for (int j = 0; j < level; ++j) {
            if ( sigma_array[i][j] < min_sigma) {
                min_i = i;
                min_j = j;
                min_sigma = sigma_array[i][j];
            }
        }
    }
    player_score = round(4000.0 * (double) level * min_sigma); splat_hint = min_i + 1;
    ostringstream s; //reads score into out box
    s << player_score;
    total_score.put(s.str());
    int remaining_moves = 50 - step_counter;
    ostringstream m;
    m << remaining_moves;
    moves_left.put(m.str());
    if (step_counter >= 50){
		file_io(); hide();
    }
}

//shows the best splat to move using the min_i index at where the smallest angle is. 
void game::hint(){
    ostringstream h;
    h << splat_hint;
    show_hint.put(h.str());
    redraw();
}

//sorts by score. 
bool sortByScore(const new_scores &lhs, const new_scores &rhs) { return lhs.final_score > rhs.final_score; }

//reads the input string from task 3 into local string variable.
string game::read_initials(){
    ifstream read_initials( "initials.txt", ios::in ); //opens the text file for reading 
    string input_initials;
    if( !read_initials ) cerr << "Cant open" << endl; //error check.
	read_initials >> input_initials;
	read_initials.close();
    return input_initials;
}

//executes an algorithm that updates the scores list.
void game::file_io(){
    string initials = read_initials();
    vector<new_scores> data(5);
	int final_score; string player_initials;
	ifstream scores_file( "scores.txt", ios::in ); //opens the text file for reading 
    if( !scores_file ) cerr << "Cant open" << endl; //error check. 
    while( scores_file >> final_score >> player_initials ){
        data.push_back({final_score,player_initials});
    }
    scores_file.close();
    if(data[4].final_score < player_score){ //only updates if the scores is large enough 
        data[4].final_score = player_score;
	    data[4].player_initials = initials;
    }
    sort(data.begin(),data.end(),sortByScore);  //sort vector by scores in descending order (C++11) feature.
	ofstream write {"scores.txt"};                         
	if(!write) error("can't open input file ","scores.txt");
    for(new_scores NS:data) write << NS.final_score << " " << NS.player_initials << endl; write.close();
}

//buttons in charge of direction call get_latitude_move and get_longitude_move for direction.
void game::north(){
    step_counter++;
    switch(splat_to_move){
        case 1: { get_latitude_move(1,0); splat1.move(x_move[0],y_move[0]); break;};
        case 2: { get_latitude_move(1,1); splat2.move(x_move[1],y_move[1]); break;};
        case 3: { get_latitude_move(1,2); splat3.move(x_move[2],y_move[2]); break;};
        case 4: { get_latitude_move(1,3); splat4.move(x_move[3],y_move[3]); break;};
        case 5: { get_latitude_move(1,4); splat5.move(x_move[4],y_move[4]); break;};
        case 6: { get_latitude_move(1,5); splat6.move(x_move[5],y_move[5]); break;};
        case 7: { get_latitude_move(1,6); splat7.move(x_move[6],y_move[6]); break;};
        case 8: { get_latitude_move(1,7); splat8.move(x_move[7],y_move[7]); break;};
        default: {splat1.move(0,0);};
    }
    redraw();
    for (m = 0; m < level; ++m ) min_great_arc();
    score_calc();
}

//buttons in charge of direction call get_latitude_move and get_longitude_move for direction.
void game::south(){
    step_counter++;
    switch(splat_to_move){
        case 1: { get_latitude_move(-1,0); splat1.move(x_move[0],y_move[0]); break;};
        case 2: { get_latitude_move(-1,1); splat2.move(x_move[1],y_move[1]); break;};
        case 3: { get_latitude_move(-1,2); splat3.move(x_move[2],y_move[2]); break;};
        case 4: { get_latitude_move(-1,3); splat4.move(x_move[3],y_move[3]); break;};
        case 5: { get_latitude_move(-1,4); splat5.move(x_move[4],y_move[4]); break;};
        case 6: { get_latitude_move(-1,5); splat6.move(x_move[5],y_move[5]); break;};
        case 7: { get_latitude_move(-1,6); splat7.move(x_move[6],y_move[6]); break;};
        case 8: { get_latitude_move(-1,7); splat8.move(x_move[7],y_move[7]); break;};
        default: {splat1.move(0,0);};
    }
    redraw();
    for (m = 0; m < level; ++m ) min_great_arc();
    score_calc();
}

//buttons in charge of direction call get_longitude_move for direction.
void game::east(){
    step_counter++;
    switch(splat_to_move){
        case 1: { get_longitude_move(1,0); splat1.move(x_move[0],0); break;};
        case 2: { get_longitude_move(1,1); splat2.move(x_move[1],0); break;};
        case 3: { get_longitude_move(1,2); splat3.move(x_move[2],0); break;};
        case 4: { get_longitude_move(1,3); splat4.move(x_move[3],0); break;};
        case 5: { get_longitude_move(1,4); splat5.move(x_move[4],0); break;};
        case 6: { get_longitude_move(1,5); splat6.move(x_move[5],0); break;};
        case 7: { get_longitude_move(1,6); splat7.move(x_move[6],0); break;};
        case 8: { get_longitude_move(1,7); splat8.move(x_move[7],0); break;};
        default: {splat1.move(0,0);};
    }
    redraw();
    for (m = 0; m < level; ++m ) min_great_arc();
    score_calc();
}

//buttons in charge of direction call get_longitude_move for direction.
void game::west(){
    step_counter++;
    switch(splat_to_move){
        case 1: { get_longitude_move(-1,0); splat1.move(x_move[0],0); break;};
        case 2: { get_longitude_move(-1,1); splat2.move(x_move[1],0); break;};
        case 3: { get_longitude_move(-1,2); splat3.move(x_move[2],0); break;};
        case 4: { get_longitude_move(-1,3); splat4.move(x_move[3],0); break;};
        case 5: { get_longitude_move(-1,4); splat5.move(x_move[4],0); break;};
        case 6: { get_longitude_move(-1,5); splat6.move(x_move[5],0); break;};
        case 7: { get_longitude_move(-1,6); splat7.move(x_move[6],0); break;};
        case 8: { get_longitude_move(-1,7); splat8.move(x_move[7],0); break;};
        default: {splat1.move(0,0);};
    }
    redraw();
    for (m = 0; m < level; ++m ) min_great_arc();
    score_calc();
}



//splat selectors 
void game::splat_1(){
    splat_to_move = 1;
    m = 0;
    redraw();
    
}

void game::splat_2(){
    splat_to_move = 2;
    m = 1;
    redraw();
    
}

void game::splat_3(){
    splat_to_move = 3;
    m = 2;
    redraw();
    
}

void game::splat_4(){
    splat_to_move = 4;
    m = 3;
    redraw();
    
}

void game::splat_5(){
    splat_to_move = 5;
    m = 4;
    redraw();
    
}

void game::splat_6(){
    splat_to_move = 6;
    m = 5;
    redraw();
    
}

void game::splat_7(){
    splat_to_move = 7;
    m = 6;
    redraw();
   
}

void game::splat_8(){
    splat_to_move = 8;
    m = 7;
    redraw();
    
}





