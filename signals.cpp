#include <iostream>
#include <signal.h>
#include "signals.h"
#include "Commands.h"

#define WHITESPACE " "
#define NULLJOB -1
#define EMPTYTEXT ""

using namespace std;

void ctrlZHandler(int sig_num) {
    SmallShell& smash=SmallShell::getInstance();
    std::cout<<"smash: got ctrl-Z"<<std::endl;
    smash.smash_jobs_list->removeFinishedJobs();
    if(smash.current_job->jobPID != NULLJOB){
        if(killpg(smash.current_job->jobPID,SIGSTOP)==-1){
            std::perror("smash error: kill faild");
            return;
        }
        smash.smash_jobs_list->stopJob(smash.current_job->jobPID ,smash.current_job->jobID , smash.current_job->commandLine , smash.current_job->start_time );
        std::cout<<"smash: process "<<smash.current_job->jobPID<<" was stopped"<<std::endl;
        smash.current_job->resetJob();
    }
}

void ctrlCHandler(int sig_num) {
    SmallShell &smash = SmallShell::getInstance();
    std::cout << "smash: got ctrl-C" << std::endl;
    smash.smash_jobs_list->removeFinishedJobs();
    if(smash.current_job->jobPID != NULLJOB)
    {
        if(killpg(smash.current_job->jobPID,SIGKILL)==-1){
            std::perror("smash error: kill faild");
            return;
        }
        std::cout<<"smash: process "<<smash.current_job->jobPID<<" was killed"<<std::endl;
        smash.current_job->resetJob();
        smash.smash_jobs_list->removeFinishedJobs();
    }
}

void alarmHandler(int sig_num) {
  // TODO: Add your implementation
}

