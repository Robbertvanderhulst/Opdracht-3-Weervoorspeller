/*
 * 	VisueelScherm.hpp
 *  Gemaakt door Robbert van der Hulst, S1063848
 *
 */

#ifndef VISUEELSCHERM_HPP_
#define VISUEELSCHERM_HPP_


#include <MAUI/Screen.h>
#include <MAUI/ListBox.h>
#include <MAUI/Label.h>
#include <MAUI/Image.h>

#include <conprint.h>

#include "WeerData.hpp"


using namespace MAUI;


class VisueelScherm : public Screen
{
private:

	//skin, font
	WidgetSkin* skin;
	Font* font;

	//scherm waar we naartoe toggelen bij indrukken visueelknop
	Screen* toggleScherm;

	//standaard knoppenset bovenaan
	ListBox* listBox;
	Label* updateKnop;
	Label* textueelKnop;

	//data van weer
	WeerData* weerData;

	//diagram tekening attributen
	MAHandle diagramTekening;
	Image* diagramImage;

	//scherm grootte
	MAExtent screenSize;
	int screenWidth;
	int screenHeight;


public:
	VisueelScherm( WeerData* weerData );
	virtual ~VisueelScherm();

	void update();
	void setToggleScherm( Screen* toggleScherm );

	void pointerPressEvent( MAPoint2d p );
};

#endif /* VISUEELSCHERM_H_ */
