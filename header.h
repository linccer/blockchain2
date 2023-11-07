# ifndef HEADER_H
# define HEADER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>	
#include <iomanip>
#include <limits>	
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <bitset>
using std::string;
using std::vector;
using std::sort;
using std::accumulate;
using std::ostream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::copy;
using std::numeric_limits;
using std::streamsize;
using std::ifstream;
using std::istringstream;
using std::stable_partition;
using std::partition_point;
using std::reverse;

using std::stringstream;
using std::to_string;
using std::bitset;


class person {

protected:
    string v,p;

public:
    //konstruktorius
    person(): v(""), p("") {}

    //set
    virtual void setv(string vardas) = 0;
    virtual void setp(string pavarde) = 0;
    
};//person


class student : public person {

private:
    //string v, p;
    double vidurkis, mediana;

public:

//konstruktoriai
    student () : person() {
        vidurkis=0;
        mediana=0;
    }

    student (string var, string pav, vector<int> &balai, int egz) {
        v=var; 
        p=pav;

        vidurkis=accumulate(&balai[0], &balai[balai.size()], 0.);   //suma
        vidurkis=(vidurkis/(balai.size()*1.0))*0.4  + (0.6*egz);
        
        sort(balai.begin(),balai.end());
        if ((balai.size())%2==0) mediana=(balai[(balai.size()/2)-1]*1.0+balai[(balai.size()/2)]*1.0)/2;
        else mediana=balai[(balai.size()/2)];
        mediana=(mediana*0.4)  + (0.6*egz);

        balai.clear();
    }

    //copy 
    student (const student& s){
        v=s.v;
        p=s.p;
        vidurkis=s.vidurkis;
        mediana=s.mediana;
    }

    //assignment
    student& operator=(const student& s){
        v=s.v;
        p=s.p;
        vidurkis=s.vidurkis;
        mediana=s.mediana;
        return *this;
    }

    //move
    student (student&& s) noexcept{
    v=s.v;
    p=s.p;
    vidurkis=s.vidurkis;
    mediana=s.mediana;
    s.~student();
    }

    //assignment
    student& operator=(student&& s) noexcept{
    v=s.v;
    p=s.p;
    vidurkis=s.vidurkis;
    mediana=s.mediana;
    s.~student();
    return *this;
    }

//

//getter
    string gfirstname () { return v; }
    string glastname () { return p; }
    double gavg () { return vidurkis; }
    double gmed () { return mediana; }
//

//set
    void setp(string pavarde){p=pavarde;}
    void setv(string vardas){v=vardas;}
//

//cout
    friend ostream &operator<<(ostream &out, student &stud){
        out <<left<<setw(15)<<stud.v
        <<left<<setw(21)<<stud.p
        <<left<<setw(18)<<std::fixed<<setprecision(2)<<stud.vidurkis
        <<left<<std::fixed<<setprecision(2)<<stud.mediana;

        return out;
    }
//

//destruktorius
    ~student(){ v.clear(); p.clear(); vidurkis=0; mediana=0;}

};
# endif