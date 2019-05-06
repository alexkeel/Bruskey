#include "TranslationUnit.hpp"
#include <iostream>

TranslationUnit::TranslationUnit(StatementList *statementList)
{
    this->statementList = statementList->getStatements();

        this->code += R"(
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

TBlobSearch blob;
struct thread_dat *ptdat;

pthread_mutex_t count_mutex; 

int getBlobHAlignment()
{
    TBlobSearch blob;
    pthread_mutex_lock(&count_mutex);
    blob = ptdat->blob;
    pthread_mutex_unlock(&count_mutex);
    return blob.halign;
}

int blobDetected()
{
    TBlobSearch blob;
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

    while (ptdat->bExit == 0) {
        blob = cameraSearchBlob( blobColor ); 

        pthread_mutex_lock(&count_mutex);

        ptdat->blob = blob;
        ptdat->blobnr++;

        pthread_mutex_unlock(&count_mutex);
    } 

    return NULL;
}

void userDefined(int argc, char *argv[], struct thread_dat *ptdat)
{
)";
    for(int x = 0; x < this->statementList.size(); x++)
    {
        code += this->statementList.at(x)->toCode();
    }   
    this->code += R"(
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
        printf("\n Mutex initialization failed\n");
        return NULL;
    }

    // Listener loop started on seperate thread
    pthread_create(&cam_thread, NULL, worker, &tdat);

    userDefined(argc, argv, &tdat);

    tdat.bExit = 1;               

    pthread_join(&cam_thread, NULL);

    pthread_attr_destroy(&pt_attr);
    pthread_mutex_destroy(&count_mutex);

    initio_Cleanup ();  
    endwin();           
    return EXIT_SUCCESS;
})";

}

std::string TranslationUnit::toCode() const
{
    return this->code;
}
