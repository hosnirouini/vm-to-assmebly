#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<stdint.h>

#if 1


typedef  unsigned int        u32;
typedef  unsigned long int   u64;
typedef  unsigned short      u16;
typedef  unsigned char       u8;




#define  GLOBAL         static
#define  internal       static
 

  GLOBAL u16  line             = 1;
  GLOBAL u16  position         = 0;
  u16         SP               = 256;
  u16         LCL              = 1000;
  u16         ARG              = 1256; 
  u16         THAT             = 2256;
  u16         THISS            = 2000;


internal void
push_instruction(char* instruction,FILE* Asm)
{
  
    u16 i = 5;	
    u16 j = 0;
    u8  p;
    char table[20];
    fprintf(Asm,"\n// this is the instruction: %s\n",instruction);
    while(instruction[i]!=' ')
    {
      if (instruction[i] == ' ')
      {
        break;
      }
      else
      {
       table[j] = instruction[i];
       j++;
      }
      ++i;
    }
    while(instruction[i]!='\n')
    {
      if (instruction[i]>= '0' && instruction[i]<= '256') 
      {
        p = (int)(instruction[i]-48);
        break;
      }
      ++i;
    }  
    table[j] = '\0';
    if (strcmp(table,"local")== 0)
    {
      //TODO::
      fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\nA=D\nD=M\n@0\nM=M+1\nA=M\nM=D\n@0\nM=M+1\n",LCL,p);
    
    }
    else if (strcmp(table,"argument") == 0)
    {
      fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\nA=D\nD=M\n@0\nM=M+1\nA=M\nM=D\n@0\nM=M+1\n",ARG,p);
    
    }
    else if (strcmp(table,"this")== 0)
    {
      fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\nA=D\nD=M\n@0\nM=M+1\nA=M\nM=D\n@0\nM=M+1\n",THISS,p);
    
    }
    else if (strcmp(table,"that")== 0)
    {
      fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\nA=D\nD=M\n@0\nM=M+1\nA=M\nM=D\n@0\nM=M+1\n",THAT,p);
    
    }
    else if (strcmp(table,"constant")== 0)
    {
      fprintf(Asm,"@%d\nD=A\n@0\nA=M\nM=D\n@0\nM=M+1\n",p);
    
    }
    else if (strcmp(table,"static")== 0)
    {
      fprintf(Asm,"@0\nM=M-1\nA=M\nD=M\n@VM.%d\nM=D",p);
    
    }
    else if (strcmp(table,"temp")== 0)
    {
      fprintf(Asm,"@%d\nD=M\n@0\nA=M\nM=D\n@0\nM=M+1\n",p+5);
    
    }
    else if (strcmp(table,"pointer")== 0)
    {
      if (p == 0)
      {
        fprintf(Asm,"@13\nD=M\n@0\nA=M\nM=D\n@0\nM=M+1\n");
      }
      else if (p == 1)
      {
        fprintf(Asm,"@14\nD=M\n@0\nA=M\nM=D\n@0\nM=M+1\n");
      }
      else
      {
        printf("error in pointer location \n");
      }
    
    
    }
    else
    {
     printf("error in instruction table \n");
     fprintf(Asm,"error in instruction\n");
    } 
  }

internal void
pop_instruction(char* instruction,FILE *Asm)
{
    u16 i = 4;
    u16 j = 0;
    u8  p;
    char table[20];
    fprintf(Asm,"\n// this is the instruction: %s\n",instruction);
    while(instruction[i]!=' ')
    {
      if (instruction[i] == ' ')
      {
        break;
      }
      else
      {
        table[j] = instruction[i];
        j++;
      }
      ++i;
    }
    while(instruction[i]!='\n')
    {
      if (instruction[i]>= '0' && instruction[i]<= '256') 
      {
        p = (int)(instruction[i]-48);
        break;
      }
      ++i;
    }  
    table[j] = '\0';
    if (strcmp(table,"local")== 0)
    {
      //TODO::
      fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\n@5000\nM=D\n@0\nM=M-1\nA=M\nD=M\n@5000\nM=D\n",LCL,p);
    
    }
    else if (strcmp(table,"argument")== 0)
    {
      fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\n@5000\nM=D\n@0\nM=M-1\nA=M\nD=M\n@5000\nM=D\n",ARG,p);
    
    }
    else if (strcmp(table,"this")== 0)
    {
     fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\n@5000\nM=D\n@0\nM=M-1\nA=M\nD=M\n@5000\nM=D\n",THISS,p); 
    }
    else if (strcmp(table,"that")== 0)
    {
     fprintf(Asm,"@%d\nD=M\n@%d\nD=D+A\n@5000\nM=D\n@0\nM=M-1\nA=M\nD=M\n@5000\nM=D\n",THAT,p); 
    }
    else if (strcmp(table,"static")== 0)
    {
      fprintf(Asm,"@0\nM=M-1\nA=M\nD=M\n@VM.%d\nM=D",p);  
    }
    else if (strcmp(table,"temp")== 0)
    {
      fprintf(Asm,"@0\nM=M-1\nA=M\nD=M\n@%d\nM=D\n",p+5);
    
    }
    else if (strcmp(table,"pointer")== 0)
    {
      fprintf(Asm,"@%d\nD=M\n@0\nA=M\nM=D\n@0\nM=M+1\n",p+5);
    
    }
    else if (strcmp(table,"pointer")== 0)
    {
      if (p == 0)
      {
        fprintf(Asm,"@0\nM=M-1\nA=M\nD=M\n@13\nM=D\n");
      }
      else if (p == 1)
      {
        fprintf(Asm,"@0\nM=M-1\nA=M\nD=M\n@14\nM=D\n");
      }
      else
      {
        printf("error in pointer location \n");
      }
    }
    else
    {
    printf("error in instruction table \n");
    fprintf(Asm,"error in instruction\n");
    }
  
}

internal void
add_instruction(char* instruction,FILE *Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n@0\nM=M-1\nA=M\nM=M+D\n@0\nM=M+1\n");
}

internal void
sub_instruction(char* instruction,FILE *Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n@0\nM=M-1\nA=M\nM=M-D\n@0\nM=M+1\n");
}

internal void
equal_instruction(char* instruction,FILE* Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n@0\nM=M-1\nA=M\nD=M-D\n@%d\nD;JEQ\n@0\nA=M\nM=0;\n@%d\n0;JMP\n@0\nA=M\nM=1\n",
          position+16,position+19);
}

internal void
less_instruction(char* instruction,FILE* Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n@0\nM=M-1\nA=M\nD=M-D\n@%d\nD;JLT\n@0\nA=M\nM=0;\n@%d\n0;JMP\n@0\nA=M\nM=1\n",
          position+16,position+19);
}

internal void
grater_instruction(char* instruction,FILE* Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n@0\nM=M-1\nA=M\nD=M-D\n@%d\nD;JGT\n@0\nA=M\nM=0;\n@%d\n0;JMP\n@0\nA=M\nM=1\n",
          position+16,position+19);
}
internal void
And_instruction(char* instruction,FILE* Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n@0\nM=M-1\nA=M\nM=M&D\n");
}

internal void
Or_instruction(char* instruction,FILE* Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n@0\nM=M-1\nA=M\nM=M|D\n");
}

internal void
Not_instruction(char* instruction,FILE* Asm)
{
    fprintf(Asm,"\n// this is the instruction : %s \n",instruction);
    fprintf(Asm,"\n@0\nM=M-1\nA=M\nM=!M\n");
}

internal void
label_instruction(char* instruction,FILE* Asm)
{
  
    char label_name[15];
    u16  i = 5;
    u16  j = 0;
    while(instruction[i] != '\n')
    {
      if(instruction[i]!=' ')
      {
        label_name[j]=instruction[i];
         j++;
      }
      i++;
    }
    label_name[j]='\0';
    fprintf(Asm,"\n // this is a label \n");
    fprintf(Asm,"\n(%s)\n",label_name);
  
}

internal void
GOTO_instruction(char* instruction,FILE* Asm)
{
  char  label[15];
  u16   i = 4;
  u16   j = 0;
  while (instruction[i]!= '\n')
  {
    if (instruction[i]!=' ')
    {
      label[j]= instruction[i];
      j++;
    }
    i++;
  }
  label[j]='\0';
  fprintf(Asm,"\n // this is the instruction : %s \n",instruction);
  fprintf(Asm,"\n(%s)\n0;JMP\n",label);
}

internal void
IF_GOTO_instruction(char* instruction,FILE* Asm)
{
  char label[15];
  u16  i = 8;
  u16  j = 0;
  while (instruction[i]!= '\n')
  {
    if(instruction[i]!=' ')
    {
      label[j]= instruction[i];
      j++;
    }
    i++;
  }
  label[j]='\0';
  fprintf(Asm,"\n // this is the instruction : %s \n",instruction);
  fprintf(Asm,"\n@0\nM=M-1\nA=M\nD=M\n(%s)\nD;JEQ\n",label);
}

internal void
function_instruction(char* instruction,FILE* Asm)
{
  fprintf(Asm,"\n // this is the instruction : %s \n",instruction);
  
  //TODO::
   
}

internal void
call_instruction(char* instruction,FILE* Asm)
{
  fprintf(Asm,"\n // this is the instruction : %s \n",instruction);
  //TODO::
}

int main(int argc,char** argv)
{

  system("Color 2");
  printf("**************************************************************************\n");
  printf("*      virtual machine translate a vm language to assembly language      *\n");
  printf("*                                                                        *\n");
  printf("**************************************************************************\n");
  

  
    FILE *vm  = fopen("vm.txt","r");
    FILE *Asm = fopen("asm.txt","w");
    if (vm == NULL)
    {
      printf("error in oppening the vm file \n");
      exit(1);
    }
    if (Asm == NULL)
    {
      printf("error in oppening the asm file");
      exit(1);
    }
    else
    {
      fprintf(Asm,"                         ******** ASSEMBLY LANGUAGE ********\n");
      char instruction[30];
    while (fgets (instruction,30,vm)!= NULL)
    {
      /*puts(instruction);
        printf("\n");*/
      if (strncmp(instruction,"push",4)== 0||strncmp(instruction,"PUSH",2)== 0)
      {
        push_instruction(instruction,Asm);
        position += 12;
        line++;
      }
      else if (strncmp(instruction,"pop",3)== 0||strncmp(instruction,"POP",2)== 0)
      {
        pop_instruction(instruction,Asm);
        position += 12;
        line++;
      }
      else if (strncmp(instruction,"add",3)== 0||strncmp(instruction,"ADD",2)== 0)
      {
        add_instruction(instruction,Asm);
        position += 10;
        line++;
      }
      else if (strncmp(instruction,"sub",3)== 0 ||strncmp(instruction,"SUB",2)== 0)
      {
        sub_instruction(instruction,Asm);
        position += 10;
        line++;
      }
      else if (strncmp(instruction,"eq",2) == 0||strncmp(instruction,"EQ",2)== 0)
      {
        equal_instruction(instruction,Asm);
        position +=18;
        line++;
      }
      else if (strncmp(instruction,"lt",2)== 0||strncmp(instruction,"LT",2)== 0)
      {
        less_instruction(instruction,Asm);
        position +=18;
        line++;
      }
      else if (strncmp(instruction,"gl",2)== 0||strncmp(instruction,"GL",2)== 0)
      {
        grater_instruction(instruction,Asm);
        position +=18;
        line++;
      }
      else if (strncmp(instruction,"and",3)== 0||strncmp(instruction,"AND",2)== 0)
      {
        And_instruction(instruction,Asm);
        position += 8;
        line++;
      }
      else if (strncmp(instruction,"or",2)== 0||strncmp(instruction,"OR",2)== 0)
      {
        Or_instruction(instruction,Asm);
        position += 8;
        line++;
      }
      else if (strncmp(instruction,"not",3)== 0||strncmp(instruction,"NOT",2)== 0)
      {
        Not_instruction(instruction,Asm);
        position += 4;
        line++;
      }
      else if (strncmp(instruction,"label",5)==0||strncmp(instruction,"LABEL",5)== 0)
      {
	    label_instruction(instruction,Asm);
	    position +=1;
	    line++;
      }
      else if (strncmp(instruction,"goto",4)==0||strncmp(instruction,"GOTO",4)== 0)
      {
	    GOTO_instruction(instruction,Asm);
	    position +=2;
	    line++;
      }
      else if (strncmp(instruction,"if",2)==0||strncmp(instruction,"IF",2)== 0)
      {
	    IF_GOTO_instruction(instruction,Asm);
	    position +=6;
	    line++;
      }
      else if (strncmp(instruction,"call",4)==0||strncmp(instruction,"CALL",4)==0)
      {
	    call_instruction(instruction,Asm);
	    line++;
      }
      else if (strncmp(instruction,"function",8)==0||strncmp(instruction,"FUNCION",8)==0)
      {
	    function_instruction(instruction,Asm);
	    line++;
      }
      else if (strncmp(instruction,"call",4)==0 || strncmp(instruction,"CALL",4)== 0)
      {
	call_instruction(instruction,Asm);
	line++;
      }
      else if (strncmp(instruction,"//",2)== 0)
      {
        continue;
        line++;
      }
      else
      {
        printf("error in instruction ::line %d\n ",line);
      }
         
    }
     fprintf(Asm,"\n// END PROGRAM \n");
     fprintf(Asm,"@%d\n0;jmp\n",position+1);
     fclose(vm);
     fclose(Asm);
    }
    

     
    system("pause");
    return (0);

}

#else


int add(int x,int y)
{
  return x+y;
}

int sub(int x,int y)
{
  return x-y;
}


int compute(int(*comp)(int,int),int x,int y)
{
  return (comp(x,y));  
}





int main(int argc,char** argv)
{
  printf("another program \n");
  int x = 10;
  int y = 5;
  printf("%d\n",compute(add,x,y));
  system("pause");
  return 0;
}
#endif

