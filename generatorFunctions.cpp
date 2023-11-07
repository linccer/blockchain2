#include "generatorFunctions.h"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> one_to_99(0, 99);                    //one_to_99(mt)
std::uniform_real_distribution<double> zero_to_mil(0.0, 1000000.0);     //zero_to_mil(mt)
std::uniform_int_distribution<int> dist(0, 61);                         //dist(mt)


string namesList[100]={
    "Garret", "Ava", "Liam", "Olivia", "Noah", "Isabella", "Lucas", "Sophia", "Mason", "Charlotte",
    "Ethan", "Amelia", "Oliver", "Harper", "Benjamin", "Aria", "Elijah", "Evelyn", "Logan", "Abigail",
    "James", "Elizabeth", "Michael", "Grace", "Henry", "Sofia", "Alexander", "Lily", "Sebastian", "Avery",
    "William", "Mia", "Daniel", "Scarlett", "Matthew", "Luna", "David", "Chloe", "Carter", "Victoria",
    "Joseph", "Madison", "Penelope", "Eli", "Riley", "Jack", "Hazel", "Owen", "Emma", "Grayson",
    "Leah", "Christopher", "Nathan", "Zoe", "Dylan", "Caleb", "Addison", "Aubrey", "Connor", "Aurora",
    "John", "Layla", "Levi", "Ariana", "Gabriel", "Hannah", "Natalie", "Evan", "Julia", "Samantha",
    "Cameron", "Sophie", "Eleanor", "Max", "Anthony", "Lucy", "Andrew", "Alexa", "Isaac", "Mila",
    "Aiden", "Bella", "Nicholas", "Thomas", "Alison", "Adam", "Ainsley", "Sidney", "Zachary", "Laura",
    "Ren", "Mitchell", "Douglas", "Vincent", "Desmond", "Adrian", "Russel", "Sandra", "Erica", "Calvin"
};


char charArray[62]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v', 'w','x','y','z'};


//______________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________


string randomName(){

    return namesList[one_to_99(mt)];
}


//______________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________


double randomDouble() { 

    return zero_to_mil(mt);
}

//______________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________


string randomString(int len) {

    string line="";

    for (int b=0; b<len; b++){
            line+=charArray[dist(mt)];
        }

    return line;

}

