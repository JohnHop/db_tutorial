#if !defined(ROW)
#define ROW

#include <string>
#include <iostream>

struct Row {
  int id{0};
  std::string username{};
  std::string email{};
};

inline std::ostream& operator<<(std::ostream& out, const Row& r) {
  return out << r.id << " " << r.username << " " << r.email << "\n";
}

#endif // ROW
