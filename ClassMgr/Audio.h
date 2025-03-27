#pragma once
#include <filesystem>
#include <fstream>
#include <QIODevice>
#include <QtMultimedia/QMediaDevices>
#include <QtMultimedia/QAudioSource>
#include <QtMultimedia/QAudioDevice>
#include <include/libavcodec/avcodec.h>
#include <include/libavformat/avformat.h>
#include <include/libavutil/avutil.h>
#include <include/libavutil/opt.h>
#include <include/libswresample/swresample.h>
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

class AudioFile :public QIODevice
{
    Q_OBJECT

public:
    AudioFile(const QAudioFormat& format);
    ~AudioFile();
    AudioTask* start(const path&);
    void stop();
    qint64 readData(char* data, qint64 maxlen) override;
    qint64 writeData(const char* data, qint64 len) override;

private:
    AudioTask* task;
    const QAudioFormat m_format;
    fstream* file;
};
