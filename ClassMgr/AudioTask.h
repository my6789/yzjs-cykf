#pragma once
#include <filesystem>
using namespace std;
using namespace std::filesystem;

enum TaskStatus {
	Waiting, Recording, Converting, Completed,
};

class AudioTask {
public:
	TaskStatus status;
	path file;
public:
	AudioTask(path);
	~AudioTask();
};
