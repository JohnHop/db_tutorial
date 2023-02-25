#include "table.h"

Table::Table(const char* fn)
: length{0}, filename{fn} 
{
  std::fstream file{filename, std::ios_base::in | std::ios_base::ate};
  
  if(file) { //Se il file esiste
    length = file.tellg() / ROW_SIZE; //Ottengo il numero di righe nel file

    file.seekg(0, std::ios_base::beg);  //Mi posiziono all'inizio del file
    for(int i = 0; i < length; ++i) {
      file.read(reinterpret_cast<char*>(&rows[i]), ROW_SIZE); //leggo le riga
    }
    file.close();
  }
}

/**
 * Aggiunta una riga alla tabella nella posizione 'length' (la prima posizione libera)
*/
void Table::insert_row(const Row& row) {
  rows[length++] = row;
}

Row& Table::read_row(const int index) {
  return rows[index];
}

Table::~Table() {
  std::fstream file{filename, std::ios_base::out};
  file.seekp(0, std::ios_base::beg);  //Mi posiziono all'inizio del file

  for(int i = 0; i < length; ++i) {
    file.write(reinterpret_cast<char*>(&rows[i]), ROW_SIZE); //scrive la riga
  }
  file.close();
}