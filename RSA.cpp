// D William Beighley
// Final Project: RSA

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <gmpxx.h>

using namespace std;

bool checkIfPrime(int number)
{
   for (int i = number - 1; i > 1; i--)
   {
      if ((number % i) == 0)
      return false;
   }
   return true; 
}

int exponent (int base, int power)
{
   int result = 1;
   for (int i = 0; i < power; i++)
   {
      result *= base;
   }
      return result; 
}

mpz_class numberFromString(const string &str)
{
   mpz_class c = 0;
   int size = str.length();
   for (int i = 0; i < size ; i++)
   {
   int t = static_cast<int>(str[i]);
      
      mpz_class s = 0;
      mpz_ui_pow_ui(s.get_mpz_t(), 10, 2 * (size - i - 1));
      mpz_mul_ui(s.get_mpz_t(), s.get_mpz_t(), t);
 
      mpz_add(c.get_mpz_t(), c.get_mpz_t(), s.get_mpz_t());
   }
   return c;
}

int main()
{
   //PART 1 - Key Generation 
   int p = 0;
   cout << "Enter a large prime for p: ";
   cin >> p; 
   
   while (checkIfPrime(p) == false || p < 0 )
   {
      cout << "ERROR: p must be a positive prime number\n";
      cout << "Enter a large prime for p: ";
      cin >> p;
   }
   
   int q = 0;
   cout << "Enter a large prime for q: ";
   cin >> q;
 
   while (checkIfPrime(q) == false || q < 0 )
   {
      cout << "ERROR: q must be a positive prime number\n";
      cout << "Enter a large prime for q: ";
      cin >> q;
   } 
   
   int n = p * q;
   cout << "Your n value is: " << n << "\n";
	
   int totientN = n - p - q + 1;
   cout << "Your totient value is: " << totientN << "\n";
   
   int e = 0;
   cout << "Enter a value between 1 and " << totientN << " that is mutually prime with " << totientN << ": ";
   cin >> e;
   
   while (checkIfPrime(e) == false || totientN % e == 0 || (e < 1 || e > totientN))
   {
      cout << "ERROR: Enter a valid value\n";
      cout << "Enter a value between 1 and " << totientN << " that is mutually prime with " << totientN << ": ";
      cin >> e; 
	  
   }
   
   //int d = 1 % totientN / e; 
   int d = 1;
   int i;
   do {
      i = (d*e) % totientN;
      d++;
   } while (i != 1);
   d = d - 1;
   
   cout << "Your e value is: " << e << "\n";
   cout << "Your d value is: " << d << "\n";
   
   cout << "Your public key is: (" << n << "," << e << ")\n";
   cout << "Your private key is: (" << n << "," << d << ")\n";
   
   //PART 2 - Encryption/Decryption
   int z = 0; 
   cout << "Enter 1 for encryption, 2 for decryption, anything else to quit: ";
   cin >> z;
   
   if (z == 1)
   {
      string a;
      ifstream myfile ("plaintext.txt");
      if (myfile.is_open())
      {
         while ( getline (myfile, a) )
         {
            cout << "Encrypting..." << '\n';
         }
      myfile >> a; 
	   
      
      mpz_class m = numberFromString(a);
      int u = m.get_ui();
	  
      //cout << m << "\n"; test to make sure m right value
      //cout << u << "\n"; test to make sure z correct value
	  
	  
      //ciphertext c = m^e mod n 
	  
      mpz_class f;
      mpz_ui_pow_ui(f.get_mpz_t(), u, e);
	  
      f = f % n;
	  
      // cout << f << '\n';  test to make sure f right value
	  
      ofstream myfile1;
      myfile1.open ("ciphertext.txt");

      myfile1 << f << endl;
      myfile1.close();
      myfile.close();
    
      cout << "Done! Saved to ciphertext.txt\n"; 
	   
      }
   
      else 
      {
         cout << "ERROR: Unable to read in message";
      }
      return 0;
    }
   
   else if (z == 2)
   {
      string v;
      ifstream myfile ("ciphertext.txt");
      if (myfile.is_open())
      {
         while ( getline (myfile, v) )
         {
         cout << "Decrypting..." << '\n';
         }
	   
      myfile >> v;  //gets ciphertext value as a string 
	
	   
      //converts the string v into a large (gmp) int 
      mpz_class o = numberFromString(v);
      int j = o.get_ui();
	   
      mpz_ui_pow_ui(o.get_mpz_t(), j, d);
	   
      o = o % n; //o is now the ASCII characters
	   
      //plaintext m = c^d mod n 
      int y = o.get_ui();
	   
      //converts ASCII int to a string
      stringstream ss;
      ss << y;
      string str = ss.str();  
	   
      ofstream myfile1;
      myfile1.open("plaintext.txt");
      myfile1 << str << endl;
	   
      myfile1.close();
      myfile.close();
      cout << "Done! Saved to plaintext.txt\n";
      }
   }
	
   else
   {
      cout << "Goodbye!\n";
   }

}


