#ifndef BDD_H
#define BDD_H
#define nb \
  int

#include <mysql/mysql.h>

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>


struct caract
{
  char *fn; // first name
  char *ln; // last name
  nb eye; // valeur yeux
  nb mouth; // valeur bouche
  nb nose; // valeur nez
  struct caract *next;
};

struct faces
{
  nb total; // somme de tout les caract
  struct caract *caract;
  struct faces *next;
};

struct faces *init_faces();
void ins_carac(struct caract *c,char *fn,char *ln, nb eye, nb mouth, nb nose);
void insert_faces(struct faces *f,char *fn,char*ln,nb eye,nb mouth,nb nose);
int search_face(struct faces *f,char *name, char *lastname);
int create_database();
int ajout (struct faces* f);
int select_face  (struct faces*);
//int del_faces(struct faces *f,char *fn,char *ln);
//int change_faces(struct faces *f,char *fn,char *ln,nb eye,nb mouth,nb nose);
//void ecriture(struct faces *f, FILE *file);
//void lecture(FILE *file);
#endif /*BDD_H*/
