#if !defined(STATEMENT)
#define STATEMENT

#include <string>
#include <stdexcept>

#include "row.h"

class Statement {
public:
  enum class StatementType { INSERT, SELECT };

private:
  StatementType type;
  Row row;  //è la riga dove si inserisce/preleva il record dal database

public:
  Statement(const std::string& input);

  // StatementType set_type(const StatementType& t) { return type = t; }; //TODO da eliminare perché il tipo viene determinato solo nel costruttore
  StatementType get_type() const { return type; };
  Row& get_row() { return row; };
};


class ParseException : public std::exception {  
public:
  enum class PrepareError { STRING_TOO_LONG, SYNTAX_ERROR, UNRECOGNIZED_STATEMENT, NEGATIVE_ID };

  ParseException(PrepareError t): type{t} { };

  const char* what() {
    switch(type) {
      case(PrepareError::STRING_TOO_LONG):
        msg = "STRING_TOO_LONG"; break;
      case(PrepareError::SYNTAX_ERROR):
        msg = "SYNTAX_ERROR"; break;
      case(PrepareError::UNRECOGNIZED_STATEMENT):
        msg = "UNRECOGNIZED_STATEMENT"; break;
      case(PrepareError::NEGATIVE_ID):
        msg = "NEGATIVE_ID"; break;
    }
    return msg.c_str();
  }

private:
  PrepareError type;
  std::string msg;
};

#endif // STATEMENT
