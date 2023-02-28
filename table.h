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

  void insert_row(const Row& src);
  Row& read_row(const size_t pos);

  size_t get_length() const { return length; }; //Numero di righe presenti nella tabella
};

#endif // TABLE
