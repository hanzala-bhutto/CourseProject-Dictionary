#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#define dict "dictionary.txt"

FILE *data;

struct dictt{
   char word[20], meaning[400], sentence[400];
};

struct dictt *a;

void SearchWord(struct dictt *a);
void AddWord(struct dictt *a);
void DeleteWord(struct dictt *a);

void LowerWord(char *word, int a);

int main(){
    int choice;
    int l;
    system("color f1");
    system("cls");

    do{ 
		a = (struct dictt*)calloc(4000,sizeof(struct dictt));
	    
		printf("\n");
		for(l=0;l<120;l++){
	        printf("=");  
		}
        printf("\n\t\t\t\t\t\tWORD MEANING DICTIONARY\n");
		for(l=0;l<120;l++){
	        printf("=");  
		}
	    printf("\n");
		        
		printf("\n\n\t 1.) Search the meaning of a Word from Dictionary");
        printf("\n\n\t 2.) Add a Word and its Meaning to Dictionary");
        printf("\n\n\t 3.) Delete a Word and its Meaning from Dictionary");
        printf("\n\n\t 4.) Exit Dictionary");

        printf("\n\n\nSelect from any one of options(1-4): ");
        scanf("%d" , &choice);
        
        switch(choice){
            case 1:
                SearchWord(a);
                system("cls");
                break;
                
            case 2:
                AddWord(a);
                system("cls");
                break;
                
            case 3:
                DeleteWord(a);
                system("cls");
                break;
                
            case 4:
                exit(0);
				    
            default:
                system("cls");
				printf("\nWrong input! Kindly Choose/Select from the given options\n");       
        }
    }while(choice != 0);
    
	return 0;
}

void LowerWord(char *word , int a){
	if(*(word+a) == '\0'){
		;
	} 
	else{	
         *(word+a) = tolower(*(word+a)); 
         LowerWord(word ,++a);
    }
}

void SearchWord(struct dictt *a){
    system("cls");
    int n=0,l;
    char searchword[20];
    
	do{ 
		system("cls");

        printf("\n");
        for(l=0; l<120;l++){
            printf("=");
        }
        printf("\n\t\t\t\t\t\tSearch A Word\n");
        for(l=0; l<120;l++){
            printf("=");
        }    
        printf("\n");

        gets(searchword);
        printf("\nTry words:intend , consider , accord , concern , commit , forgive\n");
        printf("\n\tEnter the word you want the meaning for: ");
        gets(searchword);
        

        LowerWord(searchword,0);		
		
        data = fopen(dict , "r");
        
        if(data == NULL){
            printf("File does not exist.\n");
        }
	
        else{
        	n=0;
           
			while(fscanf(data,"%d",&(a+n)->word) != EOF){
				fscanf(data ,"%[^\n]\n%[^\n]\n%[^\n]\n",(a+n)->word,(a+n)->meaning , (a+n)->sentence);

                if(strcmp((a+n)->word , searchword)==0){
                    printf("\nword   : %s\n%s\n%s" ,(a+n)->word, (a+n)->meaning,(a+n)->sentence);
					break;
                }
                n++;
            }
        }
        
		if(strcmp((a+n)->word , searchword)!=0){
            printf("\n\tWord not found in dictionary\n\tKindly use option 2(add-word) from main menu to add the given word in dictionary.");
        }
        
		fclose(data);        
        printf("\n\n\n\tSearch more words (yes[input y]/no[input n]): ");

    }while(getchar()=='y');
    free(a);

}

void AddWord(struct dictt *a){
    char ch;
    int l,i=0;
    data = fopen(dict,"a");
    
	if(data == NULL){
        printf("File does not exist\n");
    }
    
	else{
        do{
            system("cls");
            
            printf("\n");
            for(l=0; l<120;l++){
                printf("=");
            }
            printf("\n\t\t\t\t\t\tAdd A Word\n");
            for(l=0; l<120;l++){
                printf("=");
            }    
            printf("\n");

            gets((a+i)->word);
            printf("\n\n\tEnter Word(in lower letters)  : ");
            gets((a+i)->word);
            printf("\n\tEnter Meaning : ");
            gets((a+i)->meaning);
            printf("\n\tEnter Sentence: ");
            gets((a+i)->sentence);

            fprintf(data ,"\n%s\nmeaning: %s\nsentence: %s\n",(a+i)->word, (a+i)->meaning, (a+i)->sentence);
            i++;
            printf("\n\nAdd more words (yes[input y]/no[input n]): ");

        }while(getchar()=='y');
    }
    fclose(data);
    free(a);
}

void DeleteWord(struct dictt *a){
    
    FILE *data2;
    char ch;
    char deleteword[20];
    int l,j=0;
    
    do{
        system("cls");

        data = fopen(dict, "r");

        printf("\n");
        for(l=0; l<120;l++){
            printf("=");
        }
        printf("\n\t\t\t\t\t\tDelete A Word\n");
        for(l=0; l<120;l++){
            printf("=");
        }    
        printf("\n");        
        
        gets(deleteword);
        printf("\n\tEnter word you want to delete from dictionary: ");
        gets(deleteword);
        
        LowerWord(deleteword,0);
        
        data2 = fopen("replicate.txt" , "a");
        rewind(data);
        
        while(fscanf(data,"%[^\n]\n%[^\n]\n%[^\n]\n" ,(a+j)->word,(a+j)->meaning ,(a+j)->sentence) != EOF){
            if(strcmp((a+j)->word , deleteword) != 0){
                fprintf(data2,"%s\n%s\n%s\n",(a+j)->word,(a+j)->meaning ,(a+j)->sentence);
                j++;
            }
        }j=0;
        
        fclose(data);
        fclose(data2);

        remove(dict);
        rename("replicate.txt" , dict);
        
        printf("\n\n Delete more words (yes[input y]/no[input n]): ");
    
    }while(getchar()=='y');
	free(a);
}

