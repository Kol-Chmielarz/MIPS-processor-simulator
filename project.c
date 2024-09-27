#include "spimcore.h"
/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	switch (ALUControl) {
		
	//case 0 a+b 
	case 0x0:
		*ALUresu;t = A+B;
		break;
	//case 1 a-b 
	case 0x1:
		*ALUresu;t = A-B;
		break;
	//case 2 if a>b z=1 else z=0
	case 0x2:
	if ((int)A> (int)B)
		*ALUresult = 1;
	else
		*ALUresult =0;
	break;
	//case 3 if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers) 
	case 0x3:
	if(A<B)
		*ALUresult=1;
	else
		*ALUresult=0;
	break;
	//case 4 Z = A AND B 
	case 0x4:
	*ALUresult=(A&B);
	break;
	//case 5 Z = A OR B 
	case 0x5:
	*ALUresult=(A|B);
	break;
	//case 6 Z = Shift B left by 16 bits 
	case 0x6:
	*ALUresult=B << 16;
	break;
	//case 7 Z = NOT A 
	case 0x7:
	*ALUresult= ~A;
	break;
	}
	
	if (*ALUresult == 0){  //Assign Zero to 1 if the result is zero; otherwise, assign 0.
		*Zero =1;
	}
	else {
		*Zero = 0;
	}
}
	
  
	
	
	
	
	
	

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	//Return 1 if not word alligned; otherwise, return 0. 
	if (PC%4 ==0){
		*instruction = Mem[PC>>2]; //You have to use (PC >> 2) 
		return 0;
	}
	else 
		return 1;
	}









/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned 
*r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{//(op, r1, r2, r3, funct, offset, jsec)
	
	*op = (instruction & 0xfc000000) >>26;//31-26
	*r1 = (instruction & 0x03e00000) >>21;//25-21
	*r2 = (instruction & 0x001f0000) >>16;//20-16
	*r3 = (instruction & 0x0000f800) >>11;//15-11
	*funct = instruction & 0x0000003f;//5-0
	*offset = instruction & 0x0000ffff;//15-0
	*jsec = instruction & 0x03fffff;//25-0
	
	
	
	
	
}








/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{//set all to 0
	controls->RegDst=0;
	controls->Jump=0;
	controls->Branch=0;
	controls->MemRead=0;
	controls->MemtoReg=0;
	controls->ALUOp=0;
	controls->MemWrite=0;
	controls->ALUSrc=0;
	controls->RegWrite=0;
	
	switch(op){
		case 0x0: //+- and or slt sltu
		controls->RegDst=1;
		controls->ALUOp=7;
		controls->RegWrite=1;
		break;
		case 0x8://addi
		controls->RegWrite=1;
		controls->ALUSrc=1;
		break;
		case 0x23: //lw
		controls->RegWrite=1;
		controls->ALUSrc=1;
		controls->MemtoReg=1;
		controls->MemRead=1;
		break;
		case 0x2b: //sw
		controls->MemWrite=1;
		controls->ALUSrc=1;
		break;
		case 0xf: //lui
		controls->RegWrite=1;
		controls->ALUOp=6;
		controls->ALUSrc=1;
		break;
		case 0x4: //beq
		controls->RegDst=2;
		controls->Branch=1;
		controls->MemtoReg=2;
		controls->ALUOp=1;
		controls->ALUSrc=2;
		break;
		case 0xa://slti
		controls->ALUSrc=1;
		controls->RegWrite=1;
		controls->ALUOp=2;
		break;
		case 0xb://sltiu
		controls->ALUSrc=1;
		controls->RegWrite=1;
		controls->ALUOp=3;
		break;
		case 0x2://j
		controls->RegDst=2;
		controls->Jump=1;
		controls->Branch=2;
		controls->MemtoReg=2;
		controls->ALUSrc=2;
		break;
		default:
			return 1;
	}
	return 0;
	
	
	
}





/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned 
*data2)
{//get vals from reg array and fill data
	*data1= Reg[r1];
	*data2 = Reg[r2];
	
}






/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{  //see if 16th bit is 1 to see if neg or not
	if ((offset >> 15)==1){
		*extended_value = offset | 0xffff0000; //if neg keep neg 
		}
	else
		*extended_value & 0x0000ffff;//if pos keep pos
	
	
	
	
}







/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned 
funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	unsigned ALUControl = ALUOp;
	
	
	//part keeps ruining rest of code 
	
	
	
	
	
}











/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned
*memdata,unsigned *Mem)
{//check memwrite and read if asserted and divisible by 4 for ALUresult address
	if(MemRead == 1){
		if(ALUresult %4==0){ 
			*memdata=Mem[ALUresult >> 2];//data2 to memlocation
		}
		else 
			return 1;
	}
	
	if(MemWrite == 1){
		if (ALUresult % 4==0 ){
			data2 = Mem[ALUresult>>2];
		}
		else
			return 1;
	}
	return 0;
	
	
	
}








/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned 
ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	if(RegWrite == 1){
		if(MemtoReg==1){//check if info from memory
			Reg[r2] = memdata;
		}
		else if(MemtoReg == 0){//determine which register coming from
			
			if(RegDst == 1){  //write register r3 rtype
				reg[r3]=ALUresult;
			}
			else  //is 0 so r2 I type
				reg[r2]=ALUresult;
		}
	}
	
	
	
}
/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char 
Zero,unsigned *PC)
{
	*PC = *PC +4;   //update by 4
	if(jump==1)  //if jump upper 4 bits and shift left bits of jsec 2
	{
		*PC = (*PC & 0xf000000) | (jsec <<2);
	}
	if (Branch ==1 && Zero==1){ //increment PC if branch is taken and ALU is recieved
		*PC = *PC + (extended_value << 2);
	}
	
	
}