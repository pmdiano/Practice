#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

string JSON_pretty_print(string str) {
  string output = "{\n";
  int tab_size = 2;
  int indent = tab_size;
  const char *pc = str.c_str() + 1;

  while (*pc) {
    // remove whitespace
    while (*pc == ' ' || *pc == '\n' || *pc == '\t') {
      ++pc;
    }

    if (*pc == '"') { // string
      pc++;
      if (output[output.length()-1] == '\n') {
        output += string(indent, ' ');
      }
      output += '"';
      while (*pc != '"') {
        output += *pc++;
      }
      pc++;
      output += '"';
    } else if (*pc == ':') { // : between key and value
      pc++;
      output += ": ";
    } else if (*pc ==',' ) { // next record
      pc++;
      output += ",\n";
    } else if (*pc == '-' || *pc >= '0' && *pc <= '9') { // number
      while (*pc == '-' || *pc == '.' || *pc == 'e' || *pc >= '0' && *pc <= '9') {
        output += *pc++;
      }
    } else if (*pc == 't' || *pc == 'f' || *pc == 'n') { // true, false, null
      if (*pc == 't') {
        output += "true";
        pc += 4;
      } else if (*pc == 'f') {
        output += "false";
        pc += 5;
      } else if (*pc == 'n') {
        output += "null";
        pc += 4;
      }
    } else if (*pc == '{' || *pc == '[') { // object or array start
      if (output[output.length()-1] == '\n') {
        output += string(indent, ' ');
      }
      output += *pc++;
      output += '\n';
      indent += tab_size;
    } else if (*pc == '}' || *pc == ']') { // object or array end
      output += '\n';
      indent -= tab_size;
      output += string(indent, ' ');
      output += *pc++;
    }
  }

  return output;
}

int main() {
  string input = "{  \"firstName\": \"John\","
          "\"lastName\": \"Smith\",  \"age\": 25,   "
          "\"address\": {    \"streetAddress\": "
          "\"21 2nd Street\",    \"city\": \"New York\",    "
          "\"state\": \"NY\",    \"postalCode\": \"10021\"  },  "
          "\"phoneNumber\": [    {      \"type\": \"home\",      "
          "\"number\": \"212 555-1234\"    },    {      "
          "\"type\": \"fax\",      \"number\": \"646 555-4567\""
          "}  ],  \"gender\": {    \"type\": \"male\"  }, "
          "\"healthy\": true,  \"wife\": null}";
  cout << JSON_pretty_print(input);
  return 0;
}
