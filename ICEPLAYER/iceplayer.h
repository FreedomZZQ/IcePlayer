#ifndef ICEPLAYER_H
#define ICEPLAYER_H

//���ֹ����ٶ�
#define TEXT_SPEED 500

//��ȫ�����ڴ�
#ifndef ICE_SAFE_RELEASE
#define ICE_SAFE_RELEASE(p) if(p) { delete p; p = NULL;}
#endif //ICE_SAFE_RELEASE

#include <QString>
#include <QVector>
#include <QMap>

#include <QtWidgets>
//#include <qwidgetresizehandler_p.h>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <QWindow>

#include "icelrc.h"
#include "iceButton.h"
#include "aboutform.h"
#include "icevolbutton.h"
#include "icelabel.h"
#include "nofocusdelegate.h"
#include "network.h"
#include "songinfo.h"
#include <QJsonDocument>
#include <QTextCodec>
#include <QFileInfo>
#include "movablewindow.h"
//ö�ٲ���ģʽ
enum ICE_Play_Mode{SINGAL, LISTCIRCLE, SINGALCIRCLE, RANDOM};

//����������Ϣ��ר��ͼƬ�����ʻ�ȡ״̬
enum { RECEIVE_INFO, RECEIVE_LINK, RECEIVE_PIC, RECEIVE_LRC };

class miniwindow;
class IcePlayer : public movableWindow
{
    friend class miniwindow;

    Q_OBJECT

public:
    explicit IcePlayer(movableWindow *parent = 0);
    ~IcePlayer();
    void ICE_Open_Music(const QString& filePath);

public slots:
    //��mini���ڷ���������
    void ICE_goback_to_main();

    //����mini���ڴ����Ĳ������ò���ģʽ
    void ICE_set_mode_from_mini(int mode);

    //����mini���ڴ����Ĳ�����������
    void ICE_set_vol_from_mini(int val);

private slots:
    void showMinimized();
    //����Ŀ¼�ṹ
    void ice_open_dir();

    //����mp3��ʽ���ļ�
    void ice_open_music();

    //ɾ��ָ���еĸ���
    void ice_remove_current_music();

    //���ղ����б�
    void ice_clear_list();

    //�����Ҽ��˵�
    void ice_playlisttable_menu_requested(const QPoint &pos);

    //˫�����Ÿ���
    void ice_playlisttable_cell_double_clicked(int row, int);

    //����������Ϣ
    void ice_update_meta_data();

    //���½�����
    void ice_update_duration(qint64 duration);

    //���²���״̬
    void ice_update_state(QMediaPlayer::State state);

    //���²��Ž���
    void ice_set_position(/*int position*/);

    //���¸��ʡ�ʱ����ʾ
    void ice_update_position(qint64 position);

    //���ø���ť�ĵ����¼�����������ť
    void ice_play_button_clicked();
    void ice_lyric_button_clicked();
    void ice_logo_button_clicked();
    void ice_mode_button_clicked();
    void ice_pause_button_clicked();
    void ice_min_button_clicked();
    void ice_next_button_clicked();
    void ice_last_button_clicked();
    //���ò���ģʽ
    void ice_set_play_mode();

    //����LRC����
    bool ice_resolve_lrc(const QString &source_file_name);

    //��������ʱ��ȡ�����б��ļ�
    void ice_read_list();

    //�����ر�ʱ���˺�����ʱ���ã�
    void ice_close();

    //�����в����б�д���б��ļ�
    void ice_write_list();

    //���õ�ǰ����λ��
    void ice_set_play_position(int pos);

    //��ȡ��ǰ����λ��
    int ice_get_play_position();


private:

    //��ʼ��������
    void ice_init_ui();

    //��ʼ������ģ��
    void ice_init_player();

    //��ʼ���ź�-������
    void ice_init_connections();

    //��ʼ������
    void ice_init_windows();

    //��ʼ���˵���
    void ice_init_menu_actions();

    //���ӵ������б�
    void ice_add_list(QStringList list);

    //���ƴ���
    void paintEvent(QPaintEvent *event);

    //��ק����
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    //����tablewidget����
    void ice_color_table();

    //��ʼ������ģ��
    void ice_init_network();

    //��ȡ��������
    void ice_fetch_data();

    //����ר��ͼƬ
    void ice_rece_pic(QNetworkReply *reply);

    //���ո�����Ϣ
    void ice_rece_info(QNetworkReply *reply);

    //������������
    void ice_rece_lrc(QNetworkReply *reply);

    //���ո��ʵ�ַ
    void ice_rece_link(QNetworkReply *reply);

    //�Ӵ����ж�ȡר��ͼƬ
    bool ice_get_pic_from_file();


    ICE_Lrc *iceLrc;
    QMap<qint64, QString> lrcMap;

    QStringList playList;
    QString playingFile;
    QString iceDir;

    int preIndex;
    int currentIndex;
    int playMode;

    ICE_Ice_Button *minButton;
    ICE_Ice_Button *exitButton;
    ICE_Ice_Button *addButton;
    ICE_Ice_Button *lyricButton;
    ICE_Ice_Button *lastButton;
    ICE_Ice_Button *nextButton;
    ICE_Ice_Button *playButton;
    ICE_Ice_Button *pauseButton;
    ICE_Ice_Button *modeButton;
    ICE_Ice_Button *mminButton;
    ICE_Ice_Button *logoButton;

    IceLabel *nameLabel;
    QLabel *musicianLabel;
    QLabel *albumLabel;
    QLabel *timeLabel;
    QLabel *picLabel;

    QSlider *playSlider;
    QSlider *volSlider;

    QTableWidget *playlistTable;

    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaList;

    QMenu *contextMenuLess;
    QMenu *contextMenuMore;
    QMenu *playModeMenu;

    QActionGroup *modeActionGroup;

    //enum ICE_Play_Mode{SINGAL, LISTCIRCLE, SINGALCIRCLE, RANDOM};
    QAction *modeSingal;
    QAction *modeListCircle;
    QAction *modeSingalCircle;
    QAction *modeRandom;
    QAction *addMusic;
    QAction *addFileDiv;
    QAction *removeCurr;
    QAction *removeAll;

    ICE_Vol_Button *volButton;

    ICE_About_Form *aboutForm;
    miniwindow *miniForm;
    NetWorker *networker;
    QString songName;
    QString songArtist;
    QString songId;
    QString picUrl;
    QString lrcUrl;
    int receiveState;

    int playPosition;
};

#endif
