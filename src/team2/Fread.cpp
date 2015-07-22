/* Two functions Fread and Fwrite. Current version is only for testing, two functions will be implemented as subclass of Command with valid arguements and outputs in the future.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class fread:Command{
private:
    string line;
    string fileName;
    
public:
    int fread(string name){
        fileName = name;
        ifstream myfile (fileName);
        
        //add a call function to check the permission, if no rw, return 0
        
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                cout << line << '\n'; //replace cout with function in UI
            }
            myfile.close();
        }
        
        else cout << "Unable to open file";
        
        return 0;
    }
    
}

