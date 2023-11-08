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
    string miner="";
    long long int nonce;
    double version;
    int dt;
    int block_number;
    //string transactions="";
    vector<transaction> transactions;

public:

    //konstruktoriai
    block();
    block (string PREV_BLOCK_HASH, string MERKEL_HASH, string TIMESTAMP, string MINER, long long int NONCE, double VERSION, int DT, int BLOCK_NUMBER, vector<transaction> TRANSACTIONS);
    block (string PREV_BLOCK_HASH, string MERKEL_HASH, string TIMESTAMP, string MINER, long long int NONCE, double VERSION, int DT, int BLOCK_NUMBER);
    //get
    string getBLOCK_HASH ();
    string getPREV_BLOCK_HASH ();
    string getMERKEL_HASH ();
    string getTIMESTAMP ();
    string getMINER ();
    int getBLOCK_NUMBER ();
    long long int getNONCE ();
    double getVERSION ();
    int getDT ();
    //string getTRANSACTIONS ();
    transaction getTransaction(int transaction_number);
    vector<transaction> getTransactionVector();


    //cout
    //std::ostream& operator<<(std::ostream& out, block& BLOCK);
    friend ostream &operator<<(ostream &out, block &BLOCK);

    //destruktorius
    ~block();
    
};//

# endif