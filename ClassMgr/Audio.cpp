#include "Audio.h"

//AudioTask functions

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

//AudioFile functions

AudioFile::AudioFile(const QAudioFormat& format)
{
    open(QIODevice::WriteOnly);
    file = nullptr;
}

AudioFile::~AudioFile()
{
    stop();
}

AudioTask* AudioFile::start(const path& file_path)
{
    file = new fstream(file_path, ios_base::out | ios_base::trunc);
    if (file == nullptr) {
        throw exception("failed to open file!");
    }
    task = new AudioTask(file_path);
    if (task == nullptr) {
        throw exception("failed to create task!");
        delete file;
    }
    task->status = TaskStatus::Recording;
    return task;
}

void AudioFile::stop()
{
    close();
    if (!file->is_open()) {
        file->close();
    }
    if (file != nullptr) {
        delete file;
    }

}

qint64 AudioFile::readData(char* data, qint64 maxlen)
{
    return 0;
}

qint64 AudioFile::writeData(const char* data, qint64 len)
{
    file->write(data, len);
    return len;
}