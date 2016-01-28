#ifndef ICEPLAYER_H
#define ICEPLAYER_H

//文字滚动速度
#define TEXT_SPEED 500 

//安全回收内存
#ifndef ICE_SAFE_RELEASE
#define ICE_SAFE_RELEASE(p) if(p) { delete p; p = NULL;}
#endif //ICE_SAFE_RELEASE

#include <QString>
#include <QVector>
#include <QMap>

#include <QtWidgets>
#include <qwidgetresizehandler_p.h>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QMediaPlayer>

#include "icelrc.h"
#include "iceButton.h"
#include "aboutform.h"
#include "icevolbutton.h"
#include "mini.h"
#include "icelabel.h"
#include "nofocusdelegate.h"

#include "network.h"
#include "songinfo.h"
#include <QJsonDocument>
#include <QTextCodec>
#include <QFileInfo>

//枚举播放模式
enum ICE_Play_Mode{SINGAL, LISTCIRCLE, SINGALCIRCLE, RANDOM};

//网络音乐信息，专辑图片，歌词获取状态
enum { RECEIVE_INFO, RECEIVE_LINK, RECEIVE_PIC, RECEIVE_LRC };

class IcePlayer : public QWidget
{
	//设置mini窗口类为主窗口类的友元类，从而可以调用主窗口类的私有函数和私有对象
	friend class miniwindow;

	Q_OBJECT

public:
	explicit IcePlayer(QWidget *parent = 0); 
	~IcePlayer();
	void ICE_Open_Music(const QString& filePath);

public slots:
	//从mini窗口返回主窗口 
	void ICE_goback_to_main(); 

	//接受mini窗口传来的参数设置播放模式
	void ICE_set_mode_from_mini(int mode); 

	//接受mini窗口传来的参数设置音量
	void ICE_set_vol_from_mini(int val); 
	
private slots:

	//访问目录结构 
	void ice_open_dir();	

	//添加mp3格式的文件 
	void ice_open_music();	

	//删除指定行的歌曲
	void ice_remove_current_music(); 

	//清空播放列表
	void ice_clear_list();  

	//请求右键菜单
	void ice_playlisttable_menu_requested(const QPoint &pos);  

	//双击播放歌曲 
	void ice_playlisttable_cell_double_clicked(int row, int); 

	//更新音乐信息 
	void ice_update_meta_data(); 

	//更新进度条 
	void ice_update_duration(qint64 duration);

	//更新播放状态 
	void ice_update_state(QMediaPlayer::State state); 

	//更新播放进度 
	void ice_set_position(/*int position*/); 

	//更新歌词、时间显示 
	void ice_update_position(qint64 position);

	//设置各按钮的单击事件，激活各按钮
	void ice_play_button_clicked(); 
	void ice_lyric_button_clicked(); 
	void ice_logo_button_clicked(); 
	void ice_mode_button_clicked(); 
	void ice_pause_button_clicked(); 
	void ice_min_button_clicked();
	void ice_next_button_clicked();
	void ice_last_button_clicked();

	//设置播放模式
	void ice_set_play_mode();

	//解析LRC歌词 
	bool ice_resolve_lrc(const QString &source_file_name);

	//程序打开时读取播放列表文件 
	void ice_read_list();

	//程序关闭时（此函数暂时无用）
	void ice_close();
	
	//把现有播放列表写入列表文件 
	void ice_write_list();

	//设置当前播放位置
	void ice_set_play_position(int pos);

	//获取当前播放位置
	int ice_get_play_position();


private:

	//初始化主界面 
	void ice_init_ui();	

	//初始化播放模块 
	void ice_init_player();	

	//初始化信号-槽连接 
	void ice_init_connections();	

	//初始化窗口 
	void ice_init_windows();

	//初始化菜单项
	void ice_init_menu_actions(); 

	//添加到播放列表 
	void ice_add_list(QStringList list);

	//绘制窗体
	void paintEvent(QPaintEvent *event); 

	//拖拽添加
	void dragEnterEvent(QDragEnterEvent *event); 
	void dropEvent(QDropEvent *event); 

	//定制tablewidget外观
	void ice_color_table();

	//初始化网络模块
	void ice_init_network();

	//获取网络数据
	void ice_fetch_data();

	//接收专辑图片
	void ice_rece_pic(QNetworkReply *reply);

	//接收歌曲信息
	void ice_rece_info(QNetworkReply *reply);

	//接收网络歌词
	void ice_rece_lrc(QNetworkReply *reply);

	//接收歌词地址
	void ice_rece_link(QNetworkReply *reply);

	//从磁盘中读取专辑图片
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
	
	miniwindow *miniForm;
	ICE_About_Form *aboutForm;

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
