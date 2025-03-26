#pragma once

#include <QtWidgets/QMainWindow>
#include <QtMultimedia/QScreenCapture>
#include <QtMultimedia/QMediaDevices>
#include <QtMultimedia/QAudioSource>
#include <QtMultimedia/QAudioDevice>
#include <QIODevice>
#include <filesystem>
#include <fstream>
#include <time.h>
#include <vector>
#include <qDebug>
#include "AudioTask.h"
#include "ui_ClassMgr.h"
using namespace std::filesystem;
using namespace std;

class ClassMgr : public QMainWindow
{
    Q_OBJECT

public:
    ClassMgr(QWidget *parent = nullptr);
    ~ClassMgr();

protected://Window visual effects
    //Change alpha when mouse entered /exited
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);

private://Audio recording
    bool isRecording;
    QAudioSource* au_in;
    QAudioFormat au_form;
    path au_save_default;
    vector<AudioTask*> task_list;

private slots:
    void startRecord();
    void stopRecord();

private:
    Ui::ClassMgrClass ui;
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
