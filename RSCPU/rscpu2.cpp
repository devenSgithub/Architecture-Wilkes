//rscpu2.cpp



//
// rscpu2.cpp
// Deven Schwartz
// 2/24/2022
// Project 1.3
// Description: a subset of architecture opcodes: (clac, inac, mvac, and movr) 
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
unsigned char M[65536];
short AR = 0;
unsigned char Flag = 0;
short PC = 0;
unsigned char DR = 0;
unsigned char IR = 0;
unsigned char TR = 0;
unsigned char AC = 0;
unsigned char R = 0;


void fetch(){

    AR = PC;
   // cout<< "fetch 1:  AR = " << AR << " and PC = " << PC << endl;
    printf("fetch 1:  AR = %d and PC = %d \n", AR, PC);
    DR = M[AR];
    PC++;
   // cout<< "fetch 2:  DR = " << DR << " and PC = " << PC << endl;
    printf("fetch 2:  DR = %d and PC = %d \n", DR, PC);
    IR = DR;
    AR = PC;
    //cout<< "fetch 3:  IR = " << IR << " and AR = " << AR << endl;
    printf("fetch 3:  IR = %d and AR = %d \n", IR, AR);

}


void NOP(){

    //no action break out
    //print out required vars
    //cout<< "NOP Instruction execution complete: AC= "<< AC << " R = "<< R << " flag = " << Flag << " AR = " << AR << " PC = " << PC << " DR = " << DR <<"\n"<< endl;
    printf("NOP Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

    return;

}


void MOVR(){

    //move R into AC

    AC = R;

    //print out AC
    printf("MOVR: AC = %d \n", AC);

    //print out required vars
    printf("MOVR Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

    return;

}


void MVAC(){

    //move AC into R

    R = AC;

    //print out R
    printf("MVAC: R = %d \n", R);

    //print out required vars
    printf("MVAC Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

    return;

}


void CLAC(){

    //clear AC

    AC = 0;

    Flag = Z; 

    //print out Ac/Flag
    printf("CLAC: AC = %d Flag = %d \n", AC, Flag);

    //print out required vars
    printf("CLAC Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

    return;

}


void INAC(){

    //set a temp to ac, add 1 to ac and temp
    int temp1 = AC;

    AC = AC + 1; 

    int temp2 = temp1 + 1;

    Flag = 0;
    //check for carry
    if(temp2 >= 256){
        Flag = Flag + C;
    }
    //check for overflow
    //if ac and 1 are pos and ans is neg overflow flag should be set
    //if ac and 1 are neg and ans is pos then flag is set
    if(temp1 > 0 && temp2 < 0){// only need to worry about ac bein pos and ans neg since 1 is pos 
        Flag = Flag + V;
    }
    //check for negative
    if(temp2 < 0){
        Flag = Flag + N;
    }
    //check for 0
    if(temp2 == 0){
        Flag = Flag + Z;
    }

    //print out AC/Flag
    printf("INAC: AC = %d Flag = %d \n", AC, Flag);

    //print out required vars
    printf("INCA Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

    return;

}


void HALT(){

    //halt execution 
    //print out required vars
    //cout<< "HALT Instruction execution complete: AC= "<< AC << " R = "<< R << " flag = " << Flag << " AR = " << AR << " PC = " << PC << " DR = " << DR <<"\n"<< endl;
    printf("HALT Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

    return;

}



int main(){

    //common output
    cout<<"Deven Schwartz"<<endl;
    cout<<"Project 1 part 3: rscpu2"<<endl;
    cout<<"INAC, CLAC, MVAC, and MOVR insturctions implemented.\n"<<endl;
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

        string hex = newitem;

        //cout<<hex<<endl;
        n = stoi(hex, 0, 16);

        //store the value
        M[cnt] = n;
        //inc cnt
        cnt++;
        //cout<<"Value being read in: "<< M[cnt - 1] <<endl;
        //cout<<"hex: "<< hex << newitem <<endl;
     
    }//end of input loop


    //kill loop on a halt statement
    bool halt = true; 

    while (halt){

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
        
        case 4: 

            //cout<<"nop "<<endl;
            MOVR();
            break; 
        
        case 3: 

            //cout<<"nop "<<endl;
            MVAC();
            break; 
            

        case 11: 

            //cout<<"nop "<<endl;
            CLAC();
            break; 
            


        case 10: 

            //cout<<"nop "<<endl;
            INAC();
            break; 
            

        case 255: //

            halt = false; 
            
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


