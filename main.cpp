#include "header.h"
#include "Block.h"
#include "User.h"
#include "Transaction.h"
#include "generatorFunctions.h"


//settings
const int USERcount = 100;
const int TRANSACTIONcount = 10000;
const int private_key_length = 30;


vector<block> BLOCKCHAIN;
vector<user> USERS;
vector<transaction> POOL;




//main
int main () {

cout<<"\n";
cout<<"Creating users...\n\n";

    // CREATE USERS
        for (int a=0; a<USERcount; a++){

            user temp {randomName(), randomDouble(), randomString(private_key_length)};
            USERS.push_back(temp);
        }
    //

cout<<USERcount<<" users created.\n\n";       

    // OUTPUT USERS TO FILE
        string usersOUT="";
        ofstream usersFILE ("users.txt");

        int a=1; //counter

        for (auto i:USERS) {

            string temp="";
            stringstream ss;
            ss<<i;
            usersOUT+="USER "+ to_string(a) + ":\n";
            while (getline(ss, temp)){
                usersOUT+="\n"+temp;
                temp="";
            }//while
            usersOUT+="\n\n\n";
            a++;
        }//for

        usersFILE<< usersOUT;
        usersFILE.close();
        usersOUT="";
    //

cout<<"User list can be found in users.txt\n\n";

cout<<"Creating transactions...\n\n";

    //
        std::random_device rand;
        std::mt19937 generate(rand());
        std::uniform_int_distribution<int> rand_user_index(0, USERcount-1);     //rand_user_index(generate)
        std::uniform_real_distribution<double> rand_amount(0., 50000.);         //rand_amount(generate)
    //

    // CREATE TRANSACTIONS
        for (int a=0; a<TRANSACTIONcount; a++){

            int user1=rand_user_index(generate);                                        //SENDER
            int user2=user1;                                                            //RECEIVER
            while (user1==user2) user2=rand_user_index(generate);                       //check if sender =/= receiver

            double amount=rand_amount(generate);                                        //AMOUNT
            while (amount>USERS.at(user1).getBalance()) amount=rand_amount(generate);   //check if sender has enough currency

            transaction temp{USERS.at(user1).getKey(), USERS.at(user2).getKey(), amount};   //create transaction
            POOL.push_back(temp);                                                       //add to pool

        }
    //

cout<<TRANSACTIONcount<<" transactions created.\n\n";

    // OUTPUT TRANSACTIONS TO FILE
        string transactionsOUT="";                              //output string
        ofstream transactionsFILE ("transactions.txt");         //output file

        a=1;    //reset counter

        for (auto i:POOL){                                      //add transactions to output string

            string temp="";
            stringstream ss;
            ss<<i;
            transactionsOUT+="TRANSACTION "+ to_string(a) + "\n";
            while (getline(ss, temp)){
                transactionsOUT+="\n"+temp;
                temp="";
            }//while
            transactionsOUT+="\n\n\n";
            a++;
        }//for

        transactionsFILE<<transactionsOUT;                      //output to file
        transactionsFILE.close();
        transactionsOUT="";
    //

cout<<"Transaction list can be found in transactions.txt\n\n";

cout<<"Simulating blockchain...\n\n";

    a=1;    //block number

    //create genesis block

    //

//cout<<"Genesis block created.\n\n";

    //output the genesis block

    //


    a++;    //update block number;






















//clean up
BLOCKCHAIN.clear();
USERS.clear();
POOL.clear();

return 0;
} // main