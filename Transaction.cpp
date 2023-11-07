#include "Transaction.h"

    //konstruktorius
    transaction::transaction (string SENDER, string RECEIVER, double AMOUNT){
        sender=SENDER;
        receiver=RECEIVER;
        amount=AMOUNT;
        transactionID=hash(SENDER+std::to_string(AMOUNT)+RECEIVER);
    }

    //functions
    string transaction::getSender () {return sender;}
    string transaction::getReceiver () {return receiver;}
    double transaction::getAmount () {return amount;}
    string transaction::getID () {return transactionID;}


    //cout
    ostream &operator<<(ostream &out, transaction &TRANSACTION){
        out <<left<<setw(25)<<"Transaction ID "<<TRANSACTION.getID()<<endl<<
        left<<setw(25)<<"Sender "<<TRANSACTION.getSender()<<endl<<
        left<<setw(25)<<"Receiver "<<TRANSACTION.getReceiver()<<endl<<
        left<<setw(25)<<"Amount "<<TRANSACTION.getAmount()<<endl;

        return out;
    }

    //destruktorius
    transaction::~transaction(){ sender=""; receiver=""; amount=0; transactionID=""; }
    
