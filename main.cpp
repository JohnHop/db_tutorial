#include <string>
#include <iostream>
#include <cstdlib>

#include "statement.h"
#include "helper.h"
#include "table.h"

int main(int argc, char* argv[])
{
  // if(argc != 2) { //è necessario specificare il filename del db
  //   std::cerr << "Error: devi specificare il filename del database!\n";
  //   exit(EXIT_FAILURE);
  // }

  Table table{"mydb.db"};  //astrazione della memoria persistente //? lo metto momentaneamente qui e dopo risolvo la questione dell'ambito
  std::string input;
  bool exit_flag{false}; //Ci serve un flag per indicare quando si vuole uscire dal programma o meno

  while(exit_flag == false) { //REPL
    std::cout << "db > "; //prompt
    std::getline(std::cin, input);  //legge l'input formattato

    if(input.starts_with(".")) {  //se è un metacomando
      exit_flag = execute_metacommand(input);
    }
    else {  //se non è un meta-comando allora è una query (forse...)
      Statement statement{input}; //prepara lo statement
      execute_statement(statement, table);
    }
  }

  return EXIT_SUCCESS;
}