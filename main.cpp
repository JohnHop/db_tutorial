#include <string>
#include <iostream>
#include <cstdlib>

#include "statement.h"
#include "helper.h"
#include "table.h"

int main(int argc, char* argv[])
{
  std::string input;
  Table table;  //astrazione della memoria persistente

  while(true) { //REPL
    std::cout << "db > "; //prompt
    std::getline(std::cin, input);  //legge l'input formattato

    if(input.starts_with(".")) {  //se è un metacomando
      execute_metacommand(input);
    }
    else {  //se non è un meta-comando allora è una query (forse...)
      Statement statement{input}; //prepara lo statement

      execute_statement(statement, table);
    }
  }
}