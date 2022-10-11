

//
// rscpu1.cpp
// Deven Schwartz
// 2/16/2022
// Project 1.2
// Description: a subset of architecture opcodes: (NOP, HALT) 
//



#include<fstream>
#include<cassert>
#include<iostream>
#include<string>

using namespace std;


#define Z 1 
#define C 2
#define V 4
#define N 8 


//Globals needed for opcode 
int M[65536];
int AR = 0;
int Flag = 0;
int PC = 0;
int DR = 0;
int IR = 0;
int TR = 0;
int AC = 0;
int R = 0;



void fetch(){

    AR = PC;
    cout<< "fetch 1:  AR = " << AR << " and PC = " << PC << endl;
    DR = M[AR];
    PC++;
    cout<< "fetch 2:  DR = " << DR << " and PC = " << PC << endl;
    IR = DR;
    AR = PC;
    cout<< "fetch 3:  IR = " << IR << " and AR = " << AR << endl;

}


void NOP(){

    //no action break out
    //print out required vars
    cout<< "NOP Instruction execution complete: AC= "<< AC << " R = "<< R << " flag = " << Flag << " AR = " << AR << " PC = " << PC << " DR = " << DR <<"\n"<< endl;
    
    return;

}


void HALT(){

    //halt execution 
    //print out required vars
    cout<< "HALT Instruction execution complete: AC= "<< AC << " R = "<< R << " flag = " << Flag << " AR = " << AR << " PC = " << PC << " DR = " << DR <<"\n"<< endl;
    
    return;

}



int main(){

    //common output
    cout<<"Deven Schwartz"<<endl;
    cout<<"Project 1 part 2: rscpu1"<<endl;
    cout<<"Nop and halt insturctions implemented.\n"<<endl;
    //

    //string M[65536];
    int cnt = 0;

    string fn;
    ifstream fin;
    
    string newitem;
    int n = 0;
  
    //enter the name of a file 
    cout<<"Please enter the name of the file containing your program: "<<endl;
    cin >> fn;
    cout<<"The file name entered is: "<<fn<<"\n"<<endl;
    fin.open(fn.c_str());
    assert(fin.is_open());
    while(true){
        //loop until eof / bad input 
        fin>>newitem;
        if(fin.eof() || !fin.good()){
            break;
        }

        //convert string hex into a decimal value
        //   std::stringstream ss;
        //  ss << hex << newitem;
        // ss >> n;
        string hex = "0x"+newitem;
        //n = stoi(newitem, 0, 16);
        //cout<<hex<<endl;
        n = stoi(hex, 0, 16);

        //store the value
        M[cnt] = n;
        //inc cnt
        cnt++;
        //cout<<"Value being read in: "<< M[cnt - 1] <<endl;
        //cout<<"hex: "<< hex << newitem <<endl;
     
    }//end of input loop


    //convert to binary or leave as decimal??????
    //kill loop on a halt statement
    while (DR != 255){

        /*
        
            Fetch1: AR<-PC
            Fetch2: DR<-M[AR], PC<-PC+1
            Fetch3: IR<-DR, AR<-PC

        */

        int input;  
        //loop until end
        
        //get next instru
        input = M[PC];

        //call fetch for fetch 1,2 and 3
        fetch();

        //switch to handle the input chocies 
        switch(input){
            
        case 0: 

            //cout<<"nop "<<endl;
            NOP();
            break; 
            
        //case #: 

            //other opcodes
            //function();
            //break; 
            
        
        case 255: //
            
            HALT();
            //cout<<"halt"<<endl;
            break;

        default:
            //cout << "Invalid Selection." << endl; 
            //halt ?????
            break;
        
        }//switch end

    }//end of loop
  
 
  
}//end of main

