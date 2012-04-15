/*
 * 	VisueelScherm.cpp
 *  Gemaakt door Robbert van der Hulst, S1063848
 *
 */

#include "VisueelScherm.hpp"

VisueelScherm::VisueelScherm( WeerData* weerData )
{
	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = new MAUI::Font(RES_FONT);
	skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//Grootte scherm
	screenSize = maGetScrSize();
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = new Label(0,0,0,0,NULL);
	achtergrond->setBackgroundColor(0x000000);

	//knop om data te updaten
	this->updateKnop = new Label ( screenWidth/2-50, 250, 80, 30, achtergrond, "Update", 0, font );
	this->updateKnop->setSkin( this->skin );
	this->updateKnop->setPaddingLeft(5);
	this->updateKnop->setPaddingTop(5);

	//knop om naar visueel scherm te schakelen
	this->textueelKnop = new Label ( screenWidth/2-50, 285, 80, 30, achtergrond, "Textueel", 0, font );
	this->textueelKnop->setSkin( this->skin );
	this->textueelKnop->setPaddingLeft(5);
	this->textueelKnop->setPaddingTop(5);

	//staafdiagram
	//maak eerst een placeholder
	this->diagramTekening = maCreatePlaceholder();

	//laat de placeholder tekenbaar zijn
	maCreateDrawableImage( this->diagramTekening, EXTENT_X( maGetScrSize()-10 ), EXTENT_Y( screenHeight/2+60 ));

	//maak een nieuwe image met de placeholder
	this->diagramImage = new Image( 5, 5, EXTENT_X( maGetScrSize()-10 ), EXTENT_Y( screenHeight/2+60 ) , achtergrond, true, true, this->diagramTekening );

	this->setMain( achtergrond );
}


VisueelScherm::~VisueelScherm()
{
}


void VisueelScherm::update()
{
	//update waarden vam weerdata
	this->weerData->update();

	//stel draw target in op onze tekening
	maSetDrawTarget( this->diagramTekening );

	//teken een staaf diagram
	//vandaag:
	int i = weerData->zonneschijn[0];
	char zonvandaag [25];
	itoa (i, zonvandaag, 10);

	int i2 = weerData->neerslag[0];
	char neerslagvandaag [25];
	itoa (i2, neerslagvandaag, 10);

	int i3 = weerData->minimumtemperatuur[0];
	char minvandaag [25];
	itoa (i3, minvandaag, 10);

	//morgen:
	int i4 = weerData->zonneschijn[1];
	char zonmorgen [25];
	itoa (i4, zonmorgen, 10);

	int i5 = weerData->neerslag[1];
	char neerslagmorgen [25];
	itoa (i5, neerslagmorgen, 10);

	int i6 = weerData->minimumtemperatuur[1];
	char minmorgen [25];
	itoa (i6, minmorgen, 10);

	//overmorgen:
	int i7 = weerData->zonneschijn[2];
	char zonovermorgen [25];
	itoa (i7, zonovermorgen, 10);

	int i8 = weerData->neerslag[2];
	char neerslagovermorgen [25];
	itoa (i8, neerslagovermorgen, 10);

	int i9 = weerData->minimumtemperatuur[2];
	char minovermorgen [25];
	itoa (i9, minovermorgen, 10);

	//legenda
	maSetColor(0xffffff);
	maDrawText(5,10,"Legenda:");
	maSetColor(0xFFFF00);
	maDrawText(10,35,"Zonneschijn %");
	maSetColor(0x6078f4);
	maDrawText(10,50,"Neerslag %");
	maSetColor(0xFF0000);
	maDrawText(10,65,"Minimum temp.");
	maSetColor(0xffffff);
	maDrawText(10,200,"Vandaag");
	maDrawText(70,200,"Morgen");
	maDrawText(130,200,"Overmorgen");


	//teken staven
	//Vandaag
	maSetColor(0xffffff);
	maDrawText(10, screenHeight/2+40-weerData->zonneschijn[0]-15, zonvandaag);
	maDrawText(30, screenHeight/2+40-weerData->neerslag[0]-15, neerslagvandaag);
	maDrawText(50, screenHeight/2+40-weerData->minimumtemperatuur[0]-15, minvandaag);
	maSetColor(0xFFFF00);
	maFillRect(10, screenHeight/2+40-weerData->zonneschijn[0], 15, weerData->zonneschijn[0]);
	maSetColor(0x6078f4);
    maFillRect(30, screenHeight/2+40-weerData->neerslag[0], 15, weerData->neerslag[0]);
	maSetColor(0xFF0000);
	maFillRect(50, screenHeight/2+40-weerData->minimumtemperatuur[0],15,weerData->minimumtemperatuur[0]);

	//Morgen
	maSetColor(0xffffff);
	maDrawText(70, screenHeight/2+40-weerData->zonneschijn[1]-15, zonmorgen);
	maDrawText(90, screenHeight/2+40-weerData->neerslag[1]-15, neerslagmorgen);
	maDrawText(110, screenHeight/2+40-weerData->minimumtemperatuur[1]-15, minmorgen);
	maSetColor(0xFFFF00);
	maFillRect(70, screenHeight/2+40-weerData->zonneschijn[1], 15, weerData->zonneschijn[1]);
	maSetColor(0x6078f4);
    maFillRect(90, screenHeight/2+40-weerData->neerslag[1], 15, weerData->neerslag[1]);
	maSetColor(0xFF0000);
	maFillRect(110, screenHeight/2+40-weerData->minimumtemperatuur[1],15,weerData->minimumtemperatuur[1]);

	//Overmorgen
	maSetColor(0xffffff);
	maDrawText(130, screenHeight/2+40-weerData->zonneschijn[2]-15, zonovermorgen);
	maDrawText(150, screenHeight/2+40-weerData->neerslag[2]-15, neerslagovermorgen);
	maDrawText(170, screenHeight/2+40-weerData->minimumtemperatuur[2]-15, minovermorgen);
	maSetColor(0xFFFF00);
	maFillRect(130, screenHeight/2+40-weerData->zonneschijn[2], 15, weerData->zonneschijn[2]);
	maSetColor(0x6078f4);
    maFillRect(150, screenHeight/2+40-weerData->neerslag[2], 15, weerData->neerslag[2]);
	maSetColor(0xFF0000);
	maFillRect(170, screenHeight/2+40-weerData->minimumtemperatuur[2],15,weerData->minimumtemperatuur[2]);

	//altijd draw target na tekenen teruggeven naar scherm!
	maSetDrawTarget( HANDLE_SCREEN );

	//update de image met de nieuwe tekening
	this->diagramImage->setResource( this->diagramTekening );
}

void VisueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (textueel scherm)
	this->toggleScherm = toggleScherm;
}

void VisueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains( point ) )
	{
		this->updateKnop->setSelected( true );
		this->update();
	}
	else
	{
		this->updateKnop->setSelected( false );
	}


	//textueel knop is ingedrukt
	if( this->textueelKnop->contains( point ) )
	{
		this->textueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->textueelKnop->setSelected( false );
	}
}


