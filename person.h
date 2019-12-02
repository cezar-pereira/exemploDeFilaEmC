//
//  person.h
//  exemploDeFilaEmC
//
//  Created by Cezar on 26/11/19.
//  Copyright © 2019 Cezar. All rights reserved.
//

#ifndef person_h
#define person_h
#include <stdio.h>

typedef struct person
{
    int id;
    char name[50];
    struct person *nextPerson;
} Person;

#endif /* person_h */
