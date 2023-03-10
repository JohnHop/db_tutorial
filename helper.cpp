#include "helper.h"

#include <iostream>


bool execute_metacommand(const std::string& input) {
  if(input == ".exit") {
    return true;
  }
  
  throw MetacommandException{MetacommandException::MetacommandError::META_COMMAND_UNRECOGNIZED_COMMAND};
}

void execute_statement(Statement& statement, Table& table) {
  switch(statement.get_type()) {
    case(Statement::StatementType::INSERT): {
      execute_insert(statement, table);
      break;
    }
    case(Statement::StatementType::SELECT): {
      execute_select(statement, table);
      break;
    }
  }
}

void execute_insert(Statement& statement, Table& table) {
  table.insert(statement.get_row());
}

void execute_select(Statement& statement, Table& table) {
  for(auto cur = table.begin(); cur != table.end(); ++cur) {
    std::cout << *cur;
  }
}