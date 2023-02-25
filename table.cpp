#include "table.h"

Table::Table(const char* fn)
: length{0}, filename{fn} 
{
  std::fstream file{filename, std::ios_base::in | std::ios_base::binary | std::ios_base::ate};
  
  if(file) { //Se il file esiste
    length = file.tellg() / ROW_SIZE; //Ottengo il numero di righe nel file

    // file.seekg(0, std::ios_base::beg);  //Mi posiziono all'inizio del file
    // for(int i = 0; i < length; ++i) {
    //   file.read(reinterpret_cast<char*>(&rows[i]), ROW_SIZE); //leggo le righe
    // }
  }
  //* file chiuso automaticamente all'uscita dell'ambito
}

/**
 * Aggiunta una riga alla tabella nella posizione 'length' (che è la prima posizione libera)
*/
void Table::insert_row(const Row& row) {
  rows[length++] = new Row{row};
}

Row& Table::read_row(const int index) {
  //Se non presente, carico la riga dalla memoria persistente
  if(rows[index] == nullptr) {
    rows[index] = new Row;
    std::fstream file{filename, std::ios_base::in | std::ios_base::binary}; //Apro il file //TODO verifica la corretta pertura
    file.seekg(index*ROW_SIZE, std::ios_base::beg);  //Mi posiziono sulla riga che voglio leggere
    file.read(reinterpret_cast<char*>(rows[index]), ROW_SIZE); //leggo la riga
    //* file chiuso automaticamente all'uscita dell'ambito
  }
  return *rows[index];
}

Table::~Table() {
  //Scrittura delle nuove righe nel file
  std::fstream file{filename, std::ios_base::out | std::ios_base::in | std::ios_base::binary | std::ios_base::ate}; //apro e mi posiziono alla fine del file
  int file_row_length = file.tellp() / ROW_SIZE;  //ottengo il numero di righe di cui è costituito il file

  if(file_row_length < length) {  //se la tabella ha più righe del file
    for(int i = file_row_length; i < length; ++i) { //salvo solo le righe che sono "nuove" rispetto al file
      file.write(reinterpret_cast<char*>(&rows[i]), ROW_SIZE); //scrive la riga
    }
  }
  file.close();

  //Deallocazione della memoria
  for(int i = 0; i < length; ++i) {
    if(rows[i] == nullptr) {
      delete rows[i];
      rows[i] = nullptr;
    }
  }
}