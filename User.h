# ifndef USER_H
# define USER_H

#include "header.h"
#include "hashFunction.h"

class user {

private:
    string name="";
    string privateKey="";

    double balance=0.0;
    string publicKey="";

public:

    //konstruktorius
    user (string NAME, double BALANCE, string PRIVATEKEY);

    //functions
    void updateBalance(double amount);
    string getKey ();
    double getBalance ();
    string getName ();
    //string getPrivateKey ();


    //cout
    friend ostream &operator<<(ostream &out, user &USER);

    //comparison (for map)
    //friend bool operator<(const user& one, const user& two);

    //destruktorius
    ~user();
    
};//

# endif