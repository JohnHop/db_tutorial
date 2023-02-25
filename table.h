#if !defined(TABLE)
#define TABLE

#include "statement.h"
#include "row.h"
#include "pager.h"

#define TABLE_SIZE 32

/**
 * Permette di visualizzare la memoria persistente come una semplice tabella numerata per righe.
 * Pertanto, supporta banalmente le funzioni di inserimento / lettura di una riga
*/
class Table {
  Row rows[TABLE_SIZE]{};
  int length{0};

  std::string filename;

public:
  Table(const char*);
  ~Table();  //? Va implementato in qualche modo?

  void insert_row(const Row& r);
  Row& read_row(const int i);

  int get_length() const { return length; };
};

#endif // TABLE
