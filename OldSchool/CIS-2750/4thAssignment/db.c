#include "/usr/local/mysql/include/mysql.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUERY 512
#define HOSTNAME "localhost"
#define USERNAME "root"
#define PASSWORD "sys"
#define DATABASE "CIS2750"

void startup(MYSQL* mysql);
void clrstr(char *buf);
void clear(MYSQL* mysql);
void reset(MYSQL* mysql);
void posts(MYSQL* mysql);
void users(MYSQL* mysql);
int streams(MYSQL* mysql);
void newTables(MYSQL* mysql);
void insertElement(MYSQL* mysql, char* insertQuery);
int selectElement(MYSQL* mysql, char* selectQuery);

int main(int argc, char *argv[]) {
    MYSQL mysql;
    int i = 0;

    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");

    if (mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
       printf("Could not connect to host: %s\n",mysql_error(&mysql));
   	   exit(1);
    }

    for (i = 1; i < argc; i++) {
        if (strcmp("-clear",argv[i]) == 0 || strcmp("-c",argv[i]) == 0) {
            clear(&mysql);
        } else if (strcmp("-reset",argv[i]) == 0 || strcmp("-r",argv[i]) == 0) {
            reset(&mysql);
        } else if (strcmp("-posts",argv[i]) == 0 || strcmp("-p",argv[i]) == 0) {
            posts(&mysql);
        } else if (strcmp("-users",argv[i]) == 0 || strcmp("-u",argv[i]) == 0) {
            users(&mysql);
        } else if (strcmp("-streams",argv[i]) == 0 || strcmp("-s",argv[i]) == 0) {
            return streams(&mysql);
        } else if (strcmp("-new",argv[i]) == 0 || strcmp("-n",argv[i]) == 0) {
            newTables(&mysql);
        } else if (strcmp("-insert",argv[i]) == 0 || strcmp("-i",argv[i]) == 0) {
            insertElement(&mysql,argv[++i]);
        } else if (strcmp("-fill",argv[i]) == 0 || strcmp("-f",argv[i]) == 0) {
            insertElement(&mysql,NULL);
        } else if (strcmp("-select",argv[i]) == 0 || strcmp("-g",argv[i]) == 0) {
            return selectElement(&mysql,argv[++i]);
        } else if (strcmp("-help",argv[i]) == 0 || strcmp("-h",argv[i]) == 0) {
            printf( "\n\t-clear or -c\t\tthe program removes all of the posts,\n"
                    "\t\t\t\tusers, streams and any other information\n"
                    "\t\t\t\tfrom the tables in the database.\n"
                    "\t\n"
                    "\t-reset or -r\t\tflag the program deletes the tables\n"
                    "\t\t\t\tfrom the database.\n"
                    "\t\n"
                    "\t-posts or -p\t\tflag the program prints out all posts\n"
                    "\t\t\t\tstored in the database.\n"
                    "\t\n"
                    "\t-users or -u\t\tflag the program prints out all user\n"
                    "\t\t\t\tnames stored in the database.\n"
                    "\t\n"
                    "\t-streams or -s\t\tflag the program prints out all stream\n"
                    "\t\t\t\tnames stored in the database.\n"
                    "\t\n"
                    "\t-new or -n\t\tflag the program creates all needed tables\n"
                    "\t\t\t\tin the database.\n"
                    "\t\n"
                    "\t-help or -h\t\tflag it prints out a usage message.\n\n");
        } else {
            printf("An Unknown Command Was Entered\n");
        }
    }

    mysql_close(&mysql);
    return 0;
}

void clear(MYSQL* mysql) {

    if(mysql_query(mysql, "truncate table streams")){
        printf("Could not truncate table: %s\n",mysql_error(mysql));
        exit(1);
  	}

    if(mysql_query(mysql, "truncate table posts")){
        printf("Could not truncate table: %s\n",mysql_error(mysql));
        exit(1);
  	}

    if(mysql_query(mysql, "truncate table stats")){
        printf("Could not truncate table: %s\n",mysql_error(mysql));
        exit(1);
    }

}

void reset(MYSQL* mysql) {

    if(mysql_query(mysql,"drop table streams")){
        printf("Failed to drop: %s\n",mysql_error(mysql));
        exit(1);
    }

    if(mysql_query(mysql,"drop table posts")){
        printf("Failed to drop: %s\n",mysql_error(mysql));
        exit(1);
    }

    if(mysql_query(mysql,"drop table stats")){
        printf("Failed to drop: %s\n",mysql_error(mysql));
        exit(1);
    }

}

void posts(MYSQL* mysql) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i;

    if(mysql_query(mysql, "select post from posts")){
        printf("Failed to select posts from Database: %s\n",mysql_error(mysql));
        exit(1);
	}

    if (!(res = mysql_store_result(mysql))){
        printf("Failed to store the results: %s\n",mysql_error(mysql));
        exit(1);
	}

    while ((row = mysql_fetch_row(res))) {
        for (i=0; i < mysql_num_fields(res); i++){
            printf("%s ", row[i]);
        }
        printf("\n");
    }
}

void users(MYSQL* mysql) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i;

    if(mysql_query(mysql, "select distinct username from streams")){
        printf("Failed to select distinct streams from Database: %s\n",mysql_error(mysql));
        exit(1);
	}

    if (!(res = mysql_store_result(mysql))){
        printf("Failed to store the results: %s\n",mysql_error(mysql));
        exit(1);
	}

    while ((row = mysql_fetch_row(res))) {
        for (i=0; i < mysql_num_fields(res); i++){
            printf("%s ", row[i]);
        }
        printf("\n");
    }
}

int streams(MYSQL* mysql) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i = 0;

    if(mysql_query(mysql, "select distinct streamName from streams")){
        printf("Failed to select streams from Database: %s\n",mysql_error(mysql));
        exit(1);
	}

    if (!(res = mysql_store_result(mysql))){
        printf("Failed to store the results: %s\n",mysql_error(mysql));
        exit(1);
	}

    while ((row = mysql_fetch_row(res))) {
        for (i=0; i < mysql_num_fields(res); i++){
            printf("%s ", row[i]);
        }
        printf("\n");
    }

    return i;
}

void newTables(MYSQL* mysql) {

    if(mysql_query(mysql, "create table if not exists streams (id varchar(2500) binary not null, streamName varchar(2500), username varchar(2500), lastRead int, primary key(id))")){
        printf("Could not create table: %s\n",mysql_error(mysql));
        exit(1);
  	}

    if(mysql_query(mysql, "create table if not exists posts (id varchar(2500) binary, streamName varchar(2500),username varchar(2500),postTime datetime, post varchar(2500), primary key(id))")){
        printf("Could not create table: %s\n",mysql_error(mysql));
        exit(1);
  	}

    if (mysql_query(mysql, "create table if not exists stats (id int not null auto_increment,streams varchar(1000) binary,numposts int,primary key(id),UNIQUE KEY streams (streams(250)))")){
        printf("Could not create table: %s\n",mysql_error(mysql));
        exit(1);
    }

}

void insertElement(MYSQL* mysql, char* insertQuery){
    if (insertQuery != NULL) {
        if(mysql_query(mysql, insertQuery)){
            printf("Failure to insert: %s : %s \n",insertQuery,mysql_error(mysql));
        }
    } else {
        if(mysql_query(mysql, "insert into streams values ('catsIan','cats','Ian',0)")){
            printf("Failure to insert: insert into streams values: %s \n",mysql_error(mysql));
        }
        if(mysql_query(mysql, "insert into streams values ('dogsIan','dogs','Ian',0)")){
            printf("Failure to insert: insert into streams values: %s \n",mysql_error(mysql));
        }
        if(mysql_query(mysql, "insert into streams values ('catsCarl','cats','Carl',0)")){
            printf("Failure to insert: insert into streams values: %s \n",mysql_error(mysql));
        }

        if(mysql_query(mysql, "insert into posts values ('cats','Ian','2017-03-25 11:43:05','Hello')")){
            printf("Failure to insert: insert into posts values: %s \n",mysql_error(mysql));
        }
        if(mysql_query(mysql, "insert into posts values ('cats','Carl','2017-03-25 12:36:09','Goodbye')")){
            printf("Failure to insert: insert into posts values: %s \n",mysql_error(mysql));
        }
        if(mysql_query(mysql, "insert into posts values ('cats','Ian','2017-03-25 10:19:20','You suck')")){
            printf("Failure to insert: insert into posts values: %s \n",mysql_error(mysql));
        }
    }

}

int selectElement(MYSQL* mysql, char* selectQuery){
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i;

	if(mysql_query(mysql, selectQuery)){
        printf("Failed to select from Database: %s\n",mysql_error(mysql));
        exit(1);
	}

	if (!(res = mysql_store_result(mysql))){
        printf("Failed to store the results: %s\n",mysql_error(mysql));
        exit(1);
	}

	while ((row = mysql_fetch_row(res))) {
		for (i=0; i < mysql_num_fields(res); i++){
			printf("%s\t", row[i]);
		}
		printf("\n");
	}
    return i;
}
