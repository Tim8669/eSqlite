#include <stdio.h>
#include "../eSqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf(" %s-%s\n", azColName[i],argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   Akey_t **tokens;
   char *tokensFile[2] = {"token"};
   
   if(argc!=3){
   	fprintf(stderr,"Usage: select <db> <pairing>\n");
  	return 1;
   }
   sql ="SELECT NAME FROM COMPANY WHERE AGE=32;";
   //open database
   rc = eSqlite3_open(argv[1], &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return 0;
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
   //open token and token2
   //argv[2] pairing filename
   int size=eSqlite3_addToken(argv[2],tokensFile,&tokens,0,1);
   //exec SELECT query
   //eSqlite3_exec doesn't need the master secret key for SELECT query 
   rc = eSqlite3_exec(db,sql,callback,0,&zErrMsg,argv[2],NULL,tokens,size);
   if( rc != SQLITE_OK )
	{
		printf("%s\n",zErrMsg);
	}
   //close database
   eSqlite3_close(db);
}
