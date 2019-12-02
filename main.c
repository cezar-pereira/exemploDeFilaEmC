//  main.c
//  exemploDeFilaEmC
//
//  Created by Cezar on 26/11/19.
//  Copyright © 2019 Cezar. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include <term.h>
#include "stdbool.h"


int validateOption(int option);
void cleanConsole(void);
Person * init(void);
void add(Person *personList);
void showCurrentPass(Person *personList);
void toList(Person *personList);
void callNextPass(Person **personList);
void randomPerson(Person *personList);
bool listIsEmpty(Person *personList);
char * checkIfPassIsCurrent(Person *personList);

Person *personCurrent;
int idCount = 0;

static inline void clearInputBuffer(void);

int main(){
    int option;

    Person *personList = init();

    while (1){
        printf("\n1 - Adicionar Senha. ");
        printf("\n2 - Listar todas as senhas. ");
        printf("\n3 - Mostrar senha atual. ");
        printf("\n4 - Chamar proxima senha. ");
        printf("\n5 - Sair. ");
        printf("\nOpcao: ");
        scanf("%i", &option);
        option = validateOption(option);
        
        switch (option)
        {
        case 1:
            add(personList);
            break;
        case 2:
            toList(personList);
            break;
        case 3:
            showCurrentPass(personList);
            break;
        case 4:
            callNextPass(&personList);
            break;
        case 5:
            exit(0);
            break;
        }
    }

    return 0;
}
int validateOption(int opcao){
    if (opcao < 1 || opcao > 5){
        printf("Digite uma opcao valida: ");
        scanf("%i", &opcao);
        return validateOption(opcao);
    }
    return opcao;
}

Person *init(){
    Person *list = (Person *)malloc(sizeof(Person));
    list->nextPerson = NULL;
    return list;
}

void add(Person *personList){
    clearInputBuffer();
    Person *person = (Person *)malloc(sizeof(Person));
    person->nextPerson = NULL;
    printf("\nDigite um nome: ");
    fgets(person->name, 50, stdin);
    person->id = idCount;
    idCount++;
    
    while (personList->nextPerson != NULL) {
        personList = personList->nextPerson;
    }

    personList->nextPerson = person;

    printf("SENHA ADICIONADA!\n\n");
}

void showCurrentPass(Person *personList){
    personCurrent = personList->nextPerson;
    if(listIsEmpty(personList))
        printf("Lista vazia!");
    else{
        printf("SENHA ATUAL: \n");
        printf("Nome: %s", personCurrent->name);
        printf("Senha: %i\n", personCurrent->id);
    }
}

void toList(Person *personList){
    personCurrent = personList->nextPerson;
    cleanConsole();

    if(listIsEmpty(personList))
        printf("Lista vazia!");
    else{
        Person *persons = (Person *) malloc(sizeof(Person));
        persons = personList->nextPerson;
        printf("SENHAS: ");
        while(persons != NULL){
            printf("\nNome: %s", persons->name);
            printf("Senha: %i", persons->id);
            printf("%s", checkIfPassIsCurrent(persons));
            printf("\n");
            persons = persons->nextPerson;
        }
    }
}

void callNextPass(Person **personList){
    if(listIsEmpty(*personList))
        printf("Lista Vazia!");
    else{
        Person *temp = (*personList)->nextPerson;
        (*personList)->nextPerson = temp->nextPerson;
        free(temp);
        personCurrent = (*personList)->nextPerson;
        showCurrentPass(*personList);
    }
}

char * checkIfPassIsCurrent(Person *personList){
    if(personList->id == personCurrent->id)
        return " (ATUAL)";
    else
        return "";
}

bool listIsEmpty(Person *personList){
    if(personList->nextPerson == NULL)
        return true;
    else
        return false;
}

void cleanConsole(){
   // system("clear");
}


static inline void clearInputBuffer()
{
    char c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}

