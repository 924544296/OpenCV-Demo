#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <opencv2/opencv.hpp>


class WorkThread : public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = nullptr);
    // --
    ~WorkThread();
    // 摄像头、视频
    void read_image();
    void set_flag_start(bool flag);
    bool get_flag_start();
    void set_flag_send(bool flag);
    void open_camera();
    void open_video(QString name, double* pframeCount, double* pfps);
    // 超分
    void set_variable(cv::Mat image_lr_, cv::dnn::Net net_, bool flag_lr2sr_);
    void lr2sr();

private:
    // 摄像头、视频
    cv::Mat image;
    QImage qimage;
    cv::VideoCapture cap;
    cv::CascadeClassifier face_cascade;
    bool flag_start=false;
    bool flag_send=false;
    // 超分
    cv::Mat image_lr;
    cv::dnn::Net net;
    bool flag_lr2sr=false;


signals:
    // --
    //
    void done_read_image1(QImage frame);
    void done_read_image2(QImage frame);
    //
    void done_lr2sr(QImage image_sr_q_);

};

#endif // WORKTHREAD_H
