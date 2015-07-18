/*
 * @file name: parser.h
 *
 * @author: Loai L. Felemban
 * @date: July 06, 2015
 */

#ifndef _PARSER_H
#define _PARSER_H

#include <string>
#include <vector>

class parser{
private:
  std::vector<std::string> tokens;

public:
  parser();
  ~parser();

  void parsing( std::string syntax );
  void displayToken();
};


#endif // end _PARSER_H

