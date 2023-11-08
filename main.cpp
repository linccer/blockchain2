#include "header.h"
#include "Block.h"
#include "User.h"
#include "Transaction.h"
#include "generatorFunctions.h"
#include "hashFunction.h"

block mine(string prevhash, string merkelhash, string miner, int nonce, double version, int DT, int &blocknum, bool &found, vector<transaction> &transactions);
string merkel_root_hash (vector<transaction> list);
void execute(vector<transaction> list, bool &invalid);
void checkTransactions();
//bool compareAmount(transaction& a, transaction& b) { return a.getAmount() > b.getAmount(); }    //for sorting POOL (desc)

//settings
const int USERcount = 1000;
const int TRANSACTIONcount = 10000;
const int private_key_length = 30;
const int difficulty_target = 5;
const double version = 1.0;


vector<block> BLOCKCHAIN;
vector<user> USERS;
unordered_map<string, size_t> USERindex;
vector<transaction> POOL;




//main
int main () {

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                                                               USERS
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

cout<<"\n";
cout<<"Creating users...\n\n";

    // CREATE USERS
        for (int a=0; a<USERcount; a++){

            user temp {randomName(), randomDouble(), randomString(private_key_length)};
            USERS.push_back(temp);
            USERindex[temp.getKey()] = USERS.size() - 1;
            //USERS[temp.getKey()] = temp;
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



//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                                                         TRANSACTIONS
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

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



//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                                                   BLOCKCHAIN SIMULATION
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

cout<<"Simulating blockchain...\n\n";

    a=1;    //block number
    bool block_found=false;

    int nonceA=0;
    string hashA="";
    string timeA="";

    //create genesis block

        while (!block_found){

            //timestamp
                auto now = std::chrono::system_clock::now();
                time_t now_c = std::chrono::system_clock::to_time_t(now);
                stringstream ss;
                ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
                getline(ss, timeA);
            

            //hash(PREV_BLOCK_HASH+"\n"+MERKEL_HASH+"\n"+TIMESTAMP+"\n"+std::to_string(NONCE)+"\n"+std::to_string(VERSION)+"\n"+std::to_string(DT))
            hashA=hash("-\n-\n" + timeA + "\n" + std::to_string(nonceA)+"\n"+to_string(version)+"\n"+to_string(difficulty_target));


            block_found=true;

            for (int a=difficulty_target-1; a>-1; a--){    //check if hash meets difficulty target
                if (hashA.at(a) != '0') {block_found=false; break;}
            }//for

            if (!block_found) nonceA++;

        }//while


        do {block TEMPblock{"-", "-", timeA, "Miner A", nonceA, version, difficulty_target, a}; //(string PREV_BLOCK_HASH, string MERKEL_HASH, string TIMESTAMP, string MINER, long long int NONCE, double VERSION, int DT, int BLOCK_NUMBER)
        BLOCKCHAIN.push_back(TEMPblock);} while (1==2);
    //

cout<<"Genesis block created.\n\n";

    //output the genesis block
    cout<<BLOCKCHAIN[0];
    //update block number
    a++;
    //






cout<<"\nSimulating mining with 5 miners: A, B, C, D, E...\n\n"; 

    bool mining=true;
    int fail=0;

    while (mining){

        block_found=false;
        nonceA=0;
        string miner="";
        string merkelA="", merkelB="", merkelC="", merkelD="", merkelE="";

        string prevhash = BLOCKCHAIN.at(BLOCKCHAIN.size()-1).getBLOCK_HASH();

        //shuffle (or sort) pool
        //if (fail<19500) std::shuffle(POOL.begin(), POOL.end(), generate);
        //else sort (POOL.begin(), POOL.end(), compareAmount);


        if (fail>19500){ checkTransactions();}

        //shuffle pool
        std::shuffle(POOL.begin(), POOL.end(), generate);


        //pick transactions
        vector<transaction> poolA;
        vector<transaction> poolB;
        vector<transaction> poolC;
        vector<transaction> poolD;
        vector<transaction> poolE;

        if (POOL.size()>500){

            for (int a=POOL.size()-1; a>POOL.size()-101; a--){  // A gets 100 last
                poolA.push_back(POOL.at(a));
            }//for

            for (int a=POOL.size()-101; a>POOL.size()-201; a--){  // B gets 2nd 100 last
                poolB.push_back(POOL.at(a));
            }//for

            for (int a=POOL.size()-1; a>POOL.size()-200; a=a-2){  // C gets every 2nd
                poolC.push_back(POOL.at(a));
            }//for

            for (int a=POOL.size()-1; a>POOL.size()-300; a=a-3){  // D gets every 3rd
                poolD.push_back(POOL.at(a));
            }//for

            for (int a=POOL.size()-1; a>POOL.size()-500; a=a-5){  // E gets every 5th
                poolE.push_back(POOL.at(a));
            }//for

        } else {

            for (int a=POOL.size()-1; a>POOL.size()-100; a--){  // give all miners last 100
                poolA.push_back(POOL.at(a));
                poolB.push_back(POOL.at(a));
                poolC.push_back(POOL.at(a));
                poolD.push_back(POOL.at(a));
                poolE.push_back(POOL.at(a));
            }//for

        }


   
        //calculate merkel hashes
        if (POOL.size()>=500){
        merkelA=merkel_root_hash(poolA);
        merkelB=merkel_root_hash(poolB);
        merkelC=merkel_root_hash(poolC);
        merkelD=merkel_root_hash(poolD);
        merkelE=merkel_root_hash(poolE);
        } else {
        merkelA=merkel_root_hash(poolA);
        merkelB=merkelA;
        merkelC=merkelA;
        merkelD=merkelA;
        merkelE=merkelA;
        }
        


        //block
        block tempblock;
        nonceA=0;

        while (block_found==false){

            //miner A
            tempblock = mine (prevhash, merkelA, "Miner A", nonceA, version, difficulty_target, a, block_found, poolA);
            if (block_found){miner="A"; break;}

            //miner B
            tempblock = mine (prevhash, merkelB, "Miner B", nonceA, version, difficulty_target, a, block_found, poolB);
            if (block_found){miner="B"; break;}

            //miner C
            tempblock = mine (prevhash, merkelC, "Miner C", nonceA, version, difficulty_target, a, block_found, poolC);
            if (block_found){miner="C"; break;}

            //miner D
            tempblock = mine (prevhash, merkelD, "Miner D", nonceA, version, difficulty_target, a, block_found, poolD);
            if (block_found){miner="D"; break;}

            //miner E
            tempblock = mine (prevhash, merkelE, "Miner E", nonceA, version, difficulty_target, a, block_found, poolE);
            if (block_found){miner="E"; break;}

            nonceA++;

        } // while


        //execute transactions
        bool invalid=false;
        
        if (miner=="A"){ execute (poolA, invalid); }
        else if (miner=="B") { execute (poolB, invalid); }
        else if (miner=="C") { execute (poolC, invalid); }
        else if (miner=="D") { execute (poolD, invalid); }
        else if (miner=="E") { execute (poolE, invalid); }
        else {invalid=true; cout<<"\n\nERROR - miner not assigned\n\n";}

        if (invalid==false){  // if transactions valid

        //add block to blockchain
        BLOCKCHAIN.push_back(tempblock);

        //delete transactions from the pool

            vector<transaction> skipped;
            int UpdatedPoolSize= POOL.size()-100;

            if (miner=="A"){ for(int a=0; a<100; a++) POOL.pop_back(); }


            else if (miner=="B") { 
                for(int a=0; a<100; a++) { skipped.push_back(POOL.at(POOL.size()-1)); POOL.pop_back(); }
                for(int a=0; a<100; a++) { POOL.pop_back(); }
            }//B

            
            else if (miner=="C") { 

                POOL.pop_back();
                int count=1;

                while ( POOL.size() + skipped.size() != UpdatedPoolSize ){

                    if (count%2==0) {POOL.pop_back();  count++;}
                    else {skipped.push_back(POOL.at(POOL.size()-1));   POOL.pop_back(); count++;}
                }//while
            }//C


            else if (miner=="D") {

                POOL.pop_back();
                int count=1;

                while ( POOL.size() + skipped.size() != UpdatedPoolSize ){

                    if (count%3==0) {POOL.pop_back();  count++;}
                    else {skipped.push_back(POOL.at(POOL.size()-1));   POOL.pop_back(); count++;}
                }//while
            }//D


            else if (miner=="E") { 
                
                POOL.pop_back();
                int count=1;

                while ( POOL.size() + skipped.size() != UpdatedPoolSize ){

                    if (count%5==0) {POOL.pop_back();  count++;}
                    else {skipped.push_back(POOL.at(POOL.size()-1));   POOL.pop_back(); count++;}
                }//while
            }//E


            for (auto i:skipped) POOL.push_back(i);                 //return to pool
            skipped.clear();
        //


        //output new block
        cout<<BLOCKCHAIN.at(BLOCKCHAIN.size()-1);
        cout<<POOL.size()<<" Transactions remaining in pool\n\n";

        fail=0;     // reset fail counter;

        } else {    // if transactions invalid
            a--;    //return block number to previous state
            fail++; //up fail counter
        }


        //clean up
        poolA.clear();
        poolB.clear();
        poolC.clear();
        poolD.clear();
        poolE.clear();

        //checks
        if (POOL.size()<100) {mining=false; if(POOL.size()>0) fail=1;}
        if (fail>20000) {mining=false; fail=2;}
        if (POOL.size()==100 && fail>0) {mining=false; fail=3;}


    } // while(mining)

if (fail==0) cout<<"\nBlockchain simulation complete.\n\n"; 
else {cout<<"\nBlockchain simulation ended early.\n";
    if (fail==1){cout<<"Cause: Less than 100 transactions left in pool. \n\n"; }
    else if (fail==2){cout<<"Cause: Unable to find a 100 valid transactions.\n\n"; }
    else if (fail==3){cout<<"Cause: Invalid transaction found in the last 100 transactions.\n\n"; }
}//else



//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                                                       FINAL OUTPUTS
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━



    //output blockchain to file
        string chainOUT="";
        ofstream chainFILE ("blockchain.txt");

        for (auto i:BLOCKCHAIN){

            string temp="";
            stringstream ss;
            ss<<i;
            chainOUT+="━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\nBLOCK " + to_string( i.getBLOCK_NUMBER() ) + "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
            
            while (getline(ss,temp)){
                chainOUT+="\n"+temp;
                temp="";
            }//while

            chainOUT+="\n\n\nTRANSACTIONS: \n\n";

            int b=1;

            for (auto e:i.getTransactionVector()){

                string temp="";
                stringstream ss;
                ss<<e;
                chainOUT+="TRANSACTION "+ to_string(b) + "\n";
                while (getline(ss, temp)){
                chainOUT+="\n"+temp;
                temp="";
                }//while
                chainOUT+="\n\n\n";
                b++;
            }

        } // for auto BLOCKCHAIN

        chainFILE<< chainOUT;
        chainFILE.close();
        chainOUT="";

    //

cout<<"Blockchain info can be found in blockchain.txt\n\n";



    //output users with updated balances to a new file
        string usersOUT2="";
        ofstream usersFILE2 ("users after simulation.txt");

        a=1; //counter

        for (auto i:USERS) {

            string temp="";
            stringstream ss;
            ss<<i;
            usersOUT2+="USER "+ to_string(a) + ":\n";
            while (getline(ss, temp)){
                usersOUT2+="\n"+temp;
                temp="";
            }//while
            usersOUT2+="\n\n\n";
            a++;
        }//for

        usersFILE2<< usersOUT2;
        usersFILE2.close();
        usersOUT2="";
    //

cout<<"User list with updated balances can be found in \"users after simulation.txt\"\n\n";



//     //output remaining transactions to file
//     if (fail>0) {
//         string transactionsOUT2="";                              //output string
//         ofstream transactionsFILE2 ("remaining transactions.txt");         //output file

//         a=1;    //reset counter

//         for (auto i:POOL){                                      //add transactions to output string

//             string temp="";
//             stringstream ss;
//             ss<<i;
//             transactionsOUT2+="TRANSACTION "+ to_string(a) + "\n";
//             while (getline(ss, temp)){
//                 transactionsOUT2+="\n"+temp;
//                 temp="";
//             }//while
//             transactionsOUT2+="\n\n\n";
//             a++;
//         }//for

//         transactionsFILE2<<transactionsOUT2;                      //output to file
//         transactionsFILE2.close();
//         transactionsOUT2="";
//     //

// cout<<"List of transactions left in the pool after simulation can be found in \"remaining transactions.txt\"\n\n";

//     }//if (fail>0)






//clean up
BLOCKCHAIN.clear();
USERS.clear();
POOL.clear();

return 0;
} // main

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

block mine(string prevhash, string merkelhash, string miner, int nonce, double version, int DT, int &blocknum, bool &found, vector<transaction> &transactions){

    //timestamp
    string time="";

        auto now = std::chrono::system_clock::now();
        time_t now_c = std::chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        getline(ss, time);


    //hash
    string HASH="";

        HASH=hash(prevhash+"\n" +merkelhash+"\n" +time+"\n" +to_string(nonce)+"\n" +to_string(version)+"\n" + to_string(DT));

    //check if hash fits
        found=true;
        for (int a=DT-1; a>-1; a--){    //check if hash meets difficulty target
        if (HASH.at(a) != '0') {found=false; break;}
        }//for

    //create block
    block newblock;
    if (found) {
        newblock = block(prevhash, merkelhash, time, miner, nonce, version, DT, blocknum, transactions);
        blocknum++;}

return newblock;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

string merkel_root_hash (vector<transaction> list) {

    vector<string> hashList;
    vector<string> temp;
    bool cycle=true;

    for (auto i:list){hashList.push_back(i.getID());}       // put transaction hashes into hashList

    while (cycle){

        if (hashList.size()%2 != 0){ hashList.push_back(hashList.at(hashList.size()-1)); } //if number of hashes is odd, duplicate last one

        bool first=true;
        for (int a=0; a<hashList.size(); a++){              // hash pairs, add them to temp
            
            if (first==true){
                first=false;
                temp.push_back(hash(hashList.at(a)+hashList.at(a+1)));
            }//if
        }//for

        hashList.clear();                                   // clear hash list
        for (auto i:temp) hashList.push_back(i);            // move hashes from temp to hashList
        temp.clear();                                       // clear temp

        if (hashList.size()==1) cycle=false;                // if only 1 hash is left, stop cycle

    }//while

    return hashList.at(0);
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

void execute(vector<transaction> list, bool &invalid){

    vector<transaction> excecuted;

        for (auto i:list){

            //indexes
            size_t senderIndex = USERindex[i.getSender()];
            size_t receiverIndex = USERindex[i.getReceiver()];


            if (USERS[senderIndex].getBalance()>=i.getAmount()){            // if sender balance larger than amount
                USERS[senderIndex].updateBalance( i.getAmount()*(-1) );     // update sender balance
                USERS[receiverIndex].updateBalance( i.getAmount() );        // update receiver balance

                excecuted.push_back(i);                                     //add transaction to executed
            } else {

                invalid=true;

                break;
            }//else

        }//for auto list


        //undo excecuted transactions
        if (invalid) {for (auto e:excecuted){

            //indexes
            size_t IndexSender = USERindex[e.getSender()];
            size_t IndexReceiver = USERindex[e.getReceiver()];

            USERS[IndexSender].updateBalance( e.getAmount() );                  // update sender balance
            USERS[IndexReceiver].updateBalance( e.getAmount() *(-1));           // update receiver balance
        }//for auto excecuted
        }

        excecuted.clear();
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

void checkTransactions(){

    vector<transaction> temporaryPOOL;

    for (auto i:POOL){

        //sender index
        size_t senderIndex = USERindex[i.getSender()];

        if (USERS[senderIndex].getBalance()>=i.getAmount()){    // if sender balance larger than transaction amount
        temporaryPOOL.push_back(i);
        }//if

    }//for

    int invalidTransactionCount=POOL.size()-temporaryPOOL.size();

    POOL.clear();                                               // clear current pool

    for (auto i:temporaryPOOL) POOL.push_back(i);               // put transactions back into pool

    temporaryPOOL.clear();                                      // clear temporary pool

    if (invalidTransactionCount!=0) cout<<"\nRemoved "<<invalidTransactionCount<<" invalid transactions from the pool\n";
}