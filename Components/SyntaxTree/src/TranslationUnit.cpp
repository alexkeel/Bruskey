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

pthread_mutex_t count_mutex; 

bool blobDetected()
{
    pthread_mutex_lock(&count_mutex);
    blob = ptdat->blob;
    pthread_mutex_unlock(&count_mutex);

    blobSufficient = (blob.size > 20);  
}

void *worker(void *p_thread_dat)
{
    struct thread_dat *ptdat = (struct thread_dat *) p_thread_dat;
    const char blobColor[3] = { 255, 51, 51 };  // color to be detected as blob
    TBlobSearch blob;	// blob object from camera

    TBlobSearch tempData;

    while (ptdat->bExit == 0) {
        blob = cameraSearchBlob( blobColor ); // search for sign with RED colored blob
        
        tempData = cameraSearchBlob(blobColor);

        pthread_mutex_lock(&count_mutex);

        ptdat->blob = tempData.blob;
        ptdat->blobnr++;

        pthread_mutex_unlock(&count_mutex);
    } // while

    return NULL;
}

void camcar(int argc, char *argv[], struct thread_dat *ptdat) 
{
    int obstacle_L, obstacle_R, obstacle; 
    int blobSufficient; 
    int carBlobAligned; 
    int distance;
    int speed = 50;

)";
    for(int x = 0; x < this->statementList.size(); x++)
    {
        code += this->statementList.at(x)->toCode();
    }   
    this->code += R"(
}

int main (int argc, char *argv[])
{
    WINDOW *mainwin = initscr();  // curses: init screen
    noecho ();                    // curses: prevent the key being echoed
    cbreak();                     // curses: disable line buffering 
    nodelay(mainwin, TRUE);       // curses: set getch() as non-blocking 
    keypad (mainwin, TRUE);       // curses: enable detection of cursor and other keys

    initio_Init (); // initio: init the library

    pthread_t cam_thread;         // pthread: thread handle
    pthread_attr_t pt_attr;       // pthread: thread attributes
    struct thread_dat tdat;       // data structure to communicate with thread
    tdat.blobnr = 0;
    tdat.bExit = 0;
    pthread_attr_init(&pt_attr);  // pthread: create and init thread attribute

    // Initialise mutex
    if(pthread_mutex_init(&count_mutex, NULL) != 0)
    {
        printf(\"\n Mutex initialization failed\n\");
        return NULL;
    }

    // Listener loop started on seperate thread
    pthread_create(&cam_thread, NULL, worker, &tdat);

    camcar(argc, argv, &tdat);    // start control loop in main thread

    tdat.bExit = 1;               // signal thread to terminate

    pthread_join(&cam_thread, NULL);

    pthread_attr_destroy(&pt_attr);
    pthread_mutex_destroy(&count_mutex);

    initio_Cleanup ();  // initio: cleanup the library (reset robot car)
    endwin();           // curses: cleanup the library
    return EXIT_SUCCESS;
})";

}

std::string TranslationUnit::toCode() const
{
    return this->code;
}