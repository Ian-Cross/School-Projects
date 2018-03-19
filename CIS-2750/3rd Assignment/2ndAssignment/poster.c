#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stream.h"


struct PostEntry {
	void (*PostEntryreadInputUs)(UserPost * post, struct PostEntry * newPost) ;
	UserPost * (*PostEntryformatEntryUci)(UserPost * post, char * * data, int lines) ;
	char * (*PostEntrygetTimeDate)() ;
	void (*PostEntrysubmitPostU)(UserPost * post) ;
};

void PostEntryreadInputUs( UserPost * post , struct PostEntry * newPost ){
	FILE * input =fopen ("Post.new" ,"r" );
	if (input ==NULL ){
		printf ("File is Broken\n" );
	}
	char lines[1000][1000] ;
	char * * data ;
	char username[1000] ;
	int j =0 ;
	int i =0 ;
	/* store the data in the first slot in the array */
	strcpy (lines[i] ,newPost -> PostEntrygetTimeDate ());
	i ++;
	fgets (username ,1000 ,input );
	printf ("%s\n" ,username );
	post ->username =malloc (sizeof (char )* (strlen (username )+3));
	strcpy (post ->username ,username );
	post ->username[strlen (post ->username )-1] ='\0' ;
	printf ("%s\n" ,post ->username );
	/* Get the stream name, store in the next slot */
	fgets (lines[i] ,1000 ,input );
	i ++;
	/*get the users post, storing each new line in the array */
	while (fgets (lines[i] ,1000 ,input )!=NULL ){
		i ++;
	}
	/* Create a dynamic array for the post */
	data =(char * * )malloc (sizeof (char * )* i );
	/* give space for each line and move it over in to the dynamic array */
	for (j =0 ;
	j < i ;
	j ++){
		data[j] =(char * )malloc (sizeof (char )* strlen (lines[j] )+1);
		if (data[j] ==NULL ){
			printf ("Sorry, there wasn't enough room\n" );
			exit (1);
		}
		strcpy (data[j] ,lines[j] );
	}
	fclose (input );
	remove ("Post.new" );
	/* format the dynamic array and sotre everything into the post struct */
	post =newPost -> PostEntryformatEntryUci (post ,data ,i -1);
}

UserPost * PostEntryformatEntryUci( UserPost * post , char * * data , int lines ){
	int j =0 ;
	/* allocate space and move the date from the array to the struct */
	post ->date =malloc (sizeof (char )* strlen (data[0] )+1);
	if (post ->date ==NULL ){
		printf ("Im sorry there wasn't enough room\n" );
		exit (1);
	}
	strcpy (post ->date ,data[0] );
	free (data[0] );
	/* allocate space and more the stream name from the array to the struct */
	post ->streamName =malloc (sizeof (char )* strlen (data[1] )+2);
	if (post ->streamName ==NULL ){
		printf ("Im sorry there wasn't enough room\n" );
		exit (1);
	}
	/* Getting rid of the trailing newline */
	if (data[1][strlen (data[1] )-1] =='\n' )data[1][strlen (data[1] )-1] ='\0' ;
	strcpy (post ->streamName ,data[1] );
	free (data[1] );
	/* condense all the post lines in the array down to one continuous line */
	post ->text =malloc (sizeof (char )+2);
	strcpy (post ->text ,"\0" );
	for (j =2;
	j < lines ;
	j ++){
		/* hold onto the data already waiting in the line */
		char * temp =malloc (sizeof (char )* strlen (post ->text )+2);
		if (post ->text ==NULL ){
			printf ("I'm sorry there wasn't enough room\n" );
			exit (1);
		}
		strcpy (temp ,post ->text );
		/* make the line bigger */
		post ->text =realloc (post ->text ,sizeof (char )* (strlen (data[j] )+strlen (temp )+3));
		if (post ->text ==NULL ){
			printf ("I'm sorry there wasn't enough room\n" );
			exit (1);
		}
		/* attach the next line on the back */
		strcpy (post ->text ,temp );
		strcat (post ->text ,"-" );
		strcat (post ->text ,data[j] );
		/* clean up memory */
		free (data[j] );
		free (temp );
	}
	free (data );
	return post ;
}

char * PostEntrygetTimeDate(){
	time_t mytime ;
	/* get the current machine time */
	mytime =time (NULL );
	/* format it nicely and send it back */
	return ctime (&mytime );
}

void PostEntrysubmitPostU( UserPost * post ){
	/* Send off the full struct to be written to a stream */
	updateStream (post );
	/* clean up the memory */
	free (post ->username );
	free (post ->streamName );
	free (post ->text );
	free (post ->date );
	free (post );
}

void conPostEntry( struct PostEntry* myStruct ){
	myStruct-> PostEntryreadInputUs =PostEntryreadInputUs ;
	myStruct-> PostEntryformatEntryUci =PostEntryformatEntryUci ;
	myStruct-> PostEntrygetTimeDate =PostEntrygetTimeDate ;
	myStruct-> PostEntrysubmitPostU =PostEntrysubmitPostU ;
}



int main( int argc , char * argv[] ){
	struct PostEntry newPost ;
	conPostEntry( &newPost );
	UserPost * post =malloc (sizeof (UserPost ));
	/* collect the data */
	newPost .PostEntryreadInputUs (post ,&newPost );
	/* send of the full struct */
	newPost .PostEntrysubmitPostU (post );
	return 0 ;
}

