#if !defined(HELPER)
#define HELPER

#include <string>
#include <stdexcept>

#include "statement.h"
#include "table.h"

/**
 * @returns true se il meta-comando è valido, altrimenti false.
*/
bool execute_metacommand(const std::string&);

void execute_statement(Statement&, Table&); //TODO gestione degli errori nell'esecuzione dello statement
void execute_insert(Statement&, Table&);
void execute_select(Statement&, Table&);

class MetacommandException : public std::exception {
public:
  enum class MetacommandError { META_COMMAND_UNRECOGNIZED_COMMAND };

  MetacommandException(MetacommandError e): type(e) { };
  const char* what() {
    switch(type) {
      case(MetacommandError::META_COMMAND_UNRECOGNIZED_COMMAND):
        msg = "META_COMMAND_UNRECOGNIZED_COMMAND"; break;
    }
    return msg.c_str();
  }

private:
  std::string msg;
  MetacommandError type;
};

#endif // HELPER
