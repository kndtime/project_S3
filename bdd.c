#include "bdd.h"


int main(){
	return 0;
}
struct faces *init_faces(nb total){
	struct faces *f = malloc(sizeof(struct faces));
	f->total = total;
	f->caract = NULL;
	f->next = NULL;
	return f;
}

void ins_carac(struct caract *c, char *fn, char *ln, nb eye, nb mouth , nb nez){
	c->ln = ln;
	c->fn = fn;
	c->eye = eye;
	c->nez = nez;
	c->bouche = mouth;
}
struct faces *search_face(struct faces *f, nb total){
	while (f != NULL && f->total != total)
	{
		f = f->next;
	}
	return f;
}

void insert_faces(struct faces *f, char *fn, char *ln, nb eye, nb mouth,nb nez){
	nb total = eye + nez + mouth;
	struct caract *c = malloc(sizeof(struct caract));
	struct faces *t = search_face(f,total);
	ins_carac(c, fn, ln, eye, mouth, nez);
	if(t){
		c->next = t->caract;
		t->caract=c;
	}
	else{
		t=f;
		if(f==NULL || f->total > total){
			f = init_faces(total);
			f->caract = c;
			f->next = t;
		}
		else{
			while(t->next != NULL && t->next->total < total){
				t = t-> next;
			}
			struct faces *new = init_faces(total);
			c->next = NULL;
			new->caract = c;
			new->next = t->next;
			t->next = new;
		}
	}
}

int del_faces(struct faces *f,char *nom, char *prenom){
	struct caract *c;
	struct faces *t = f;
	while(f != NULL){
		c = f->caract;
		while( c != NULL){
			if(strcmp(c->ln, nom) == 0 && strcmp(c->fn, prenom) == 0){
				f->caract = NULL;
				t->next = f-> next;
				free(f);
				free(c);
				return 1;
			}
			c = c->next;
		}
		t = f;
		f = f->next;
	}
	return 0;
}

int modif_faces(struct faces *f, char *nom, char *prenom, nb eye, nb mouth, nb nez){
	int b = del_faces(f, nom, prenom);
	insert_faces(f, prenom, nom, eye, mouth, nez);
	return b;
}

void ecriture(struct faces *f, FILE *file){
	file = NULL;
	file =	fopen("text.txt", "w");
	if (file != NULL){
		struct faces *t = f;
		while(t != NULL){
			struct caract *c = t->caract;
			fprintf(file, "%u\n", t->total);
			while(c != NULL){
				fprintf(file,", %s ", c->fn);
				fprintf(file,", %s\n", c->ln);
				fprintf(file,", %u ", c->eye);
				fprintf(file,", %u ", c->bouche);
				fprintf(file,", %u\n ", c->nez);
				c=c->next;
			}
			t = t->next;
		}
		fclose(file);
	}
}

void lecture(FILE *file){
	file = NULL;
	file = fopen("text.txt", "r");
	int m = 1000;
	char chaine[m];
	while (fgets(chaine, m, file) != NULL){
		printf("%s\n", chaine);
	}
	fclose(file);
}
