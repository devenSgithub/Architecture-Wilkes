//rscpue.cpp

//
// rscpue.cpp
// Deven Schwartz
// 4/26/2022
// Project 2
// Description: added 16 bit versions of the instructions  
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
short DR = 0;
unsigned char IR = 0;
unsigned char TR = 0;
short AC = 0;
short R = 0;


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

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //no action break out
    //print out required vars
    //cout<< "NOP Instruction execution complete: AC= "<< AC << " R = "<< R << " flag = " << Flag << " AR = " << AR << " PC = " << PC << " DR = " << DR <<"\n"<< endl;
    printf("NOP Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void LDAC(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

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

    AC8 = DR;

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out AC
    printf("LDAC5: AC = %d \n", AC8);
    printf("LDAC5: ACE = %d \n", AC);

    //print out required vars
    printf("LDAC Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void LDAC16(){

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

    short temp0 = 0;
    short tempac = DR;
    tempac = tempac << 8;
    // AC = DR;

    AC = AC & temp0;

    AC = AC | tempac;

    //print out AC
    printf("LDAC5: ACE = %d \n", AC);

    DR++;
    AR++;
    DR = M[AR];

    printf("LDAC6: DR = %d AR = %d \n", DR, AR);

    AC = AC | DR;

     //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    printf("LDAC7: ACE = %d \n", AC);
    printf("LDAC7: AC = %d \n", AC8);

    //print out required vars
    printf("LDAC16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void STAC(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

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

    DR = AC8;

    //print out DR
    printf("STAC4: DR = %d \n", DR);

    //print out AC before 
    printf("STAC5 (before store location): AR = %d before = %d \n", AR, M[AR]);
    
    M[AR] = DR;

    //print out AC after
    printf("STAC5 (after store location): AR = %d after = %d \n", AR, M[AR]);

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out required vars
    printf("STAC Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void STAC16(){

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

    DR = AC >> 8;

    //print out DR
    printf("STAC4: DR = %d \n", DR);

    //print out AC before 
    printf("STAC5 (before store location): AR = %d before = %d \n", AR, M[AR]);
    
    M[AR] = DR;

    //print out AC after
    printf("STAC5 (after store location): AR = %d after = %d \n", AR, M[AR]);

    DR = AC;

    AR++;
    printf("STAC6: AR = %d \n", AR);

    printf("STAC7 (before store location): AR = %d before = %d DR = %d \n", AR, M[AR], DR);

    M[AR] = DR;

    printf("STAC7 (after store location): AR = %d after = %d \n", AR, M[AR]);





    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;


    //print out required vars
    printf("STAC16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}



void MOVR(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //move R into AC

    AC8 = R8;

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out AC
    printf("MOVR: AC = %d \n", AC8);
    printf("MOVR: ACE = %d \n", AC);

    //print out required vars
    printf("MOVR Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void MOVR16(){

    //move R into AC

    AC = R;

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out AC
    printf("MOVR: ACE = %d \n", AC);
    printf("MOVR: AC = %d \n", AC8);

    //print out required vars
    printf("MOVR Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void MVAC(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;

    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //move AC into R

    R8 = AC8;


    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out R
    printf("MVAC: R = %d \n", R8);
    printf("MVAC: RE = %d \n", R);

    //print out required vars
    printf("MVAC Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void MVAC16(){

    //move AC into R

    R = AC;

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;


    //print out R
    printf("MVAC: R = %d \n", R8);
    printf("MVAC: RE = %d \n", R);

    //print out required vars
    printf("MVAC16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void JUMP(){

    DR = M[AR];
    AR++;

    printf("JUMP 1: DR = %d AR = %d\n", DR, AR);

    TR = DR;
    DR = M[AR];

    printf("JUMP 2: TR = %d DR = %d\n", TR, DR);

    PC = TR * 256;
    PC = PC + DR;
    
    printf("JUMP 3: PC = %d\n", PC);

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out required vars
    printf("JUMP Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void JMPZ(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    if((Flag & Z) > 0){

        DR = M[AR];
        AR++;

        printf("JMPZ 1: DR = %d AR = %d\n", DR, AR);

        TR = DR;
        DR = M[AR];

        printf("JMPZ 2: TR = %d DR = %d\n", TR, DR);

        PC = TR * 256;
        PC = PC + DR;
        
        printf("JMPZ 3: PC = %d\n", PC);

        //print out required vars
        printf("JMPZ Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

        
    }else{
        PC++;
        printf("JMPC 1: PC = %d\n", PC);
        PC++;
        printf("JMPC 2: PC = %d\n", PC);
        
        printf("JMPZ Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    }
    return;

}


void JPNZ(){

        //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    if((Flag & Z) == 0){

        DR = M[AR];
        AR++;

        printf("JPNZ 1: DR = %d AR = %d\n", DR, AR);

        TR = DR;
        DR = M[AR];

        printf("JPNZ 2: TR = %d DR = %d\n", TR, DR);

        PC = TR * 256;
        PC = PC + DR;
        
        printf("JPNZ 3: PC = %d\n", PC);

        //print out required vars
        printf("JPNZ Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

        
    }else{
        PC++;
        printf("JMPC 1: PC = %d\n", PC);
        PC++;
        printf("JMPC 2: PC = %d\n", PC);

        printf("JPNZ Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    }
    return;

}


void JMPC(){

        //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    if((Flag & C) > 0){

        DR = M[AR];
        AR++;

        printf("JMPC 1: DR = %d AR = %d\n", DR, AR);

        TR = DR;
        DR = M[AR];

        printf("JMPC 2: TR = %d DR = %d\n", TR, DR);

        PC = TR * 256;
        PC = PC + DR;
        
        printf("JMPC 3: PC = %d\n", PC);

        //print out required vars
        printf("JMPC Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

        
    }else{
        PC++;
        printf("JMPC 1: PC = %d\n", PC);
        PC++;
        printf("JMPC 2: PC = %d\n", PC);

        printf("JMPC Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    }
    return;

}


void JV(){

        //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    if((Flag & V) > 0){

        DR = M[AR];
        AR++;

        printf("JV 1: DR = %d AR = %d\n", DR, AR);

        TR = DR;
        DR = M[AR];

        printf("JV 2: TR = %d DR = %d\n", TR, DR);

        PC = TR * 256;
        PC = PC + DR;
        
        printf("JV 3: PC = %d\n", PC);

        //print out required vars
        printf("JV Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

        
    }else{
        PC++;
        printf("JMPC 1: PC = %d\n", PC);
        PC++;
        printf("JMPC 2: PC = %d\n", PC);

        printf("JV Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    }
    return;

}


void JN(){

        //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    if((Flag & N) > 0){

        DR = M[AR];
        AR++;

        printf("JN 1: DR = %d AR = %d\n", DR, AR);

        TR = DR;
        DR = M[AR];

        printf("JN 2: TR = %d DR = %d\n", TR, DR);

        PC = TR * 256;
        PC = PC + DR;
        
        printf("JN 3: PC = %d\n", PC);

        //print out required vars
        printf("JN Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

        
    }else{
        PC++;
        printf("JMPC 1: PC = %d\n", PC);
        PC++;
        printf("JMPC 2: PC = %d\n", PC);

        printf("JN Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    }
    return;

}


void ADD(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;


    //AC<-AC + R, ZCVN set/reset
    //set a temp to ac, tempR to R, temp2 to added
    int temp1 = AC8;
    int tempR = R8;

    AC8 = AC8 + R8; 

    int temp2 = temp1 + tempR;

    //reset flag
    Flag = 0;

    //check for carry
    if(temp2 >= 256){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    temp2 = temp2 % 256;
    //check for overflow ()
    //if ac and 1 are pos and ans is neg overflow flag should be set
    //if ac and 1 are neg and ans is pos then flag is set
    if(temp1 <= 127 && tempR <= 127 && temp2 > 127){      
        Flag = Flag + V;
    }
    if(temp1 > 127 && tempR > 127 && temp2 <= 127){
        Flag = Flag + V;
    }
    
    //check for negative
    if(temp2 > 127){
        Flag = Flag + N;
    }

    //check for 0
    if(temp2 == 0 | temp2 % 256 == 0){
        Flag = Flag + Z;
    }


    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out R
    printf("ADD: AC = %d Flag = %d \n", AC8, Flag);
    printf("ADD: ACE = %d \n", AC);

    //print out required vars
    printf("ADD Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void ADD16(){

    //AC<-AC + R, ZCVN set/reset

   // AC = AC + R;

    //set a temp to ac, tempR to R, temp2 to added
    int temp1 = AC;
    int tempR = R;

    AC = AC + R; 

    int temp2 = temp1 + tempR;

    //reset flag
    Flag = 0;

    //check for carry
    if(temp2 >= 65536){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    temp2 = temp2 % 65536;
    //check for overflow ()
    //if ac and 1 are pos and ans is neg overflow flag should be set
    //if ac and 1 are neg and ans is pos then flag is set
    if(temp1 <= 32767 && tempR <= 32767 && temp2 > 32767){      
        Flag = Flag + V;
    }
    if(temp1 > 32767 && tempR > 32767 && temp2 <= 32767){
        Flag = Flag + V;
    }
    
    //check for negative
    if(temp2 > 32767){
        Flag = Flag + N;
    }

    //check for 0
    if(temp2 == 0 | temp2 % 65536 == 0){
        Flag = Flag + Z;
    }


    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;


    //print out R
    printf("ADD: AC = %d Flag = %d \n", AC8, Flag);
    printf("ADD: ACE = %d  \n", AC);

    //print out required vars
    printf("ADD Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void SUB(){

    //AC<-AC - R, ZCVN set/reset

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //set a temp to ac, tempR to R, temp2 to subbed
    unsigned short temp1 = AC8;
    int tempR = R8; //

    int temp2 = temp1 - tempR; 

    //reset flag
    Flag = 0;

    //take two com of ac for carry check
    int tempAC2 = (~AC8) + 1;
    int temp3 = tempAC2 - tempR;

    int tempR2 = (~R8) + 1;
    int temp32 = R8 - 128;

    AC8 = AC8 - R8; 
    int tempN = AC8;

    //check for carry
    if( (temp1>=tempR)){
        
        Flag = Flag + C;
    }

    if(tempN > 127){
        Flag = Flag + N;
    }

    temp2 = temp2 % 256;

    //check for overflow ()
    //if ac and 1 are pos and ans is neg overflow flag should be set
    //if ac and 1 are neg and ans is pos then flag is set
    if(temp1 > 127 && tempR < temp1 && (temp2) <= 127){    
        Flag = Flag + V; 
    }else if(temp1 <= 127 && tempR > temp1 && (temp2) > 127){    
        Flag = Flag + V; 
    }//check ac for the sign, R should be >< depending on sign and then the answer has to be changed sign


    //check for 0 or if multiple of 256(mod by val to get 0 )
    if(temp2 == 0 | temp2 % 256 == 0){
        Flag = Flag + Z;
    }

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out R
    printf("SUB: AC = %d Flag = %d \n", AC8, Flag);
    printf("SUB: ACE = %d \n", AC);

    //print out required vars
    printf("SUB Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void SUB16(){

    //AC<-AC - R, ZCVN set/reset

    //set a temp to ac, tempR to R, temp2 to subbed
    unsigned short temp1 = AC;
    int tempR = R; //

    int temp2 = temp1 - tempR; 

    //reset flag
    Flag = 0;

    //take two com of ac for carry check
    int tempAC2 = (~AC) + 1;
    int temp3 = tempAC2 - tempR;

    int tempR2 = (~R) + 1;
    int temp32 = R - 32768;

    AC = AC - R; 

    int tempN = AC;

    //check for carry
    if( (temp1>=tempR)){
        
        Flag = Flag + C;
    }

    temp2 = temp2 % 65536;

    //check for overflow ()
    //if ac and 1 are pos and ans is neg overflow flag should be set
    //if ac and 1 are neg and ans is pos then flag is set
    if(temp1 > 32767 && tempR < temp1 && (temp2) <= 32767){    
        Flag = Flag + V; 
    }else if(temp1 <= 32767 && tempR > temp1 && (temp2) > 32767){    
        Flag = Flag + V; 
    }//check ac for the sign, R should be >< depending on sign and then the answer has to be changed sign

    //mod max val so ints go back to 0 once at max like the actual ac
    temp2 = temp2 % 65536;

    //check for negative (above 127)
    if(temp2 > 32767){
        Flag = Flag + N;
    }
    
    //check for 0 or if multiple of 256(mod by val to get 0 )
    if(temp2 == 0 | temp2 % 65536 == 0){
        Flag = Flag + Z;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out R
    printf("SUB: ACE = %d Flag = %d \n", AC, Flag);
    printf("SUB: AC = %d \n", AC8);

    //print out required vars
    printf("SUB16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void CLAC(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //clear AC

    AC8 = 0;

    Flag = Z; 

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out Ac/Flag
    printf("CLAC: AC = %d Flag = %d \n", AC8, Flag);
    printf("CLAC: ACE = %d  \n", AC);

    //print out required vars
    printf("CLAC Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void CLAC16(){

    //clear AC

    AC = 0;

    Flag = Z; 

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out Ac/Flag
    printf("CLAC: AC = %d Flag = %d \n", AC8, Flag);
    printf("CLAC: ACE = %d  \n", AC);

    //print out required vars
    printf("CLAC16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}

void INAC(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //set a temp to ac, add 1 to ac and temp
    int temp1 = AC8;

    AC8 = AC8 + 1; 

    int temp2 = temp1 + 1;

    Flag = 0;
    //check for carry
    if(temp2 >= 256){//should not get above 256
        AC8 = 0;//should already 0 but just in case
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

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out AC/Flag
    printf("INAC: AC = %d Flag = %d \n", AC8, Flag);
    printf("INAC: ACE = %d  \n", AC);

    //print out required vars
    printf("INAC Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void INAC16(){

    //set a temp to ac, add 1 to ac and temp
    int temp1 = AC;

    AC = AC + 1; 

    int temp2 = temp1 + 1;

    Flag = 0;
    //check for carry
    if(temp2 >= 65536){//should not get above 256
        AC = 0;//should already 0 but just in case
        temp2 = 0;
        Flag = Flag + C;
    }
    //check for overflow ()
    //if ac and 1 are pos and ans is neg overflow flag should be set
    //if ac and 1 are neg and ans is pos then flag is set
    if(temp1 <= 32767 && temp1 + 1 >= 32767){// only need to worry about ac bein pos and ans neg since 1 is pos 
        Flag = Flag + V;
    }
    //check for negative
    if(temp2 > 32767){
        Flag = Flag + N;
    }
    //check for 0
    if(temp2 == 0){
        Flag = Flag + Z;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out AC/Flag
    printf("INAC: ACE = %d Flag = %d \n", AC, Flag);
    printf("INAC: AC = %d \n", AC8);

    //print out required vars
    printf("INAC16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void AND(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //AC<-AC bitwise AND R, ZN set/reset

    AC8 = AC8 & R8;

    //flag checks
    //set a temp to ac
    int temp1 = AC8;

    //reset for Z/N flags to 0
    Flag = (Flag & (C|V));
    //Flag = 0;

    //check for negative
    if(temp1 > 127){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }
    
    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out Ac/Flag
    printf("AND: AC = %d Flag = %d \n", AC8, Flag);
    printf("AND: AC = %d  \n", AC);

    //print out required vars
    printf("AND Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void AND16(){

    //AC<-AC bitwise AND R, ZN set/reset

    AC = AC & R;

    //flag checks
    //set a temp to ac
    int temp1 = AC;

    //reset for Z/N flags to 0
    Flag = (Flag & (C|V));
    //Flag = 0;

    //check for negative
    if(temp1 > 32767){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out Ac/Flag
    printf("AND: ACE = %d Flag = %d \n", AC, Flag);
    printf("AND: AC = %d  \n", AC8);

    //print out required vars
    printf("AND16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void OR(){

    //AC<-AC bitwise OR R, ZN set/reset

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    AC8 = AC8 | R8;
 
    //flag checks
    //set a temp to ac
    int temp1 = AC8;

    //reset flags to 0
    //Flag = 0;
    Flag = (Flag & (C|V));

    //check for negative
    if(temp1 > 127){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out Ac/Flag
    printf("OR: AC = %d Flag = %d \n", AC8, Flag);
    printf("OR: ACE = %d  \n", AC);

    //print out required vars
    printf("OR Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void OR16(){

    //AC<-AC bitwise OR R, ZN set/reset

    AC = AC | R;
 
    //flag checks
    //set a temp to ac
    int temp1 = AC;

    //reset flags to 0
    //Flag = 0;
    Flag = (Flag & (C|V));

    //check for negative
    if(temp1 > 32767){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out Ac/Flag
    printf("OR: ACE = %d Flag = %d \n", AC, Flag);
    printf("OR: AC = %d  \n", AC8);

    //print out required vars
    printf("OR16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void XOR(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //AC<-AC bitwise XOR R, ZN set/reset

    AC8 = AC8 ^ R8;
 
    //flag checks
    //set a temp to ac
    int temp1 = AC8;

    //reset flag to 0
    //Flag = 0;
    Flag = (Flag & (C|V));

    //check for negative
    if(temp1 > 127){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out Ac/Flag
    printf("XOR: AC = %d Flag = %d \n", AC8, Flag);
    printf("XOR: ACE = %d  \n", AC);

    //print out required vars
    printf("XOR Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void XOR16(){

    //AC<-AC bitwise XOR R, ZN set/reset

    AC = AC ^ R;
 
    //flag checks
    //set a temp to ac
    int temp1 = AC;

    //reset flag to 0
    //Flag = 0;
    Flag = (Flag & (C|V));

    //check for negative
    if(temp1 > 32767){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out Ac/Flag
    printf("XOR: ACE = %d Flag = %d \n", AC, Flag);
    printf("XOR: AC = %d \n", AC8);

    //print out required vars
    printf("XOR Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void NOT(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //AC<-AC bitwise NOT R, ZN set/reset

    AC8 = ~AC8;
 
    //flag checks
    //set a temp to ac
    int temp1 = AC8;

    //reset flags to 0
    //Flag = 0;
    Flag = (Flag & (C|V));

    //check for negative
    if(temp1 < 0){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out Ac/Flag
    printf("NOT: AC = %d Flag = %d \n", AC8, Flag);
    printf("NOT: ACE = %d  \n", AC);

    //print out required vars
    printf("NOT Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}

void NOT16(){

    //AC<-AC bitwise NOT R, ZN set/reset

    AC = ~AC;
 
    //flag checks
    //set a temp to ac
    int temp1 = AC;

    //reset flags to 0
    //Flag = 0;
    Flag = (Flag & (C|V));

    //check for negative
    if(temp1 < 0){
        Flag = Flag + N;
    }
    //check for 0
    if(temp1 == 0){
        Flag = Flag + Z;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out Ac/Flag
    printf("NOT: ACE = %d Flag = %d \n", AC, Flag);
    printf("NOT: AC = %d\n", AC8);

    //print out required vars
    printf("NOT Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void RL(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;


    int temp = AC;
    
    AC8 = (AC8 << 1) | (temp >> 7);

    int tempafter = AC8;

    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter > 127){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(temp > 127){
        
        //temp2 = 0;
        Flag = Flag + C;
    }


    //check for overflow 
    if(temp <= 127 && tempafter > 127){      
        Flag = Flag + V;
    }
    if(temp > 127 && tempafter <= 127){
        Flag = Flag + V;
    }
    
    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out AC and flag
    printf("RL: AC = %d Flag = %d \n", AC8, Flag);
    printf("RL: ACE = %d  \n", AC);

    //print out required vars
    printf("RL Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}

void RL16(){

    //AC = AC * 2;
    //(AC << 1)|(AC >> ( 1));
    unsigned short temp = AC;
    unsigned short temp2 = AC;
    
    AC = (temp2 << 1) | (temp >> 15);

    int tempafter = AC;

    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter > 32767){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(temp > 32767){
        
        //temp2 = 0;
        Flag = Flag + C;
    }


    //check for overflow 
    if(temp <= 32767 && tempafter > 32767){      
        Flag = Flag + V;
    }
    if(temp > 32767 && tempafter <= 32767){
        Flag = Flag + V;
    }
    
    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out AC and flag
    printf("RL: ACE = %d Flag = %d \n", AC, Flag);
    printf("RL: AC = %d  \n", AC8);

    //print out required vars
    printf("RL16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void RR(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;
   
    int temp = AC8;
    int tempcheck = AC8 % 2;

    AC8 = (AC8 >> 1) | (temp << 7 );

    int tempafter = AC8;
    
    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter > 127){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(tempcheck != 0){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    //check for overflow 
    if(temp <= 127 && tempafter > 127){      
        Flag = Flag + V;
    }
    if(temp > 127 && tempafter <= 127){
        Flag = Flag + V;
    }

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out AC and flag
    printf("RR: AC = %d Flag = %d \n", AC8, Flag);
    printf("RR: ACE = %d  \n", AC);

    //print out required vars
    printf("RR Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void RR16(){

    unsigned short temp = AC;
    unsigned short temp2 = AC;
    
    int tempcheck = AC % 2;

    AC = (temp2 >> 1) | (temp << 15 );

    int tempafter = AC;
    
    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter < 0){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(tempcheck != 0){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    //check for overflow 
    if(temp <= 32767 && tempafter < 0){      
        Flag = Flag + V;
    }
    if(temp < 0 && tempafter <= 32767){
        Flag = Flag + V;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out AC and flag
    printf("RR: ACE = %d Flag = %d \n", AC, Flag);
    printf("RR: AC = %d \n", AC8);

    //print out required vars
    printf("RR16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void LSL(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    int temp = AC8;
    AC8 = AC8 << 1;
    int tempafter = AC8;
    
    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter > 127){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(temp > 127){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    //check for overflow 
    if(temp <= 127 && tempafter > 127){      
        Flag = Flag + V;
    }
    if(temp > 127 && tempafter <= 127){
        Flag = Flag + V;
    }

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out AC and flag
    printf("LSL: AC = %d Flag = %d \n", AC8, Flag);
    printf("LSL: ACE = %d \n", AC);

    //print out required vars
    printf("LSL Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void LSL16(){

    int temp = AC;
    AC = AC << 1;
    int tempafter = AC;
    
    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter > 32767){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(temp > 32767){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    //check for overflow 
    if(temp <= 32767 && tempafter > 32767){      
        Flag = Flag + V;
    }
    if(temp > 32767 && tempafter <= 32767){
        Flag = Flag + V;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out AC and flag
    printf("LSL: AC = %d Flag = %d \n", AC8, Flag);
    printf("LSL: ACE = %d  \n", AC);

    //print out required vars
    printf("LSL16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void LSR(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    int temp = AC8;
    int tempcheck = AC8 % 2;

    AC8 = AC8 >> 1;

    int tempafter = AC8;
    
    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter > 127){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(tempcheck != 0){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    //check for overflow 
    if(temp <= 127 && tempafter > 127){      
        Flag = Flag + V;
    }
    if(temp > 127 && tempafter <= 127){
        Flag = Flag + V;
    }

    //stick 8 back on 16
    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;
    R = R>>8;
    R = R<<8;
    R = R | R8;

    //print out AC and flag
    printf("LSR: AC = %d Flag = %d \n", AC8, Flag);
    printf("LSR: ACE = %d  \n", AC);

    //print out required vars
    printf("LSR Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void LSR16(){

    int temp = AC;

    int tempcheck = AC % 2;

    AC = AC >> 1;

    int tempafter = AC;
    
    //reset flag
    Flag = 0;
    
    //check for negative
    if(tempafter > 32767){
        Flag = Flag + N;
    }

    //check for 0
    if(tempafter == 0){
        Flag = Flag + Z;
    }
    
    //check for carry
    if(tempcheck != 0){
        
        //temp2 = 0;
        Flag = Flag + C;
    }

    //check for overflow 
    if(temp <= 32767 && tempafter > 32767){      
        Flag = Flag + V;
    }
    if(temp > 32767 && tempafter <= 32767){
        Flag = Flag + V;
    }

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out AC and flag
    printf("LSR: AC = %d Flag = %d \n", AC8, Flag);
    printf("LSR: ACE = %d \n", AC);

    //print out required vars
    printf("LSR16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void MVI(){

    DR = M[AR];
    PC++;
    AR++;

    //print out DR, PC, AR
    printf("MVI1: DR = %d PC = %d AR = %d \n", DR, PC, AR);

    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    
    AC8 = DR;

    AC = AC>>8;
    AC = AC<<8;
    AC = AC | AC8;

    //print out AC
    printf("MVI2: AC = %d \n", AC8);
    printf("MVI2: ACE = %d \n", AC);

    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out required vars
    printf("MVI Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void MVI16(){

    DR = M[AR];
    PC++;
    AR++;

    //print out DR, PC, AR
    printf("MVI1: DR = %d PC = %d AR = %d \n", DR, PC, AR);

    short temp0 = 0;
    short tempac = DR;
    tempac = tempac << 8;

    AC = AC & temp0;

    AC = AC | tempac;

    //print out AC
    printf("MVI2: AC = %d \n", AC);

    DR = M[AR];
    PC++;
    AR++;

    //print out DR, PC, AR
    printf("MVI3: DR = %d PC = %d AR = %d \n", DR, PC, AR);

    AC = AC | DR;

     //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //print out AC
    printf("MVI4: ACE = %d \n", AC);
    printf("MVI4: AC = %d \n", AC8);

    //print out required vars
    printf("MVI16 Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}


void HALT(){

    //8 bit ac 
    unsigned char AC8;
    AC8 = 0;
    AC8 = AC8 | AC;
    //create R 8 bit for print
    unsigned char R8;
    R8 = 0;
    R8 = R8 | R;

    //halt execution 
    //print out required vars
    //cout<< "HALT Instruction execution complete: AC= "<< AC << " R = "<< R << " flag = " << Flag << " AR = " << AR << " PC = " << PC << " DR = " << DR <<"\n"<< endl;
    printf("HALT Instruction execution complete: AC = %d ACE = %d R = %d RE = %d flag = %d AR = %d PC = %d DR = %d \n", AC8, AC, R8, R, Flag, AR, PC, DR);

    return;

}



int main(){

    //common output
    cout<<"Deven Schwartz"<<endl;
    cout<<"Project 2: rscpue"<<endl;
    cout<<"16 bit version instructions implemented.\n"<<endl;
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
    //testing numbers 
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

        case 129: 

            cout<<"LDAC16 Instruction"<<endl;
            LDAC16();
            break; 
        
        case 2: 

            cout<<"STAC Instruction"<<endl;
            STAC();
            break; 

        case 130: 

            cout<<"STAC16 Instruction"<<endl;
            STAC16();
            break; 
        
        case 4: 

            cout<<"MOVR Instruction"<<endl;
            MOVR();
            break; 
        
        case 132: 

            cout<<"MOVR16 Instruction"<<endl;
            MOVR16();
            break; 

        case 3: 

            cout<<"MVAC Instruction"<<endl;
            MVAC();
            break; 

        case 131: 

            cout<<"MVAC16 Instruction"<<endl;
            MVAC16();
            break; 
            
        case 5: 

            cout<<"JUMP Instruction"<<endl;
            JUMP();
            
            break; 

        case 6: 

            cout<<"JMPZ Instruction"<<endl;
            JMPZ();
            
            break; 

        case 7: 

            cout<<"JPNZ Instruction"<<endl;
            JPNZ();
            
            break;

        case 16: 

            cout<<"JMPC Instruction"<<endl;
            JMPC();
            
            break;

        case 17: 

            cout<<"JV Instruction"<<endl;
            JV();
            
            break;

        case 23: 

            cout<<"JN Instruction"<<endl;
            JN();
            
            break; 

        case 8: 

            cout<<"ADD Instruction"<<endl;
            ADD();
            
            break; 
            
        case 9: 

            cout<<"SUB Instruction"<<endl;
            SUB();
            break; 
            
        case 11: 

            cout<<"CLAC Instruction"<<endl;
            CLAC();
            break; 

        case 10: 

            cout<<"INAC Instruction"<<endl;
            INAC();
            break; 

        case 136: 

            cout<<"ADD16 Instruction"<<endl;
            ADD16();
            
            break; 
            
        case 137: 

            cout<<"SUB16 Instruction"<<endl;
            SUB16();
            break; 
            
        case 139: 

            cout<<"CLAC16 Instruction"<<endl;
            CLAC16();
            break; 

        case 138: 

            cout<<"INAC16 Instruction"<<endl;
            INAC16();
            break; 

        case 12: 

            cout<<"AND Instruction"<<endl;
            AND();
            break; 
            
        case 13: 

            cout<<"OR Instruction"<<endl;
            OR();
            break; 
            
        case 14: 

            cout<<"XOR Instruction"<<endl;
            XOR();
            break; 
            
        case 15: 

            cout<<"NOT Instruction"<<endl;
            NOT();
            break; 
        
        case 18: 

            cout<<"RL Instruction"<<endl;
            RL();
            break; 

        case 19: 

            cout<<"RR Instruction"<<endl;
            RR();
            break; 

        case 20: 

            cout<<"LSL Instruction"<<endl;
            LSL();
            break; 

        case 21: 

            cout<<"LSR Instruction"<<endl;
            LSR();
            break; 

        case 22: 

            cout<<"MVI Instruction "<<endl;
            MVI();
            break; 

        case 140: 

            cout<<"AND16 Instruction"<<endl;
            AND16();
            break; 
            
        case 141: 

            cout<<"OR16 Instruction"<<endl;
            OR16();
            break; 
            
        case 142: 

            cout<<"XOR16 Instruction"<<endl;
            XOR16();
            break; 
            
        case 143: 

            cout<<"NOT16 Instruction"<<endl;
            NOT16();
            break; 
        
        case 146: 

            cout<<"RL16 Instruction"<<endl;
            RL16();
            break; 

        case 147: 

            cout<<"RR16 Instruction"<<endl;
            RR16();
            break; 

        case 148: 

            cout<<"LSL16 Instruction"<<endl;
            LSL16();
            break; 

        case 149: 

            cout<<"LSR16 Instruction"<<endl;
            LSR16();
            break; 

        case 150: 

            cout<<"MVI16 Instruction "<<endl;
            MVI16();
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


