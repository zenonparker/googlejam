#include <iostream>
#include <sstream>
#include <cmath>
#include <reader.hpp>
#include <writer.hpp>

using namespace std;
using namespace jam;

struct Language {
  Language(const string& str) : langStr(str) { }

  long numDecimal(const string& num) const {
    long ret = 0;
    DEBUG("tranlating " << num << " to lang using [" << langStr << "]");
    for (int i = 0; i < num.length(); ++i) {
      int pos = langStr.find(num[i]);
      if (pos != string::npos) {
        ret += pow(langStr.length(), num.length() - i - 1) * pos;
      }
    }
    return ret;
  }

  string numFromLang(const string& num, const Language& lSource) const {
    long decNum = lSource.numDecimal(num);
    DEBUG(decNum);
    string ret;
    int x = 1;
    while (decNum > 0) {
      long ind = decNum % langStr.length();
      DEBUG("ind " << ind);
      ret.insert(0, 1, langStr[ind]);
      DEBUG("ret " << ret);
      decNum /= langStr.length();
      ++x;
    }
    return ret;
  }

  string langStr;
};

int main(int argc, char** argv) {

  Writer w(argc, argv);
  Reader r(argc, argv);

  stringstream ss;

  int numCases = 0;
  r.nextLine(ss);
  ss >> numCases;

  for (int i = 0; i < numCases; ++i) {

    r.nextLine(ss);

    DEBUG("Reading " << ss.str());

    string num, source, target;
    ss >> num >> source >> target;

    Language lSource(source);
    Language lTarget(target);

    w.out() << "Case #" << (i + 1) << ": " << lTarget.numFromLang(num, lSource) << '\n';
  }

  return 0;
}

