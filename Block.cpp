#include "block.h"

    block::block (string PREV_BLOCK_HASH, string MERKEL_HASH, string TIMESTAMP, long long int NONCE, double VERSION, int DT, vector<transaction> TRANSACTIONS){
        prev_block_hash=PREV_BLOCK_HASH;
        merkel_hash=MERKEL_HASH;
        timestamp=TIMESTAMP;
        nonce=NONCE;
        version=VERSION;
        dt=DT;
        transactions=TRANSACTIONS;
        block_hash=hash(PREV_BLOCK_HASH+"\n"+MERKEL_HASH+"\n"+TIMESTAMP+"\n"+std::to_string(NONCE)+"\n"+std::to_string(VERSION)+"\n"+std::to_string(DT));
    }

    //get
    string block::getBLOCK_HASH () {return block_hash;}
    string block::getPREV_BLOCK_HASH () {return prev_block_hash;}
    string block::getMERKEL_HASH () {return merkel_hash;}
    string block::getTIMESTAMP () {return timestamp;}
    long long int block::getNONCE () {return nonce;}
    double block::getVERSION () {return version;}
    int block::getDT () {return dt;}

    transaction block::getTransaction(int transaction_number){
        return transactions.at(transaction_number+1);
    };


    //cout
    ostream &operator<<(ostream &out, block &BLOCK){
        out <<left<<setw(25)<<"Block hash "<<BLOCK.getBLOCK_HASH()<<endl<<
        left<<setw(25)<<"Previous block hash "<<BLOCK.getPREV_BLOCK_HASH()<<endl<<
        left<<setw(25)<<"Merkel root hash "<<BLOCK.getMERKEL_HASH()<<endl<<
        left<<setw(25)<<"Timestamp "<<BLOCK.getTIMESTAMP()<<endl<<
        left<<setw(25)<<"Nonce "<<BLOCK.getNONCE()<<endl<<
        left<<setw(25)<<"Version "<<BLOCK.getVERSION()<<endl<<
        left<<setw(25)<<"Difficulty target "<<BLOCK.getDT()<<endl;
        return out;
    }

    //destruktorius
    block::~block(){ block_hash=""; prev_block_hash=""; merkel_hash=""; timestamp=""; nonce=0; version=0; dt=0; transactions.clear(); }