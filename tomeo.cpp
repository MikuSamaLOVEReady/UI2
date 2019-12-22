/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for no reason
 *
 * 2811 cw2 November 2019 by twak
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QImageReader>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QLabel>
#include <QScrollArea>
#include <QSlider>
#include "the_player.h"
#include "the_button.h"
#include "PlayerSlider.h"


using namespace std;

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>(); // container list for all the information
    //int a =0;

    QDirIterator it(QString::fromStdString(loc), QDir::Files);

    while (it.hasNext()) { // for all files ����ȫ���ļ� ��������Ƶ�ļ� ��ֱ�Ӳ����Ƿ�������Ӧ�� ����ͼ���ҵ������̴����ɰ�ť��Ϣ����list

		QString f = it.next();

        if (!f.contains(".png")) { // if it isn't an image
            QString thumb = f.left( f .length() - 3) +"png";
            if (QFile(thumb).exists()) { // but a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb); // �����ֶ�ȡ ��Ӧ ����ͼ����Ϣ
                    QImage sprite = imageReader->read(); // �Ѷ�ȡ���������� ����ͼƬ
					if (!sprite.isNull()) {  //������ͼƬ �����س����Ļ���
						QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // ��ȡ��ͼƬ��Ϊ�� ��ť��ͼ�ꡣʲôͼ��Ӧʲôʲô����
						QUrl* url = new QUrl(QUrl::fromLocalFile(f)); //���ļ�·��ת����URL convert the file location to a generic url
						out.push_back(TheButtonInfo(url, ico)); // add to the output list
						//++;
						//Ҳ����˵Щ��ť��Ϣ����������ͼ ����ת��ĵ�λ�� ������Щ��Ϣ���ձ��ŵ� һ��list�� ����
					}
					else
						qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb ;
            }
            else
				qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb;
        }
        //printf("%d",a);

    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
	qDebug() << "Qt version: " << QT_VERSION_STR;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    vector<TheButtonInfo> videos = getInfoIn("/Users/luoruidi/Desktop/cwk2/Resources/2811_videos");

    if (videos.size() == 0) {
		qDebug() << "no videos found";
        exit(-1);
    }

    // the widget that will show the video  ��������
    QVideoWidget *videoWidget = new QVideoWidget;
	//videoWidget -> setBaseSize(600, 300);

	//
    // the QMediaPlayer which controls the playback   �� player�ļ�������ϸ ��Ϣ
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget); //

    //float persentage;
    //persentage = player->position()/player->duration();





    // a row of buttons
    QWidget *buttonWidget = new QWidget();

    // a list of the buttons
    std::vector<TheButton*> buttons;   //������һ�� ָ���͵����飿 ����ȫ�� TheButton���̳���pushbutton �����԰���ť

    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(layout);


    QLabel *lab1 = new QLabel();

   // TheButton::connect(this,SIGNAL(released()),lab1,SLOT(setText(QString*) ) );


    // create the four buttons
    for ( int i = 0; i < 7; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        //button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), lab1, SLOT (setText(TheButtonInfo*)));
        button->setMaximumWidth(210);
        button->setMaximumHeight(140);
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i)); //������ط���֮ǰ��źõ� ��ť��Ϣ��ֵ����ʵ��button
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);



    //scrollarea
   // QLabel* lewy = new QLabel();
    QScrollArea* scroll = new QScrollArea();
   // QWidget* area = new QWidget();
    buttonWidget->setGeometry(0, 0,1500,140);  //���ݵĴ�Сֱ��Ӱ������������
    //buttonWidget->setMaximumHeight(200);
    /*buttonWidget->setMaximumSize(wd,100);*/
    //scroll->setGeometry(0, 0, 100, 1000);
    scroll->setWidget(buttonWidget);
    /*QHBoxLayout* Scrolllayout = new QHBoxLayout();
    Scrolllayout->addWidget(scroll);
    area->setMinimumSize(QSize(wd, 110));
    area->setLayout(Scrolllayout);*/



    // create the main window and layout
    QWidget window;
    QVBoxLayout *top = new QVBoxLayout();
    window.setLayout(top);

    window.setWindowTitle("tomeo");
    PlayerSlider *slider = new PlayerSlider();



    QTimer *SlideTimer = new QTimer(player);
    SlideTimer->setInterval(1000); // 1000ms is one second between ...
    SlideTimer->start();
    //float persentage;
    //persentage = player->position()/player->duration();
    slider->getplayer(player);
    QTimer::connect(SlideTimer, SIGNAL(timeout()), slider, SLOT(onTimerOut()));



    //PlayerSlider::connect(slider,SIGNAL(sliderPressed()),player,SLOT(slider_clicked()));
    //slider ������ʱ ����� Ȼ��



    // add the video and the buttons to the top level widget
	top->addWidget(videoWidget);
    top->addWidget(slider);
    top->addWidget(scroll);
    top->setStretchFactor(videoWidget, 3);
    //top->setStretchFactor(scroll);

	window.setMinimumSize(800, 680);
	window.setGeometry(40, 40, 800, 680);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
