#if !defined(TABLE)
#define TABLE

#include "statement.h"
#include "row.h"
#include "pager.h"

#define TABLE_SIZE 1024 //Per ora la tabella può contenere 1024 Row...

/**
 * Permette di visualizzare la memoria come una semplice tabella numerata di Row.
 * Pertanto, supporta banalmente le funzioni di inserimento / lettura di una riga.
 * L'inserimento attualmente aggiunge semplicemente una Row alla fine della tabella.
 * Per la lettura è necessario specificare la posizione all'interno della tabella della riga da leggere
*/
class Table {
  size_t length;  //Numero di righe nella tabella
  Row* rows[TABLE_SIZE];
  Pager pager;

public:
  Table(const char*);
  ~Table();

  void insert(const Row& src);
  Row& read(const size_t pos);  //* con l'utilizzo di Cursor potrebbe essere non più necessaria

  size_t get_length() const { return length; }; //Numero di righe presenti nella tabella

  /**
   * Definizione di una sorta di iteratore per Table (come da Parte 6)
  */
  class Cursor {
    Table& table;
    size_t position; //posizione del cursore
    bool end_of_table;  //true se punta alla posizione libera in tabella

  public:
    Cursor(Table& t, size_t p): table{t}, position{p} {
      end_of_table = ( (p == t.length) ? true : false );
    }
    Row& operator*() { return table.read(position); };  //restituisce una Row alla posizione attuale del cursore
    Cursor& operator++() { position += 1; return *this; };
    Cursor& operator--() { position -= 1; return *this; };
    bool operator==(const Cursor& c) const { return (this->position == c.position) ? true : false; };
    bool operator!=(const Cursor& c) const { return !this->operator==(c); };
    //TODO: rispetto alla Parte 6, manca una funzione che restituisce l'area di memoria alla posizione attuale del cursore
  };  //Fine class Cursor

  Cursor begin() { return Cursor{*this, 0}; };  //restituisce un cursore all'inizio di Table
  Cursor end() { return Cursor{*this, length}; }; //cursore alla prossima posizione libera
};

#endif // TABLE
