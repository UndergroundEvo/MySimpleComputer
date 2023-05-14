#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

std::map<std::string, int>::iterator it;
std::map<std::string, int> commands = {
  { "READ", 0x10 },  { "WRITE", 0x11 }, { "LOAD", 0x20 },   { "STORE", 0x21 },
  { "ADD", 0x30 },   { "SUB", 0x31 },   { "DIVIDE", 0x32 }, { "MUL", 0x33 },
  { "JUMP", 0x40 },  { "JNEG", 0x41 },  { "JZ", 0x42 },     { "HALT", 0x43 },
  { "NOT", 0x51 },   { "AND", 0x52 },   { "OR", 0x53 },     { "XOR", 0x54 },
  { "JNS", 0x55 },   { "JC", 0x56 },    { "JNC", 0x57 },    { "JP", 0x58 },
  { "JNP", 0x59 },   { "CHL", 0x60 },   { "SHR", 0x61 },    { "RCL", 0x62 },
  { "RCR", 0x63 },   { "NEG", 0x64 },   { "ADDC", 0x65 },   { "SUBC", 0x66 },
  { "LOGLC", 0x67 }, { "LOGRC", 0x68 }, { "RCCL", 0x69 },   { "RCCR", 0x70 },
  { "MOVA", 0x71 },  { "MOVR", 0x72 },  { "MOVCA", 0x73 },  { "MOVCR", 0x74 },
  { "=", 0x7F }
};

struct machineWord
{
  int address = 0;
  int command = 0;
  int operand = 0;
};

void
split (string str, char separator, vector<string> &array)
{
  string buffer;
  for (int i = 0; i < str.size (); i++)
    {
      if (str[i] == ';')
        {
          break;
        }
      if (str[i] != separator)
        {
          buffer += str[i];
        }
      else
        {
          array.push_back (buffer);
          buffer = "";
        }
    }
  if (buffer != "")
    {
      array.push_back (buffer);
    }
}

int
stringToInt (string word)
{
  int num;
  num = stoi (word);
  return num;
}

int
findInCommands (string command)
{
  it = commands.find (command);
  return it->second;
}

int
fromWordToInt (machineWord word)
{
  if (word.command == 0x7F)
    {
      return word.operand + (1 << 14);
    }
  return word.command << 7 | word.operand;
}

machineWord
decodeLine (string line)
{
  machineWord currentWord;
  vector<string> words;
  split (line, ' ', words);

  currentWord.address = stringToInt (words[0]);
  currentWord.command = findInCommands (words[1]);
  currentWord.operand = stringToInt (words[2]);

  return currentWord;
}

int
main (int argc, char *argv[])
{
  cout << "Start translator" << endl;

  if (argc < 2)
    {
      return -1;
    }

  ifstream in (argv[1]); // окрываем файл для чтения
  if (!in.is_open ())
    {
      return -1;
    }

  ofstream out (argv[2], ios::binary);
  if (!out.is_open ())
    {
      return -1;
    }

  vector<machineWord> app;
  string line;

  while (getline (in, line))
    {

      machineWord currentWord = decodeLine (line);
      app.push_back (currentWord);
    }

  machineWord tmp;
  for (int i = 0; i < app.size (); i++)
    {
      for (int j = i + 1; j < app.size (); j++)
        {
          if (app[i].address > app[j].address)
            {
              tmp = app[i];
              app[i] = app[j];
              app[j] = tmp;
            }
        }
    }

  int num = 0;
  int count = 0;
  for (int i = 0; i < 100; i++)
    {
      num = 0;
      if (i == app[count].address)
        {
          num = fromWordToInt (app[count]);
          if (count < app.size () - 1)
            {
              count++;
            }
        }
      out.write ((char *)&num, sizeof (num));
    }

  in.close (); // закрываем файл

  cout << "End Translator" << endl;

  return 0;
}