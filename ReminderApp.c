#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define n 20

//Wait for enter to continue.
void clear_stream(){
    int Press_Enter;
    do {
        printf("\nPress <0> to continue...\n");
        scanf("%d",&Press_Enter);
    } while (Press_Enter!=0);
    return;
};

//Repeats a character n times.
void Replicate(char letter, int times){
    int i;
    printf("\n");
    for (i=0;i<times;i++){
        printf("%c",letter);
    };
    printf("\n");
    return;
};

//Contact structure.
typedef struct Contact{
    char fname[10];
    char lname[20];
    char MobileNum[12];
    char ZipCode[10];
    char City[20];
    char Country[15];
    char TIN[9];
    struct Contact *next;
} Contact;

Contact *newNode, *temp;

//Diary structure.
typedef struct Diary{
    Contact *list;
    char Name[20];
    char Description[20];
} Diary;

//Diary management.
Diary Diaries[n];

int DiaryCount;

void AddDiary(){
    DiaryCount++;
    Diaries[DiaryCount].list=(Contact *)malloc(sizeof(Contact));
    printf("\nName:");
    scanf("%20s",Diaries[DiaryCount].Name);
    printf("\nA brief description:");
    scanf("%20s",Diaries[DiaryCount].Description);
    printf("\nDiary created successfully!\n");
    return;
};

void DisplayDiaries(){
    int i;
        Replicate('-',50);
        printf("%26s","DIARIES");
        Replicate('-',50);
        printf("%-4s|","Ref.");
        printf("%-20s|","Name");
        printf("%-23s|","Description");
        Replicate('=',50);
    for (i=1;i<=DiaryCount;i++){
        printf("%-4d|",i);
        printf("%-20s|",Diaries[i].Name);
        printf("%-23s|",Diaries[i].Description);
        Replicate('-',50);
    };
    return;
};

void DeleteDiary(){
    int dNum;
    scanf("%d",&dNum);
    if (Diaries[dNum].list->next!=NULL){
        printf("The diary contains contacts. You can't delete it.\n");
    } else {
        int i;
        for (i=dNum;i<DiaryCount;i++){
            Diaries[i]=Diaries[i+1];
        };
        DiaryCount--;
    };
    return;
};

//Contact structure.
Contact *CreateContact(){
    newNode=(Contact *)malloc(sizeof(Contact));
    printf("First Name:  ");
    scanf("%10s",newNode->fname);

    printf("Last Name:  ");
    scanf("%20s",newNode->lname);

    printf("Mobile Phone:  ");
    scanf("%12s",newNode->MobileNum);

    printf("ZIP Code:  ");
    scanf("%10s",newNode->ZipCode);

    printf("City:  ");
    scanf("%20s",newNode->City);

    printf("Country:  ");
    scanf("%15s",newNode->Country);

    printf("TIN:  ");
    scanf("%9s",newNode->TIN);
    newNode->next=NULL;

    return newNode;
};

void AddContact(Contact *list, Contact *newNode){
    if (list==NULL){
        list=newNode;
    } else {
        temp=list;
        while (temp->next!=NULL){
            temp=temp->next;
        };
        temp->next=newNode;
    };
    printf("\nContact added successfully!\n");
    return;
};

void DeleteContact(Contact *Contactlist){
    int cNum;
    Contact *ContactToDelete;
    printf("\nSelect a contact to delete:\n");
    scanf("\n%d",&cNum);
    int i;
    temp=Contactlist;
    for (i=0;i<cNum-1;i++){
        temp=temp->next;
    };
    ContactToDelete=temp;
    temp->next=temp->next->next;
    free(ContactToDelete);
    printf("\nContact deleted successfully!\n");
    return;
};

void DisplayContact(Contact *list){
    int ContactCount=0;
    if (list==NULL){
        printf("***NO CONTACTS***\n");
    } else {
        temp=list->next;
        printf("%-4s|","Ref.");
        printf("%-9s|","TIN");
        printf("%-10s|","First Name");
        printf("%-20s|","Last Name");
        printf("%-15s|","Country");
        printf("%-20s|","City");
        printf("%-10s|","ZIP Code");
        printf("%-12s|","Mobile Phone");
        Replicate('=',109);
        while (temp!=NULL){
            ContactCount++;
            printf("%-4d|",ContactCount);
            printf("%-9s|",temp->TIN);
            printf("%-10s|",temp->fname);
            printf("%-20s|",temp->lname);
            printf("%-15s|",temp->Country);
            printf("%-20s|",temp->City);
            printf("%-10s|",temp->ZipCode);
            printf("%-12s|",temp->MobileNum);
            Replicate('-',109);
            temp=temp->next;
        };
    };
    return;
};

int main(){
    //Main menu.
    int choice;
    do {
        printf("\n[1] Create a new contact.\n");
        printf("\n[2] Display contacts of a diary.\n");
        printf("\n[3] Create a new diary.\n");
        printf("\n[4] Delete a diary.\n");
        printf("\n[9] Exit.\n\n");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                if (DiaryCount==0){
                    printf("\nThere are no diaries available.\n");
                    clear_stream();
                } else {
                    int dNum;
                    printf("\nSelect a diary to modify:\n");
                    scanf("%d",&dNum);
                    AddContact(Diaries[dNum].list,CreateContact());
                    clear_stream();
                };
                break;
            case 2:
                int dNum;
                DisplayDiaries();
                printf("\nSelect a diary to display:\n");
                scanf("%d",&dNum);
                Replicate('-',109);
                printf("Contacts of %s", Diaries[dNum].Name);
                Replicate('-',109);
                DisplayContact(Diaries[dNum].list);
                char ans;
                do {
                    printf("\nDelete a contact from this  diary?\n");
                    scanf("\n%c",&ans);
                    if (ans=='y'){
                        DeleteContact(Diaries[dNum].list);
                    } else {
                        break;
                    };
                } while (ans!='y' && ans!='n');
                clear_stream();
                break;
            case 3:
                printf("\nCreate a new diary:\n\n");
                AddDiary();
                DisplayDiaries();
                clear_stream();
                break;
            case 4:
                printf("\nSelect a diary to delete:\n");
                DisplayDiaries();
                DeleteDiary();
                DisplayDiaries();
                clear_stream();
                break;
            case 5:
                break;
            case 6:
                break;
        };
    } while (choice!=9);
    return 0;
};
