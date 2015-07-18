/*
 * @file name: parser.cpp
 *
 * @author: Loai L. Felemban.
 * @date: July 06, 2015
 * @description: parser.cpp is to read the command line and parse
 *  the input into the utility command and it's argument.
 */

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "parser.h"
using namespace std;

parser::parser(){}

parser::~parser(){}

/*
 * @parameter: string syntax.
 * @return: non.
 * @behaviour: store the parameter value
 *  after parsing into a vector.
 */
void parser::parsing( string syntax ){

  istringstream iss( syntax);

  copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(tokens));
}

/*
 * @parameter: non.
 * @return: non.
 * @behaviour: To print out the value in each index
 *  in the vector.
 */
void parser::displayToken() {
  for(int i = 0; i < tokens.size() ; i++){
    cout << tokens[i] << endl;
  }
}
