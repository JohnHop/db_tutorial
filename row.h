#if !defined(ROW)
#define ROW

#include <string>
#include <iostream>
#include <cstring>

#define USERNAME_SIZE 14
#define EMAIL_SIZE 14

/**
 * Attualmente Row è una sorta di contenitore perché ha come membri vettori (ovvero puntatori ad aree di dati).
 * Per questo è necessario definire un costruttore, costruttore di copia e operatore di assegnamento
*/
struct Row {
  int id;
  char username[USERNAME_SIZE];
  char email[EMAIL_SIZE];

  Row(): id{}, username{0}, email{0} { }; //Costruttore di default
  Row(const Row& row): id{row.id} {       //Costruttore copia
    std::memcpy(username, row.username, USERNAME_SIZE);
    std::memcpy(email, row.email, EMAIL_SIZE);
  }

  Row& operator=(const Row& row) {  //operatore di assegnamento
    id = row.id;
    std::memcpy(username, row.username, USERNAME_SIZE);
    std::memcpy(email, row.email, EMAIL_SIZE);
    return *this;
  }
};

#define ROW_SIZE sizeof(Row)

inline std::ostream& operator<<(std::ostream& out, const Row& r) {
  return out << r.id << " " << r.username << " " << r.email << "\n";
}

#endif // ROW
