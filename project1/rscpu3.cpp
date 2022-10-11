//rscpu3.cpp



//
// rscpu3.cpp
// Deven Schwartz
// 3/2/2022
// Project 1.4
// Description: a subset of architecture opcodes: (ldac, stac, mvi) 
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


void LDAC(){

    DR = M[AR];
    PC++;
    AR++;

    //print out DR, PC, AR
    printf("LDAC1: DR = %d, PC = %d, AR = %d \n", DR, PC, AR);


    TR = DR;
    DR = M[AR];
    PC++;

    //print out TR, DR, AR, and PC
    printf("LDAC2: TR = %d, DR = %d, AR = %d, PC = %d \n", TR, DR, AR, PC);

    AR = TR * 256;
    AR = AR + DR;

    //print out AR
    printf("LDAC3: AR = %d \n", AR);

    DR = M[AR];

    //print out DR
    printf("LDAC4: DR = %d \n", DR);

    AC = DR;

    //print out AC
    printf("LDAC5: AC = %d \n", AC);

    //print out required vars
    printf("LDAC Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

    return;

}


void STAC(){

    DR = M[AR];
    PC++;
    AR++;

    //print out DR, PC, AR
    printf("STAC1: DR = %d, PC = %d, AR = %d \n", DR, PC, AR);


    TR = DR;
    DR = M[AR];
    PC++;

    //print out TR, DR, AR, and PC
    printf("STAC2: TR = %d, DR = %d, PC = %d \n", TR, DR, PC);

    AR = TR * 256;
    AR = AR + DR;

    //print out AR
    printf("STAC3: AR = %d \n", AR);

    DR = AC;

    //print out DR
    printf("STAC4: DR = %d \n", DR);

    //int beforeMAR = M[AR];
    //print out AC before 
    printf("STAC5 (before store location): AR = %d before = %d \n", AR, M[AR]);
    
    M[AR] = DR;

    //print out AC after
    //printf("STAC5 (before store location): AR = %d before = %d \n", AR, beforeMAR);
    printf("STAC5 (after store location): AR = %d after = %d \n", AR, M[AR]);

    //print out required vars
    printf("STAC Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

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
        AC = 0;//should already 0 but just in case
        temp2 = 0;
        Flag = Flag + C;
    }
    //check for overflow ()
    //if ac and 1 are pos and ans is neg overflow flag should be set
    //if ac and 1 are neg and ans is pos then flag is set
    if(temp1 <= 127 && temp1 + 1 >= 127){// only need to worry about ac bein pos and ans neg since 1 is pos 
        Flag = Flag + V;
    }
    //check for negative
    if(temp2 > 127){
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


void MVI(){


    DR = M[AR];
    PC++;
    AR++;

    //print out DR, PC, AR
    printf("MVI1: DR = %d PC = %d AR = %d \n", DR, PC, AR);

    AC = DR;

    //print out AC
    printf("MVI2: AC = %d \n", AC);

    //print out required vars
    printf("MVI Instruction execution complete: AC = %d R = %d flag = %d AR = %d PC = %d DR = %d \n", AC, R, Flag, AR, PC, DR);

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
    cout<<"Project 1 part 4: rscpu3"<<endl;
    cout<<"LDAC, STAC, and MVI insturctions implemented.\n"<<endl;
    //

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

            cout<<"NOP Instruction"<<endl;
            NOP();
            break; 

        case 1: 

            cout<<"LDAC Instruction"<<endl;
            LDAC();
            break; 
        
        case 2: 

            cout<<"STAC Instruction"<<endl;
            STAC();
            break; 
        
        case 4: 

            cout<<"MOVR Instruction"<<endl;
            MOVR();
            break; 
        
        case 3: 

            cout<<"MVAC Instruction"<<endl;
            MVAC();
            break; 
            

        case 11: 

            cout<<"CLAC Instruction"<<endl;
            CLAC();
            break; 

        case 10: 

            cout<<"INAC Instruction"<<endl;
            INAC();
            break; 
            
        case 22: 

            cout<<"MVI Instruction "<<endl;
            MVI();
            break; 
            
        case 255: //

            halt = false; 
            
            cout<<"HALT Instruction"<<endl;
            HALT();
            break;

        default:
            cout << "Invalid Instruction." << endl; 
            break;
        
        }//switch end

    }//end of loop
  
 
  
}//end of main


