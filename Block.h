# ifndef BLOCK_H
# define BLOCK_H

#include "hashFunction.h"
#include "header.h"
#include "Transaction.h"


class block {

private:
    string block_hash="";
    string prev_block_hash="";
    string merkel_hash="";
    string timestamp="";
    long long int nonce;
    double version;
    int dt;
    //string transactions="";
    vector<transaction> transactions;

public:

    //konstruktorius
    block (string PREV_BLOCK_HASH, string MERKEL_HASH, string TIMESTAMP, long long int NONCE, double VERSION, int DT, vector<transaction> TRANSACTIONS);
    //get
    string getBLOCK_HASH ();
    string getPREV_BLOCK_HASH ();
    string getMERKEL_HASH ();
    string getTIMESTAMP ();
    long long int getNONCE ();
    double getVERSION ();
    int getDT ();
    //string getTRANSACTIONS ();
    transaction getTransaction(int transaction_number);


    //cout
    //std::ostream& operator<<(std::ostream& out, block& BLOCK);
    friend ostream &operator<<(ostream &out, block &BLOCK);

    //destruktorius
    ~block();
    
};//

# endif