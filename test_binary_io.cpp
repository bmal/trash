#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

struct Pirate
{
   const char* name;
   unsigned long booty;
   unsigned int beard_long;
};

int main()
{
   Pirate tmp1, tmp2;
   Pirate blackbeard = {"Czarnobrody", 1002, 120};

   FILE* out = fopen("test1_bin", "w");
   if(!out)
      throw runtime_error("fopen");

   if(!fwrite(&blackbeard, sizeof(struct Pirate), 1, out))
      throw runtime_error("fwrite");

   if(fclose(out))
      throw runtime_error("fclose");

   FILE* in = fopen("test1_bin", "r");
   if(!in)
      throw runtime_error("forpen");

   if(!fread(&tmp1, sizeof(struct Pirate), 1, in))
      throw runtime_error("fread");

   if(fclose(in))
      throw runtime_error("fclose");

   cout << "Imie: " << tmp1.name << "\nwartosc lupu: " << tmp1.booty << "\ndlugosc brody: " << tmp1.beard_long;

   

   cout << "\n\n";

   fstream file("test_bin", ios::in | ios::out | ios::binary);
   if(!file)
      throw runtime_error("Blad otwierania");

   if(!file.write(reinterpret_cast<char*>(&blackbeard), sizeof(struct Pirate)))
      throw runtime_error("Blad pisania");

   file.seekg(0, ios::beg);
   if(!file.read(reinterpret_cast<char*>(&tmp2), sizeof(struct Pirate)))
      throw runtime_error("Blad czytania");

   cout << "Imie: " << tmp2.name << "\nwartosc lupu: " << tmp2.booty << "\ndlugosc brody: " << tmp2.beard_long;
}
