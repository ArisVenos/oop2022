#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

using namespace std;


/*

void Key(){
    while (true) {
    // Check if a button has been pressed on the keyboard
    if (kbhit()) {
      // If a button was pressed, get the character that was pressed
      char ch = getch();

      // Update the character's position based on the button that was pressed
      switch (ch) {
        case 'w':
          // Move the character up by 1 unit if the 'w' key was pressed
          Avatar.UpdatePosition(0, -1);
          break;
        case 'a':
          // Move the character left by 1 unit if the 'a' key was pressed
          Avatar.UpdatePosition(-1, 0);
          break;
        case 's':
          // Move the character down by 1 unit if the 's' key was pressed
          Avatar.UpdatePosition(0, 1);
          break;
        case 'd':
          // Move the character right by 1 unit if the 'd' key was pressed
          Avatar.UpdatePosition(1, 0);
          break;
        case 'q':
          // Quit the game if the 'q' key was pressed
          return 0;
      }
    }
  }
}
*/

int main(){
    int X, Y;
    cout <<  "Enter dimensions" <<endl;
    cin >> X >> Y;
    cout << X << " " << Y <<endl;

    srand(time(0));


}
