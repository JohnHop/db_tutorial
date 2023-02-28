#include "table.h"

Table::Table(const char* fn)
: length{0}, pager{fn}
{
  //Devo determinare il numero di righe presenti nella tabella in base al contenuto del file
  std::pair len = pager.get_length();
  this->length = ( ( len.first * pager.get_page_size() ) + len.second ) / sizeof(Row);
}

/**
 * Aggiunge una nuova riga alla tabella e ordina al Pager di aggiungere una riga
*/
void Table::insert_row(const Row& row) {
  pager.write( reinterpret_cast<const void*>(&row), ROW_SIZE ); //fa scrivere al pager
  rows[length++] = new Row{row};  //Aggiunge la riga alla tabella
}

/**
 * Legge una riga alla posizione 'pos' della tabella.
 * Se non è presente in rows[pos] allora la carica dal pager
*/
Row& Table::read_row(const size_t pos) {
  if(rows[pos] == nullptr) {
    Row* dest = new Row{};

    size_t byte_pos = pos * ROW_SIZE; //determino a partire da 'pos' la posizione, in termini di byte, della riga da leggere

    pager.read(
      dest,
      ROW_SIZE,
      byte_pos / pager.get_page_size(),
      byte_pos % pager.get_page_size()
    );
    rows[pos] = dest; //salvo il puntatore
  }
  return *rows[pos];
}

/**
 * Dealloca tutte le righe della tabella solo se sono state allocate
*/
Table::~Table() {
  for(size_t i = 0; i < length; ++i) {
    if(rows[i] != nullptr) {
      delete rows[i];
      rows[i] = nullptr;
    }
  }
}