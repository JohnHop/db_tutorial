#include "statement.h"

#include <sstream>
#include <algorithm>

/**
 * Questo costruttore è praticamente un parser: recepisce l'input, verifica la correttezza e quindi costruisce uno Statement.
 * In caso di input errato, lo Statement non viene costruito perché il costruttore fallisce lanciando una eccezione (come avviene nella filosofia RAII).
*/
Statement::Statement(const std::string& input) {
  std::stringstream input_stream{input};
  std::string token;  //conterrà i singoli elementi della query

  input_stream >> token;  //prelevo INSERT | SELECT
  std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){ return std::tolower(c);}); //converto in minuscolo

  //Classificazione della query
  if(token == "insert") { //per ora devo prelevare id, username ed email e salvarli in una Row
    this->type = Statement::StatementType::INSERT;

    ((input_stream >> this->row.id) >> this->row.username) >> this->row.email;  //prelevo tutti i dati formattati

    //lancio se l'utente: non inserisce come primo dato un intero || non inserisce abbastanza dati || ne inserisce troppi
    if(input_stream.fail() || input_stream.bad() || !input_stream.eof()) {
      throw ParseException{ParseException::PrepareError::SYNTAX_ERROR};
    }

    //lancio se l'id è negativo
    if(this->row.id < 0) {
      throw ParseException{ParseException::PrepareError::NEGATIVE_ID};
    }
  }
  else if(token == "select") {
    this->type = Statement::StatementType::SELECT;
  }
  else {  //la query non è stata riconosciuta
    throw ParseException{ParseException::PrepareError::UNRECOGNIZED_STATEMENT};
  }
}