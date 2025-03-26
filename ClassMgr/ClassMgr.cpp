#include "ClassMgr.h"

ClassMgr::ClassMgr(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowFlags(windowFlags() | Qt::WindowType::FramelessWindowHint);
    connect(ui.toolButton_0, SIGNAL(clicked(bool)), this, SLOT(startRecord()));
    connect(ui.toolButton_1, SIGNAL(clicked(bool)), this, SLOT(stopRecord()));

    QScreen* widget = QApplication::primaryScreen();
    QRect scr_size = widget->availableGeometry();
    this->setFixedSize(size().width(), scr_size.height());
    this->move(scr_size.width() - this->width(), scr_size.height()-this->height());
    setWindowOpacity(0.7);

    ui.timeCase_1->append("99 Days");
    ui.timeCase_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
    ui.timeCase_2->append("99 Days");
    ui.timeCase_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

    isRecording = false;
    au_in = nullptr;
    au_save_default = temp_directory_path() / "recdata";
    qDebug() << au_save_default.c_str();
}

ClassMgr::~ClassMgr()
{}

void ClassMgr::enterEvent(QEnterEvent* event)
{
    setWindowOpacity(1);
}

void ClassMgr::leaveEvent(QEvent* event)
{
    setWindowOpacity(0.7);
}

void ClassMgr::startRecord()
{
    if (!isRecording) {
        au_form.setSampleRate(44100);
        au_form.setChannelCount(1);
        au_form.setSampleFormat(QAudioFormat::Int16);
        if (!exists(au_save_default)) {
            create_directories(au_save_default);
        }
        path save_path = au_save_default / (to_string(clock()) + ".pcm");
        for (int i = 0;; i++) {
            if (!exists(save_path)) {
                break;
            }
            save_path = au_save_default / (to_string(clock()) + to_string(i) + ".pcm");
        }
        AudioFile* au_file = new AudioFile(au_form);
        task_list.push_back(au_file->start(save_path));
        au_in = new QAudioSource(QMediaDevices::defaultAudioInput(), au_form);
        au_in->start(au_file);
        isRecording = true;
        qDebug() << "Recing";
    }
}

void ClassMgr::stopRecord()
{
    if (isRecording) {
        au_in->stop();
        isRecording = false;
        qDebug() << "Reced";
    }
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

