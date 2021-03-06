





#include <stdlib.h>
#include <initio.h>
#include <curses.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <pthread.h>
#include <assert.h>
#include "detect_blob.h"

#define DIST_MIN 60
#define DIST_MAX 100

struct thread_dat {
    TBlobSearch blob;	
    int blobnr;		
    int bExit; 		
};

int speed;
int obstacle_L, obstacle_R, obstacle; 
int blobSufficient; 
int carBlobAligned; 
int distance;
int speed = 50;

pthread_mutex_t count_mutex; 

int getBlobHAlignment()
{
    pthread_mutex_lock(&count_mutex);
    blob = ptdat->blob;
    pthread_mutex_unlock(&count_mutex);
    return blob.halign;
}

bool blobDetected()
{
    pthread_mutex_lock(&count_mutex);
    blob = ptdat->blob;
    pthread_mutex_unlock(&count_mutex);

    return (blob.size > 20);  
}

void *worker(void *p_thread_dat)
{
    struct thread_dat *ptdat = (struct thread_dat *) p_thread_dat;
    const char blobColor[3] = { 255, 51, 51 };  
    TBlobSearch blob;	

    TBlobSearch tempData;

    while (ptdat->bExit == 0) {
        blob = cameraSearchBlob( blobColor ); 
        
        tempData = cameraSearchBlob(blobColor);

        pthread_mutex_lock(&count_mutex);

        ptdat->blob = tempData.blob;
        ptdat->blobnr++;

        pthread_mutex_unlock(&count_mutex);
    } 

    return NULL;
}

void camcar(int argc, char *argv[], struct thread_dat *ptdat) 
{
while(true)
{if(true)
{initio_DriveReverse(0);
}
}
}

int main (int argc, char *argv[])
{
    WINDOW *mainwin = initscr();  
    noecho ();                    
    cbreak();                     
    nodelay(mainwin, TRUE);       
    keypad (mainwin, TRUE);       

    initio_Init ();

    pthread_t cam_thread;        
    pthread_attr_t pt_attr;       
    struct thread_dat tdat;       
    tdat.blobnr = 0;
    tdat.bExit = 0;
    pthread_attr_init(&pt_attr);  

    if(pthread_mutex_init(&count_mutex, NULL) != 0)
    {
        printf(\"\n Mutex initialization failed\n\");
        return NULL;
    }

    // Listener loop started on seperate thread
    pthread_create(&cam_thread, NULL, worker, &tdat);

    camcar(argc, argv, &tdat);    

    tdat.bExit = 1;               

    pthread_join(&cam_thread, NULL);

    pthread_attr_destroy(&pt_attr);
    pthread_mutex_destroy(&count_mutex);

    initio_Cleanup ();  
    endwin();           
    return EXIT_SUCCESS;
}
