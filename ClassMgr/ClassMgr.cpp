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
        string file_extension = ".pcm";
        au_form.setSampleRate(44100);
        au_form.setChannelCount(2);
        au_form.setSampleFormat(QAudioFormat::Int16);

        qDebug() << au_form.bytesPerFrame();

        if (!exists(au_save_default)) {
            create_directories(au_save_default);
        }
        path save_path = au_save_default / (to_string(time(nullptr)) + file_extension);
        for (int i = 0;; i++) {
            if (!exists(save_path)) {
                break;
            }
            save_path = au_save_default / (to_string(time(nullptr)) + to_string(i) + file_extension);
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



