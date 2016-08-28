//game.h
/*
4. Ask for a difficulty level from 2 to 8; this is the number of satellites (orwhatever). 
Each satellite is a circle of a different color. 
Display the satellites in random positions on a planar map of the earth; use either Mercator or polar projection. 

5. Allow the player to select a satellite and move it north, south, east, 
or west from its present position by a given step size,
which gradually decreases as the game progresses. The step size starts out at 20 degrees of latitude or longitude, 
then after 10 moves changes to 15 degrees, after another 10 moves to 10 degrees, then 5 degrees, 
then 1 degree of latitude or longitude. You may decide to have four buttons labelled N, S, E, and W, 
or choose some other way to indicate which direction to move the selected satellite. Remember to redraw the screen!

6. After each move, calculate the “minor-arc great-circle distance” in miles from every satellite to its nearest neighbor, 
then take the minimum of those distances and multiply by the number of satellites to get the the player's score, 
and display it next to the player's initials. (Note: To simplify the calculations, even if you chose satellites or electrons, 
place the markers on the surface of the earth and assume a
radius of 4,000 miles.) 
After 50 moves the game is over, so sort the list of 6 scores and write the top 5 out to disk with initials. 
Then the next time the game is played that file will be read in and displayed in step 3 above. 
Ask the player if they want to play another game or quit.

Developed by Austin Gonzalez for Team 12. Timer and features by Ibukun Folarin.
Sources:
http://en.cppreference.com/w/cpp/language/auto
http://www.cplusplus.com/reference/cstdlib/rand/
*/
#include "GUI.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"
#include <ctime>
#include <math.h>
#define PI 3.14159265
using namespace Graph_lib;

struct new_scores{
    //used to read/write scores with player initials to scores.txt 
	int final_score;
	string player_initials;
};


struct game : Graph_lib::Window{
    game(Point xy, int w, int h, const string& title);
    
    
    //declare x and y that define the satellite locations
    
    
     //random number generator for splat locations. 
    int randomx(int n){
		if (!seed_set){
			seed_set = true;
			srand(time(NULL));
		}
        int a = rand() % n; //generates the range. 
        return a;
    }
    int level; // 2-8 number of splats 
    int selected_splat; //this is the selected splat for the great arc function 
    int x1 = randomx(795);
    int y1 = randomx(595);
    int x2 = randomx(795);
    int y2 = randomx(595);
    int x3 = randomx(795);
    int y3 = randomx(595);
    int x4 = randomx(795);
    int y4 = randomx(595);
    int x5 = randomx(795);
    int y5 = randomx(595);
    int x6 = randomx(795);
    int y6 = randomx(595);
    int x7 = randomx(795);
    int y7 = randomx(595);
    int x8 = randomx(795);
    int y8 = randomx(595);
    int x[8] = {x1,x2,x3,x4,x5,x6,x7,x8};
    int y[8] = {y1,y2,y3,y4,y5,y6,y7,y8};
    
    int x_move[8] = {0,0,0,0,0,0,0,0};
    int y_move[8] = {0,0,0,0,0,0,0,0};
    
    int lambda_array[8];
    int phi_array[8];
    
    double sigma_array[8][8]; //contains the great arc angles.
    int m; //index of arrays 
    double player_score;      // contains the instantaneous player score
    int splat_hint;           // contains the splat number that is producing the lowest score
    
    int step_counter = 0; //number of moves made. 
    
    
    
    //converts x in pixels to lambda in degrees longitude.
    //auto deduces return types for functions (C++14) feature.
    auto get_lambda(int x){
        int lambda;
        lambda = ((0.45 * x) - 180.0); //0.45 is 360/800 degrees/pixels
        return lambda; 
    }
    
    //converts y in pixels to phi in degrees latitude.
    auto get_phi(int y){
        int phi;
        int yprime;
        yprime = (-8.0962/600.0) * y + 4.0481;
        phi = 2.0 * atan(exp(yprime)) * (180.0/PI) - 90.0;
        
        return phi;
    }
    void get_longitude_move(int flag, int index){
        int move_lambda[5] = {20,15,10,5,1};
        int k;
        int lambda = lambda_array[index];
        int x_previous = x[index];
        if (step_counter <= 10) k = 0;
        else if (step_counter <= 20) k = 1;
        else if (step_counter <= 30) k = 2;
        else if (step_counter <= 40) k = 3;
        else  k = 4;
        if (flag == 1){ lambda += move_lambda[k];} //east 
        if (flag == -1){ lambda -= move_lambda[k];} //west 
        if (lambda > 180){  lambda -= 360;} //E - W wraparound
        if (lambda <= -180){ lambda += 360;} //W - E wraparound
        lambda_array[index] = lambda;
        x[index] = (800.0 * (lambda + 180.0)) / 360.0;
        x_move[index] = x[index] - x_previous;
    }
    
    void get_latitude_move(int flag, int index){
        int move_phi[5] = {20,15,10,5,1}; int k; int wrap_lat = 0; double log_tan;
        int phi = phi_array[index]; int y_previous = y[index]; int lambda = lambda_array[index]; int x_previous = x[index];
        if (step_counter <= 10) k = 0;  // Defines the index K to step through the move_phi array
        else if (step_counter <= 20) k = 1;
        else if (step_counter <= 30) k = 2;
        else if (step_counter <= 40) k = 3; else  k = 4;
        if (flag == 1){ phi += move_phi[k];} //north
        if (flag == -1){ phi -= move_phi[k];} //south
        if (phi >= 88 && phi <= 92) phi = 88; if (phi >= -92 && phi <= -88) phi = -88;  
        if (abs(phi) > 88) wrap_lat = 1;   // flag indicating we're in a wrap around scenario
        if (phi > 88){    phi = 180 - phi;} //North pole wraparound
        if (phi < -88){ phi = -180 - phi;} //South pole wraparound
        phi_array[index] = phi;
        log_tan = log( tan( (45.0 + ((double)phi/2.0)) * (PI/180.0) ));
        y[index] = (4.0481 - log_tan) * (600.0/8.0962);
        y_move[index] = y[index] - y_previous;
        if (wrap_lat == 1) {  //Phase 2 of the wrap around involving lambda
            if (lambda >= 0) lambda -= 180; else if (lambda < 0) lambda += 180;
            lambda_array[index] = lambda;
            x[index] = (800.0 * (lambda + 180.0)) / 360.0;
            x_move[index] = x[index] - x_previous;
        } else { x_move[index] = 0;  } // initialize x_move to zero for case with no wrap around
}


// Calculate the tangent inverse for sigma_array using complex calculation
// Source: https://en.wikipedia.org/wiki/Great-circle_distance
double atan2_calc(int i) {
    double x, y, arc_calc, delta_lambda, phi_m, phi_i, sin_phi1, sin_phi2, cos_phi1, cos_phi2, sin_delta_lambda, cos_delta_lambda;
    // calculate the elements of the atan2 function
    delta_lambda = fabs((double)(lambda_array[i] - lambda_array[m])) * ( PI / 180.0 );
    phi_m = phi_array[m] * ( PI / 180.0 );
    phi_i = phi_array[i] * ( PI / 180.0 );
    sin_phi1 = sin(phi_m);
    sin_phi2 = sin(phi_i);
    cos_phi1 = cos(phi_m);
    cos_phi2 = cos(phi_i);
    sin_delta_lambda = sin(delta_lambda);
    cos_delta_lambda = cos(delta_lambda);
    y = sqrt(pow((cos_phi2 * sin_delta_lambda), 2.0) + pow((cos_phi1 * sin_phi2 - sin_phi1 * cos_phi2 * cos_delta_lambda), 2.0));
    x = sin_phi1 * sin_phi2 + cos_phi1 * cos_phi2 * cos_delta_lambda;
    // find the angle between (phi,lambda) for index m and (phi,lambda) for index i
    arc_calc = atan2(y,x);
    return arc_calc;
}




    // Populates sigma_array with the angles between all the splat locations
void min_great_arc(){
    for (int i = 0; i < level; ++i)
        if ( i != m) {
            sigma_array[m][i] = atan2_calc(i);      // populate the row of sigma_array for the selected splat 
            sigma_array[i][m] = sigma_array[m][i]; //populate the opposite member of sigma array.  
            
        }
}

void score_calc();

// Debug code:  Prints sigma_array in a nice, compact matrix form
void print_sigma_array(){
    for (int i = 0; i < 8; ++i){
        cout << "sigma_array = ";
        for (int j = 0; j < 8; ++j){
            cout << sigma_array[i][j] << "  ";
        }
        cout << "\n";
    }
}

string read_initials();
void file_io();


    
    
   
    
    private:
    //objects
    Image world_map;
    Out_box total_score;
    Out_box moves_left;
    Out_box show_hint;
    Out_box show_time;
	Circle splat1;
    Circle splat2;
    Circle splat3;
    Circle splat4;
    Circle splat5;
    Circle splat6;
    Circle splat7;
    Circle splat8;
    Rectangle rect1;
    Rectangle rect2;
    Rectangle rect3;
    Rectangle rect4;
    Rectangle rect5;
    Rectangle rect6;
    Rectangle rect7;
    Rectangle rect8;
    
    //integers 
	int splat_to_move; //used for selecting splat objects
    int seconds;
    //booleans
	bool seed_set; //used for seeding rand function 
    //next and quit buttons 
    Button next_button;
    Button quit_button;
    
    static void cb_next(Address,Address pw){
        reference_to<game>(pw).next();
    }
    
    static void cb_quit(Address,Address pw){
        reference_to<game>(pw).quit();
    }
    
    void next();
    void quit();
    
   static void cb_countdown(Address pw);
   void countdown(Address pw);
    
    
    //Hint button 
    Button hint_button;
    
    static void cb_hint(Address,Address pw){
        reference_to<game>(pw).hint();
    }
    
    void hint();
    
    //menu of buttons 2 - 8
    Menu level_menu;
    Button menu_button;
    
    void hide_menu(){
        level_menu.hide();
        menu_button.show();
    }
    
    void menu_pressed(){
        menu_button.hide();
        level_menu.show();
    }
    //callbacks for menu buttons. 
    static void cb_menu(Address, Address pw){
        reference_to<game>(pw).menu_pressed();
    }
    static void cb_level2(Address, Address pw){
        reference_to<game>(pw).level2();
    }
    
    static void cb_level3(Address, Address pw){
        reference_to<game>(pw).level3();
    }
    
    static void cb_level4(Address, Address pw){
        reference_to<game>(pw).level4();
    }
    
    static void cb_level5(Address, Address pw){
        reference_to<game>(pw).level5();
    }
    
    static void cb_level6(Address, Address pw){
        reference_to<game>(pw).level6();
    }
    
    static void cb_level7(Address, Address pw){
        reference_to<game>(pw).level7();
    }
    
    static void cb_level8(Address, Address pw){
        reference_to<game>(pw).level8();
    }
    
    //actions by callbacks 
    void level2();
    void level3();
    void level4();
    void level5();
    void level6();
    void level7();
    void level8();
    
    
   
    
    //buttons controlling satellite movement.
    
    Button North;
    Button South;
    Button East;
    Button West;
    
    static void cb_north(Address, Address pw){
        reference_to<game>(pw).north();
    }
    
    static void cb_south(Address, Address pw){
        reference_to<game>(pw).south();
    }
    
    static void cb_east(Address, Address pw){
        reference_to<game>(pw).east();
    }
    
    static void cb_west(Address, Address pw){
        reference_to<game>(pw).west();
    }
    
    void north();
    void south();
    void east();
    void west();
    
    //creates list of select buttons 
    
    Button select_splat1;
    Button select_splat2;
    Button select_splat3;
    Button select_splat4;
    Button select_splat5;
    Button select_splat6;
    Button select_splat7;
    Button select_splat8;
    
    static void cb_splat1(Address, Address pw){
        reference_to<game>(pw).splat_1();
    }
    
    static void cb_splat2(Address, Address pw){
        reference_to<game>(pw).splat_2();
    }
    
    static void cb_splat3(Address, Address pw){
        reference_to<game>(pw).splat_3();
    }
    
    static void cb_splat4(Address, Address pw){
        reference_to<game>(pw).splat_4();
    }
    
    static void cb_splat5(Address, Address pw){
        reference_to<game>(pw).splat_5();
    }
    
    static void cb_splat6(Address, Address pw){
        reference_to<game>(pw).splat_6();
    }
    
    static void cb_splat7(Address, Address pw){
        reference_to<game>(pw).splat_7();
    }
    
    static void cb_splat8(Address, Address pw){
        reference_to<game>(pw).splat_8();
    }
    
    void splat_1();
    void splat_2();
    void splat_3();
    void splat_4();
    void splat_5();
    void splat_6();
    void splat_7();
    void splat_8();
};





