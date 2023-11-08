#include "block.h"

    //default constructor
    block::block(){};

    //constructor with transactions
    block::block (string PREV_BLOCK_HASH, string MERKEL_HASH, string TIMESTAMP, string MINER, long long int NONCE, double VERSION, int DT, int BLOCK_NUMBER, vector<transaction> TRANSACTIONS){
        prev_block_hash=PREV_BLOCK_HASH;
        merkel_hash=MERKEL_HASH;
        nonce=NONCE;
        version=VERSION;
        dt=DT;
        transactions=TRANSACTIONS;
        timestamp=TIMESTAMP;
        miner = MINER;
        block_number=BLOCK_NUMBER;

        block_hash=hash(PREV_BLOCK_HASH+"\n"+MERKEL_HASH+"\n"+TIMESTAMP+"\n"+std::to_string(NONCE)+"\n"+std::to_string(VERSION)+"\n"+std::to_string(DT));
    }

    //constructor without transactions (for genesis block)
    block::block (string PREV_BLOCK_HASH, string MERKEL_HASH, string TIMESTAMP, string MINER, long long int NONCE, double VERSION, int DT, int BLOCK_NUMBER){
        prev_block_hash=PREV_BLOCK_HASH;
        merkel_hash=MERKEL_HASH;
        nonce=NONCE;
        version=VERSION;
        dt=DT;
        timestamp=TIMESTAMP;
        miner = MINER;
        block_number=BLOCK_NUMBER;

        block_hash=hash(PREV_BLOCK_HASH+"\n"+MERKEL_HASH+"\n"+TIMESTAMP+"\n"+std::to_string(NONCE)+"\n"+std::to_string(VERSION)+"\n"+std::to_string(DT));
    }

    //get
    string block::getBLOCK_HASH () {return block_hash;}
    string block::getPREV_BLOCK_HASH () {return prev_block_hash;}
    string block::getMERKEL_HASH () {return merkel_hash;}
    string block::getTIMESTAMP () {return timestamp;}
    string block::getMINER () {return miner;}
    long long int block::getNONCE () {return nonce;}
    double block::getVERSION () {return version;}
    int block::getDT () {return dt;}
    int block::getBLOCK_NUMBER () {return block_number;};

    transaction block::getTransaction(int transaction_number){
        return transactions.at(transaction_number+1);
    };
    vector<transaction> block::getTransactionVector() {return transactions;}


    //cout
    ostream &operator<<(ostream &out, block &BLOCK){
        out <<"\n"<<left<<setw(25)<<"Block hash "<<BLOCK.getBLOCK_HASH()<<endl<<
        left<<setw(25)<<"Previous block hash "<<BLOCK.getPREV_BLOCK_HASH()<<endl<<
        left<<setw(25)<<"Merkel root hash "<<BLOCK.getMERKEL_HASH()<<endl<<
        left<<setw(25)<<"Block number "<<BLOCK.getBLOCK_NUMBER()<<endl<<
        left<<setw(25)<<"Timestamp "<<BLOCK.getTIMESTAMP()<<endl<<
        left<<setw(25)<<"Nonce "<<BLOCK.getNONCE()<<endl<<
        left<<setw(25)<<"Miner "<<BLOCK.getMINER()<<endl<<
        left<<setw(25)<<"Difficulty target "<<BLOCK.getDT()<<endl<<
        left<<setw(25)<<"Version "<<BLOCK.getVERSION()<<"\n\n";
        return out;
    }

    //destruktorius
    block::~block(){ block_hash=""; prev_block_hash=""; merkel_hash=""; timestamp=""; nonce=0; version=0; dt=0; transactions.clear(); }