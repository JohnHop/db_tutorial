#include "pager.h"

#include <fstream>
#include <cstring>
#include <iostream>

Pager::Pager(const char* fn, const size_t ps)
: filename{fn}, pages{nullptr}, page_size{ps}
{
  std::fstream file{filename, std::ios_base::binary | std::ios_base::in | std::ios_base::ate};
  
  if(!file) {
    std::cerr << "Pager: Impossibile aprire il file '" << filename << "'\n";
    exit(EXIT_FAILURE);
  }

  length = file.tellg() / PAGE_SIZE; //Determino il numero di pagine complete scritte nel file
  partial_page_length = file.tellg() % PAGE_SIZE; //se è presente una pagina parziale allora determino la sua lunghezza
};

/**
 * Accoda 'count' byte da 'source' in una pagina.
*/
void Pager::write(const void* source, size_t count) {
  if(PAGE_SIZE - partial_page_length < count) { //se non riesco a scrivere nello spazio rimanente della pagina
    length += 1;  //allora scrivo nella pagina successiva
    partial_page_length = 0;
  }

  if(pages[length] == nullptr) {  //se la pagina non esiste allora la creo
    pages[length] = new char[page_size];

    /**
     * La pagina creata ora in memoria potrebbe avere un corrispettivo parziale nel file.
     * Quindi determino prima se sto scrivendo all'inizio della pagina o meno.
    */
    if(partial_page_length) { //non sto scrivendo all'inizio della pagina. Quindi carico i dati parziali dal file
      std::fstream file{filename, std::ios_base::binary | std::ios_base::in};
      file.read(pages[length], partial_page_length);  //legge tutta la pagina parziale
    }  
  }

  std::memcpy(  //scrive la riga nella pagina
    reinterpret_cast<void*>( &(pages[length][partial_page_length]) ),
    source, 
    count
  );

  partial_page_length += count;

  if(partial_page_length > PAGE_SIZE) { //se ho riempito la pagina passo alla successiva
    length += 1;
    partial_page_length = 0;
  }
}

/**
 * Legge da 'source' un numero di byte pari a 'count' e li salva in 'dest' in base alla posizione determinata da 
 * 'page_pos' e un 'offset'.
*/
void Pager::read(void* dest, const size_t count, const size_t pos, const size_t offset) {
  if(pages[pos] == nullptr) { //Verifico se la pagina è presente in memoria, altrimenti la carico dal file
    pages[pos] = new char[page_size];
    std::fstream file{filename, std::ios_base::binary | std::ios_base::in};
    file.seekg( pos*PAGE_SIZE );  //mi posiziono alla pagina da leggere
    file.read(pages[pos], PAGE_SIZE);
  }

  std::memcpy(  //Lettura dal vettore delle pagine
    dest,
    reinterpret_cast<const void*>( &(pages[pos][offset]) ),
    count
  );
}

/**
 * Salva le pagine nel file se necessario e le dealloca dalla memoria principale
*/
Pager::~Pager() {
  std::fstream file{filename, std::ios_base::binary | std::ios_base::in | std::ios_base::out | std::ios_base::ate};
  
  //TODO Controllo sull'apertura del file

  size_t file_byte_length = file.tellg(); //determino la dimensione del file

  //Se ci sono delle righe da scrivere in memoria
  if(file_byte_length < (length*PAGE_SIZE) + partial_page_length) {
    size_t file_length = file_byte_length / PAGE_SIZE;  //pagine presenti nel file
    size_t file_partial_page_length = file_byte_length % PAGE_SIZE;

    //Inizio il salvataggio delle singole pagine intere
    file.seekp(file_length * PAGE_SIZE);  //mi posiziono all'inizio della pagina da scrivere nel file
    while(file_length < length-1 && length > 0) {
      file.write(pages[file_length++], PAGE_SIZE);  //scrivo la pagina e aggiorno il contatore
    }

    //L'ultima pagina in memoria potrebbe essere parziale
    if(partial_page_length) {
      file.write(pages[file_length], partial_page_length);
    }
  }

  //Deallocazione della memoria
  for(size_t i = 0; i < length; ++i) {
    if(pages[i] != nullptr) {
      delete [] pages[i];
      pages[i] = nullptr;
    }
  }
  if(partial_page_length) {
    delete [] pages[length];
    pages[length] = nullptr;
  }
}