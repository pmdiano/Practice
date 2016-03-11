#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

/**
 * JSON pretty print. Assuems the input is a valid JSON string.
 * @param  str [Input JSON string]
 * @return     [Output beautified version]
 */
string JSON_pretty_print(string input) {
  string output;
  int indent = 0;
  bool new_line = false;
  const int tab_size = 2;
  const char *pc = input.c_str() - 1;

  while (*++pc) {
    if (*pc == ' ' || *pc == '\t' || *pc == '\n') {
      continue;
    }

    if (new_line) {
      output += '\n';
      output += string(indent, ' ');
    }

    if (*pc == '{' || *pc == '[') {
      output += *pc;
      new_line = true;
      indent += tab_size;
      continue;
    }

    if (*pc == ',') {
      output += *pc;
      new_line = true;
      continue;
    }

    new_line = false;

    if (*pc == '}' || *pc == ']') {
      output += '\n';
      indent -= tab_size;
      output += string(indent, ' ');
      output += *pc;
      continue;
    }

    if (*pc == '"') {
      output += '"';
      while (*++pc != '"') {
        output += *pc;
      }
      output += '"';
      continue;
    }

    if (*pc == ':') {
      output += ": ";
      continue;
    }

    output += *pc;
  }

  return output;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    string input =
      "{  \"firstName\": \"John\",\n\n"
      "\"lastName\": \"Smith\",  \"age\": 25,   "
      "\"address\": {    \"streetAddress\": "
      "\"21 2nd Street\",    \"city\": \"New York\",    "
      "\"state\": \"NY\",    \"postalCode\": \"10021\"  },  "
      "\"phoneNumber\": [    {      \"type\": \"home\",      "
      "\"number\": \"212 555-1234\"    },    {      "
      "\"type\": \"fax\",      \"number\": \"646 555-4567\""
      "}  ],  \"gender\": {    \"type\": \"male\"  }, "
      "\"healthy\": true,  \"wife\": null}";
    cout << JSON_pretty_print(input) << endl;
  } else {
    for (int i = 1; i < argc; ++i) {
      ifstream t(argv[i]);
      stringstream buffer;
      buffer << t.rdbuf();
      cout << JSON_pretty_print(buffer.str()) << endl;
    }
  }
  return 0;
}
