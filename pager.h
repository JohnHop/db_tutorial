#if !defined(PAGER)
#define PAGER

#include <cstddef>  //per std::size_t
#include <utility>  //per std::pair

/**
 * Espone come interfaccia un modello di memoria semplice:
 * - la memoria è una sequenza di byte a partire dalla locazione zero
 * - sono disponibili operazioni di read / write di basso di libello simili a quella della libreria standard
*/

#define PAGER_SIZE 100  //Il numero massimo di pagine che può avere il file
#define PAGE_SIZE 4096  //Dimensione di una pagina

class Pager {
  const size_t page_size; //Dimensione di una pagina
  size_t length;  //Numero di pagine presenti
  size_t partial_page_length;  //Riempimento dell'ultima pagina espressa in byte
  char* pages[PAGER_SIZE];  //Vettore di puntatori alle singole pagine
  
  const char* filename; //file dove verranno salvate le pagine
public:
  Pager(const char*, const size_t ps = 4096);
  ~Pager();

  std::pair<size_t, size_t> get_length() const { return std::pair{length, partial_page_length}; };
  size_t get_page_size() const { return page_size; };

  void write(const void* source, const size_t count);
  void read(void* dest, const size_t count, const size_t pos, const size_t offset);
};

#endif // PAGER
