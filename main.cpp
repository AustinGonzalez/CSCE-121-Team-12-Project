//main method 
#include "splash_screen.h"

int main()
try
{
    splash_screen win {Point{100,100},1125,750,"What a lovely day"};
    return gui_main();
}
//error handling 
catch(exception& e)
{
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Some expection\n";
    return 2;
}












