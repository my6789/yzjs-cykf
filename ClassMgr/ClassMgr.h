#pragma once

#include <QtWidgets/QMainWindow>
#include <QtMultimedia/QScreenCapture>
#include <filesystem>
#include <time.h>
#include <vector>
#include <qDebug>
#include "Audio.h"
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

