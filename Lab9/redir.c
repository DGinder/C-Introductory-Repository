#include <unistd.h>
int main ()
{
    int fileId;
    fileId = creat( "x.lis",0640 );
    if( fileId < 0 )  {  
	printf( stderr, "error creating x.lis\n“ ); 
	exit (1);     
    }
    dup2( fileId, stdout ); /* copy fileID to stdout */
    close( fileId );     		
    execl( "/bin/ls", "ls", 0 );
}
