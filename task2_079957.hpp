#ifndef TASK2_079957_HPP
#define TASK2_079957_HPP

const int MAX_ROBOTS = 10;
const int MAX_ASSIGNMENTS = 100;
const int MAX_TEXT = 40;

enum RobotStatus {
    AVAILABLE = 0,
    BUSY = 1,
    MAINTENANCE = 2
};

struct Robot {
    int id;
    char name[MAX_TEXT];
    RobotStatus status;
    int taskCount;
};

struct Assignment {
    int assignmentId;
    int robotId;
    char taskName[MAX_TEXT];
};

class RobotAssignmentModule {
private:
    Robot robots[MAX_ROBOTS];
    Assignment assignments[MAX_ASSIGNMENTS];
    int robotCount;
    int assignmentCount;
    int nextRobotIndex;

    const char* statusText(RobotStatus status);
    int findRobotIndexById(int robotId);

public:
    RobotAssignmentModule();
    bool addRobot(int id, const char name[]);
    bool updateStatus(int robotId, RobotStatus status);
    bool loadRobotsFromFile(const char fileName[]);
    bool assignTask(const char taskName[]);
    void completeTask(int robotId);
    void displayRobotStatus();
    void displayAssignments();
};

void runRobotAssignmentMenu();

#endif
