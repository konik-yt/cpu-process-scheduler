#pragma once


struct Process {
    // Input 
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;  // Lower number the higher the priority


    int remainingTime;   
    int startTime;       
    int completionTime;  

    Process()
        : pid(0), arrivalTime(0), burstTime(0), priority(0),
          remainingTime(0), startTime(-1), completionTime(-1) {}

    Process(int id, int arrival, int burst, int prio)
        : pid(id), arrivalTime(arrival), burstTime(burst), priority(prio),
          remainingTime(burst), startTime(-1), completionTime(-1) {}

    void reset() {
        remainingTime = burstTime;
        startTime = -1;
        completionTime = -1;
    }

    bool hasStarted() const { return startTime != -1; }
    bool isFinished() const { return remainingTime == 0; }
};
