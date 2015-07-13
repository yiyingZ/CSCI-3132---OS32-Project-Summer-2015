/* Two functions Fread and Fwrite. Current version is only for testing, two functions will be implemented as subclass of Command with valid arguements and outputs in the future.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int fread(string name){
    string line;
    string fileName = name;
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

int fwrite(string name, string content){
    string fileName = name;
    fstream file;
    file.open(fileName, ios_base::out | ios_base::in);  // will not create file
    
    //check if the file already exists
    if (file.is_open())
    {
        cout << "File already exists, append to the end";
        
        //add a call function to check the permission, if no rw, return 0
        file.close();
        file.open(fileName,fstream::in | fstream::out | fstream::app);  // will not create file
        file << content<<"\n";
        file.close();
        return 1;
        
    }
    else
    {
        cout<<"file not exists, create a new file";
        file.clear();
        file.open(fileName, ios_base::out);  // will create a new file
        file << content<<"\n";
        file.close();
        return 1;
    }
    
    return 0;
}

//testing
int main(int argc, const char * argv[]) {
    fwrite("kkkka.txt","ccccc");
    cout<<"\n";
    fread("kkkka.txt");

    return 0;
}
