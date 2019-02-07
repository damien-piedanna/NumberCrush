#ifndef TYPE_H
#define TYPE_H
#include <string>
#include <vector>
#include <map>

typedef std::vector <unsigned> CVLine;
typedef std::vector <CVLine> CMat;
typedef std::pair <unsigned, unsigned> CPosition;

struct CMyParam {
    std::map <std::string, char> MapParamChar;
    std::map <std::string, unsigned> MapParamUnsigned;
    std::map <std::string, std::string> MapParamString;
};

struct AuthorizedKey {
    const std::vector <std::string> VParamChar {"KeyUp", "KeyDown", "KeyLeft", "KeyRight"};
    const std::vector <std::string> VParamString {"LineColor", "RowColor", "IndexColor", "MyColor"};
    const std::vector <std::string> VParamUnsigned {"GridSize"};
};

const AuthorizedKey KAuthorizedKey;

const std::map <std::string, std::string> KColor
{
  {"KReset", "0"},
  {"KBlack", "30"},
  {"KRed", "31"},
  {"KGreen", "32"},
  {"KYellow", "33"},
  {"KBlue", "34"},
  {"KMAgenta", "35"},
  {"KCyan", "36"},

};
//const std::string KReset   ("0");
//const std::string KBlack   ("30");
//const std::string KRed     ("31");
//const std::string KGreen   ("32");
//const std::string KYellow ("33");
//const std::string KBlue    ("34");
//const std::string KMAgenta ("35");
//const std::string KCyan    ("36");
#endif // TYPE_H
