# ifndef TRANSACTION_H
# define TRANSACTION_H

#include "header.h"
#include "hashFunction.h"

class transaction {

private:
    string transactionID="";
    string sender="";
    string receiver="";
    double amount=0.0;

public:

    //konstruktorius
    transaction (string SENDER, string RECEIVER, double AMOUNT);

    //functions
    string getSender ();
    string getReceiver ();
    double getAmount ();
    string getID ();


    //cout
    friend ostream &operator<<(ostream &out, transaction &TRANSACTION);

    //destruktorius
    ~transaction();
    
};//

# endif