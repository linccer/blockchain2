#include "hashFunction.h"



string hash(string input){

    unsigned long long unicode;
    vector<int> value;

     //  for each character of the input string:
    while (input.length()!=0){

        unicode = static_cast<int>(static_cast<char>(input[0]));    //get unicode
        //cout<<unicode<<" ";
        unicode = unicode * pow(X,(input.length() % 10));   //X raised to length % 9
        //cout<<unicode<<endl;

        add(value, unicode);


        input.erase(0, 1);
        unicode=0;
    }



    //adjust length to be over 64
    while(value.size()<64) {
        square(value); 
    }



    //output
    string output="";
    for (auto &i:value) {
        if(i<10) output+=to_string(i);
        else switch (i) {
            case 10: output+="a"; break;
            case 11: output+="b"; break;
            case 12: output+="c"; break;
            case 13: output+="d"; break;
            case 14: output+="e"; break;
            case 15: output+="f"; break;
        }
    }
    //reverse(output.begin(), output.end()); 
    value.clear();
    


    //shorten
    while(output.length()>64) {

        switch (output.length() % 10) {
            case 0: output.erase((output.length()/2), 1); break;
            case 1: output.erase((output.length()/6), 1); break;
            case 2: output.erase(1, 1); break;
            case 3: output.erase((output.length()*2/3), 1); break;
            case 4: output.erase((output.length()*5/9), 1); break;
            case 5: output.erase((output.length()/8), 1); break;
            case 6: output.erase((output.length()*3/7), 1); break;
            case 7: output.erase((output.length()/10), 1); break;
            case 8: output.erase((output.length()*15/23), 1); break;
            case 9: output.erase((output.length()*3/4), 1); break;
        }
    }
    //if (output.length()>64) output.erase(1, (output.length()-64));


    return output;
}





void add(vector<int>& vec, unsigned long long x) {
    unsigned long long carry = x;                      // Initialize the carry with the value of X

    for (size_t i = 0; i < vec.size(); ++i) {
        unsigned long long sum = vec[i] + carry;
        vec[i] = sum % 16;              // Update the current digit
        carry = sum / 16;               // Update the carry
    }

    // If there's a remaining carry, add it as a new digit
    while (carry > 0) {
        vec.push_back(carry % 16);
        carry /= 16;
    }
}



void square(vector<int>& vec) {
    vector<int> result(vec.size() * 2, 0);

    for (size_t i = 0; i < vec.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < vec.size(); ++j) {
            int product = vec[i] * vec[j] + result[i + j] + carry;
            result[i + j] = product % 16;
            carry = product / 16;
        }
        result[i + vec.size()] = carry;
    }

    // Remove zeros from front
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }


    vec = result;
}