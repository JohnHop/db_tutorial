#include "helper.h"

#include <iostream>
#include <regex>

void execute_metacommand(const std::string& input) {
  if(input == ".exit") {
    std::exit(EXIT_SUCCESS);
  }
  
  throw MetacommandException{MetacommandException::MetacommandError::META_COMMAND_UNRECOGNIZED_COMMAND};
}

bool execute_statement(Statement& statement, Table& table) {
  switch(statement.get_type()) {
    case(Statement::StatementType::INSERT): {
      return execute_insert(statement, table);
    }
    case(Statement::StatementType::SELECT): {
      return execute_select(statement, table);
    }
    default:
      return false; //FIXME Statement non riconosciuto (UNRECOGNIZED_STATEMENT)
  }
}

bool execute_insert(Statement& statement, Table& table) {
  // TODO esegue la serializzazione in Table
  table.insert(statement.get_row());
  return true;
}

bool execute_select(Statement& statement, Table& table) {
  //TODO esegue la deserializzazione da Table

  for(int i = 0; i < table.get_length(); ++i) {
    std::cout << table.get_page(i);
  }
  return true;
}