#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <clogg/clogger.h>

static Clogger_t* logger = NULL;

/**\brief method creats logger. If logger = -1 then the logger could not be allocated
 * If the logfile is NULL then the output runs on the shell
 * If the logfile is set the funtion returns 0
 *
 * \return -1 -> logger object could not be created
 * \return 0 -> logger object rights message to terminal
 * \return 1 -> logger write output into the logfile
*/
int start_logging(const char* logfilename){
	assert(logfilename);

	if (logger == NULL){
		logger =(Clogger_t*) malloc(sizeof(logger));
	}

	pthread_mutex_init((&(logger->lock)), NULL);
	logger->logfile = fopen(logfilename, "a");

	if (logger->logfile == NULL){
		fprintf(stderr,"No Logfile created. The output is written on the shell.\n");
		return 0;
	}

	return 1;
};

void write_logging(const char* message){
  assert(message);

  pthread_mutex_lock((&(logger->lock)));

  if (logger->logfile == NULL){
    printf("Logger: %s \n",message);
  }else{
    fprintf(logger->logfile, "%s\n", message);
  }

  pthread_mutex_unlock(&(logger->lock));
};


void stop_logging(void){

  pthread_mutex_destroy(&(logger->lock));

  if (logger->logfile != NULL){
    fclose(logger->logfile);
  }
  free(logger);
};
