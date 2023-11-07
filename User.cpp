#include "User.h"

    //konstruktorius
    user::user (string NAME, double BALANCE, string PRIVATEKEY){
        balance=BALANCE;
        name=NAME;
        privateKey=PRIVATEKEY;
        publicKey=hash(name + privateKey);
    }

    //functions
    void user::updateBalance(double amount){balance=balance+amount;}
    string user::getKey () {return publicKey;}
    double user::getBalance () {return balance;}
    string user::getName () {return name;}
    //string user::getPrivateKey () {return privateKey;}


    //cout
    ostream &operator<<(ostream &out, user &USER){
        out <<left<<setw(25)<<"Public key "<<USER.getKey()<<endl<<
        left<<setw(25)<<"Name "<<USER.getName()<<endl<<
        left<<setw(25)<<"Account balance "<<USER.getBalance()<<endl;
        return out;
    }

    //destruktorius
    user::~user(){ name.clear(); privateKey.clear(); publicKey.clear(); balance=0; }
