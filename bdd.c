#include <mysql/mysql.h>
#include "bdd.h"

int main (){
 struct faces* f = init_faces();
 struct caract* c= NULL;
 ins_carac(c,"Jacques","Jean",  11, 14,  12);
 f->caract = c;
 create_database();
 ajout(f);
 select_face(f);
 return 0;
}



struct faces *init_faces(nb total){
	struct faces *f = malloc(sizeof(struct faces));
	f->total = total;
	f->caract = NULL;
	f->next = NULL;
	return f;
}

void ins_carac(struct caract *c, char *fn, char *ln, nb eye, nb mouth , nb nose){
	c->ln = ln;
	c->fn = fn;
	c->eye = eye;
	c->nose = nose;
	c->mouth = mouth;
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

  if (mysql_real_connect(con, "localhost", "root", "root_pswd", 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  

  if (mysql_query(con, "CREATE DATABASE facedb")) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  mysql_close(con);
  exit(0);
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

  if (mysql_real_connect(con, "localhost", "user12", "34klq*", "facedb", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, "DROP TABLE IF EXISTS Visage")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE Visage(Name TEXT, Lastname TEXT, Nose INT, Mouth INT, Eyes INT, Total INT)")) {      
      finish_with_error(con);
  }
  
  while (f != NULL){
	struct caract* c  = f->caract;
	if (search_face(f,c->fn,c->ln) == 0){
  		if (mysql_query(con, "INSERT INTO Visage VALUES(c->fn, c->ln, c->nose, c->mouth, c->eyes, f->total)")) {
      	    		finish_with_error(con);
			f=f->next;
  		}	
	}
	else {
		 if (mysql_query(con, "UPDATE Visage SET Mouth = c->mouth, SET Nose = c->nose, SET Eyes = c->eyes, SET Total = c->total WHERE Lastname = c->ln ")){
			finish_with_error(con);		
		 }
	}
   }		
   
 	mysql_close(con);
  	exit(0);
}

int select_face  (struct faces* f){ 
  int status = 0; 
  struct caract* c  = f->caract;
  f->caract = c;
  MYSQL *con = mysql_init(NULL);  
  
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, "localhost", "user12", "34klq*", 
          "facedb", 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, "SELECT Name FROM Visage WHERE Lastname = c->ln, Name = c->fn")) 
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
      
      printf("%s\n", row[0]);
      
      mysql_free_result(result);
                 
      status = mysql_next_result(con); 
     
      if (status > 0) {
          finish_with_error(con);
      }
      
  } while(status == 0);
    
  mysql_close(con);  
  exit(0);
}









int search_face(struct faces *f, char* name, char* lastname){
	struct caract* c = f->caract;
	while (f != NULL && (c->fn != name && c->ln !=lastname))
	{
		f = f->next;
		c = f->caract;
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
