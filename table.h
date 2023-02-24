#if !defined(TABLE)
#define TABLE

#include "statement.h"
#include "row.h"

#define TABLE_MAX_PAGES 100

class Table {
  int length{0};
  Row pages[TABLE_MAX_PAGES]{};

public:
  int get_length() const { return length; };

  void insert(const Row& r) { pages[length++] = r; };
  Row get_page(const int i) const { return pages[i]; }; //estrae dalla memoria
};

#endif // TABLE
