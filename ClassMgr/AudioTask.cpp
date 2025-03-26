#include "AudioTask.h"

AudioTask::AudioTask(path file_path)
{
	if (!exists(file_path)) {
		throw exception("no such file");
	}
	else if (!is_regular_file(file_path)) {
		throw exception("cannot use directory");
	}
	file = file_path;
}

AudioTask::~AudioTask()
{
	remove(file);
}
