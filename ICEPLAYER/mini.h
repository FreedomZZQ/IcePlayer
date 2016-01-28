#ifndef MINI_H
#define MINI_H

#include <QtWidgets>
#include <qwidgetresizehandler_p.h>
#include "iceButton.h"
#include "iceplayer.h"

class IcePlayer;

class miniwindow : public QWidget{

	Q_OBJECT

public:

	miniwindow(QWidget *parent = 0);
	~miniwindow();

	void ICE_Set_Parent(IcePlayer *parent);
	void ICE_Init_Play_Mode(int vol);

private slots:

	void ice_back_to_main();

	void ice_next_music();

	void ice_last_music();

	void ice_play();

	void ice_pause();

	void ice_set_mode();

	void ice_exit();

	void ice_lyric_action();
	
	void ice_update_vol(int);
private:

	void paintEvent(QPaintEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);

	void ice_init_menu_actions();
	
	ICE_Ice_Button *playButton;
	ICE_Ice_Button *pauseButton;
	ICE_Ice_Button *miniNextButton;

	QMenu *contextMenu;
	QActionGroup *modeGroup;
	
	QAction *mode0;
	QAction *mode1;
	QAction *mode2;
	QAction *mode3;
	QAction *mainForm;
	QAction *exit;
	QAction *next;
	QAction *last;
	QAction *lyric;
	QWidgetAction *setVolumn;
	QSlider *volSlider;

	IcePlayer *parentForm;

};

#endif