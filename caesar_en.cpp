#include <iostream>
using namespace std;

string encryptCaesar(string text, int k) {
  string result = "";
  
  for (int i = 0; i < text.length(); i++) {
    if (isupper(text[i])) {
      result += char(int(text[i] + k - 65) % 26 + 65);
    }
    else if (islower(text[i])) {
      result += char(int(text[i] + k - 97) % 26 + 97);  
    }
    else {
      result += text[i];
    }
  }
  
  return result;
}

int main() {
  string originalText;
  int k;
  
  cout << "Enter text to encrypt: ";
  getline(cin, originalText);
  
  cout << "Enter shift value (1-25): ";
  cin >> k;
  
  string encryptedText = encryptCaesar(originalText, k);
  
  cout << "Encrypted text: " << encryptedText << endl;
  
  return 0;
}
