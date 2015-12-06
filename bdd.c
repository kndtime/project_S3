#include <mysql/mysql.h>
#include <my_global.h>
#include <string.h>
#include "bdd.h"

int main (){
 struct faces* f = malloc(sizeof(struct faces));
 f = init_faces("Jacques","Jean",  11, 14,  12);
 struct faces* g = malloc(sizeof(struct faces));
 g = init_faces("Martin","Dupont",  11, 14,  12);
 f->next = g;
 create_database();
 modification(g);
 select_face(g);
 free(f);
 free(g);
 return 0;
}



struct faces *init_faces(char *fn, char *ln, nb eye, nb mouth , nb nose){
	struct faces *f = malloc(sizeof(struct faces));
	f->ln = ln;
        f->fn = fn;
        f->eye = eye;
        f->nose = nose;
        f->mouth = mouth;
	f->total = mouth + eye + nose;
	f->next = NULL;
	return f;
}


/* 2 fct de recherche nom/prenom et caracteristique*/

/* fct alloc qui renvois 1 struct faces contenant plusieur faces ou alors renvois juste la face si elle est seul*/

// fct ajout/suppr


int create_database()
{  
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "kenshin", 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  

  if (mysql_query(con, "CREATE DATABASE IF NOT EXISTS facedb")) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  mysql_close(con);
  return 1;
}


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int ajout (struct faces* f)
{ 
  MYSQL *con = mysql_init(NULL);
  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "root", "kenshin", "facedb", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
  /*if (mysql_query(con, "DROP TABLE IF EXISTS Visage")) {
      finish_with_error(con);
  }*/
  
  if (mysql_query(con, "CREATE TABLE IF NOT EXISTS Visage(Name TEXT, Lastname TEXT, Nose INT, Mouth INT, Eyes INT, Total INT)")) {      
      finish_with_error(con);
  }
  
  while (f != NULL){
	char s[1000];

	sprintf(s, "INSERT INTO Visage VALUES('%s' , '%s' , %d, %d, %d, %d);",  f->fn, f->ln, f->nose, f->mouth, f->eye, f->total);
	printf("%s\n",s);
  	if (mysql_query(con, s)) 
      	    		finish_with_error(con);
   	f= f->next;
	}
 	mysql_close(con);
  	return (1);
}

int select_face  (struct faces* f){ 
  int status = 0; 
 
  MYSQL *con = mysql_init(NULL);  
  
  char s[1000];

  sprintf(s, "SELECT Name, Lastname FROM Visage WHERE Total =%d;",  f->total);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, "localhost", "root", "kenshin", "facedb", 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, s)) 
  {
      finish_with_error(con);
  }
  
  do {  
      MYSQL_RES *result = mysql_store_result(con);
        
      if (result == NULL) 
      {
          finish_with_error(con);
      }
            
      MYSQL_ROW row = mysql_fetch_row(result);
      
      printf("%s %s\n", row[0],row[1]);
      
      mysql_free_result(result);
                 
      status = mysql_next_result(con); 
     
      if (status > 0) {
          finish_with_error(con);
      }
      
  } while(status == 0);
    
  mysql_close(con);  
  return(1);
}
	
int suppression(struct faces *f){

  MYSQL *con = mysql_init(NULL);

  char s[1000];

  sprintf(s, "DELETE FROM Visage WHERE NAME ='%s' && Lastname = '%s' ;",  f->fn , f->ln);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "kenshin", "facedb", 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, s))
  {
      finish_with_error(con);
  }

  mysql_close(con);
  return (1);

}

int modification(struct faces *f){

MYSQL *con = mysql_init(NULL);
  
  char s[1000];

  sprintf(s, "UPDATE Visage SET Nose = %d, Mouth = %d, Eyes = %d, Total = %d WHERE Name ='%s' && Lastname = '%s' ;",  f->nose , f->mouth , f->eye, f->total, f->fn, f->ln);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "kenshin", "facedb", 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, s))
  {
      finish_with_error(con);
  }

  mysql_close(con);
  return (1);
}

int search_face(struct faces *f, char* name, char* lastname){
	
	while (f != NULL && (f->fn != name && f->ln !=lastname))
	{
		f = f->next;
	}
	if (f!=NULL)
		return 1;
	return 0;
}

/*void insert_faces(struct faces *f, char *fn, char *ln, nb eye, nb mouth,nb nose){
	nb total = eye + nose + mouth;
	struct caract *c = malloc(sizeof(struct caract));
	struct faces *t = search_face(f,total);
	ins_carac(c, fn, ln, eye, mouth, nose);
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
}*/
