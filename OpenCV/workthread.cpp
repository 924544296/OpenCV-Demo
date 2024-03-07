#include "workthread.h"

WorkThread::WorkThread(QObject *parent)
    : QObject{parent}
{

}


WorkThread::~WorkThread()
{
    cap.release();
}


void WorkThread::read_image()
{
    if (flag_start)
    {
//        cv::Mat image, image1;
        cap >> image;//    cap.read(frame);
        if (image.empty())
        {
            return;
        }
        cv::resize(image, image, cv::Size(400,400));
        cvtColor(image, image, cv::COLOR_BGR2RGB);
        // 人脸检测
//        cvtColor(image, image1, cv::COLOR_RGB2GRAY);
//        std::vector<cv::Rect> faces;
//        face_cascade.detectMultiScale(image1, faces);
//        for (int i = 0; i < faces.size(); i++)
//        {
//            cv::rectangle(image, cv::Point(faces[i].x,faces[i].y), cv::Point(faces[i].x+faces[i].width,faces[i].y+faces[i].height), cv::Scalar(255,0,0), 3);
//        }
        //
        qimage = QImage((const unsigned char*)(image.data), image.cols, image.rows, int(image.step), QImage::Format_RGB888);
//        qDebug() << "ok";
        emit done_read_image1(qimage);
        if (flag_send)
        {
            emit done_read_image2(qimage);
            flag_send = false;
        }
    }
}


void WorkThread::set_flag_start(bool flag)
{
    flag_start = flag;
}


bool WorkThread::get_flag_start()
{
    return flag_start;
}


void WorkThread::set_flag_send(bool flag)
{
    flag_send = flag;
}


void WorkThread::lr2sr()
{
    if (flag_lr2sr)
    {
        // --
        cv::Mat inputBlob = cv::dnn::blobFromImage(image_lr, 1.0/127.5, cv::Size(100, 100), cv::Scalar(127.5, 127.5, 127.5), false, false, CV_32F);
        net.setInput(inputBlob);
        cv::Mat image_sr = net.forward();
        // --
        int c = image_sr.size[1], h = image_sr.size[2], w = image_sr.size[3];
        cv::Mat result = cv::Mat::zeros(cv::Size(w, h), CV_32FC3);
        float* data = image_sr.ptr<float>();
        for (int id_c = 0; id_c < c; id_c++)
        {
            for (int id_h = 0; id_h < h; id_h++)
            {
                for (int id_w = 0; id_w < w; id_w++)
                {
                    result.at<cv::Vec3f>(id_h, id_w)[id_c] = *data++;
                }
            }
        }
        result = result * 127.5 + 127.5;
        result.convertTo(result, CV_8U);
        QImage image_sr_q = QImage((const unsigned char*)(result.data), result.cols, result.rows, int(result.step), QImage::Format_RGB888);
        // --
        flag_lr2sr = false;
        emit done_lr2sr(image_sr_q);
    }
}


void WorkThread::set_variable(cv::Mat image_lr_, cv::dnn::Net net_, bool flag_lr2sr_)
{
    image_lr = image_lr_;
    net = net_;
    flag_lr2sr = flag_lr2sr_;
}


void WorkThread::open_camera()
{
    cap.open(0);
    face_cascade.load("E:\\opencv470\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_default.xml");
}


void WorkThread::open_video(QString name, double* pframeCount, double* pfps)
{
    cap.open(name.toStdString());
    face_cascade.load("E:\\opencv470\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_default.xml");
//    *pframeCount = cap.get(cv::CAP_PROP_FRAME_COUNT);
    *pfps = cap.get(cv::CAP_PROP_FPS);
}
