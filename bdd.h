#ifndef BDD_H
#define BDD_H
#define nb \
  unsigned int

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

struct caract
{
  char *fn; // first name
  char *ln; // last name
  nb eye; // valeur yeux
  nb bouche; // valeur bouche
  nb nez; // valeur nez
  struct caract *next;
};

struct faces
{
  nb total; // somme de tout les caract
  struct caract *caract;
  struct faces *next;
};

struct faces *init_faces();
void ins_carac(struct caract *c,char *fn,char *ln, nb y, nb neb, nb nm);
void insert_faces(struct faces *f,char *fn,char*ln,nb y,nb neb,nb nm);
struct faces *search_faces(struct faces *f,nb total);
int del_faces(struct faces *f,char *fn,char *ln);
int change_faces(struct faces *f,char *fn,char *ln,nb y,nb neb,nb nm);
#endif /*BDD_H*/
