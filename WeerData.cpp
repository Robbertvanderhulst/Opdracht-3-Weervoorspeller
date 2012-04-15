/*
 * 	WeerData.cpp
 *  Gemaakt door Robbert van der Hulst, S1063848
 *
 */

#include "WeerData.hpp"
#include <conprint.h>


//hulpfunctie
char* zoekWoord(char* buffer, char* testString)
{
	//zoekt de beginpositie van testString als die voorkomt in buffer
	char* myPos = strstr( buffer, testString );

	if(myPos == NULL)
	{
		return NULL;
	}

	else
	{
		//geef de positie terug achter de gevonden string
		return( myPos + strlen(testString) );
	}
}



WeerData::WeerData() : HttpConnection( this )
{
	//stel de isConnecting boolean in op 'in gebruik'
	this->isConnecting = true;

	//maak een nieuwe connectie
	this->url = "http://www.knmi.nl/waarschuwingen_en_verwachtingen/#meerdaagse";
    int res = this->create( url, HTTP_GET );

    //foutafhandeling bij connectie probleem
    if(res < 0)
    {
        lprintfln( "unable to connect - %i\n", res );
    }

    else
    {
    	this->finish();
    }

    //reset de weerdata naar 0
	for( int i = 0; i < 3; i++ )
	{
		this->zonneschijn[i] = 0;
		this->neerslag[i] = 0;
		this->minimumtemperatuur[i] = 0;
	}
}

WeerData::~WeerData()
{

}


void WeerData::update()
{
	//update alleen als er niet momenteel al een update uitgevoerd wordt
	if( this->isConnecting == false )
	{
		//stel de isConnecting boolean in op 'in gebruik'
		this->isConnecting = true;

		//maak een nieuwe connectie
		this->connect( this->url );
	}
}




void WeerData::httpFinished( HttpConnection* http, int result )
{
	//stel de isConnecting boolean in op 'in gebruik'
	this->isConnecting = true;

	//recv() leest maximaal 1024 bytes (staat in CONNECTION_BUFFER_SIZE)
	//als we beginnen met het lezen van 700 bytes, komen we later mooi uit op de dataset die we willen lezen
	this->recv( weerDataRecv, 1000 );
}


void WeerData::connRecvFinished( Connection* conn, int result )
{
	//blijf lezen met 1024 bytes (zie onder) tot result einde van de site heeft bereikt (waarbij result < 0)
    if(result >= 0)
    {
    	//zoek zonneschijn
        char* weerDataString = zoekWoord( weerDataRecv, "<td>Zonneschijn (%)</td>" ); //buffer van totale tekst

        //zonneschijn gevonden
        if( weerDataString )
        {
        	char data[2];

			//zonneschijn data vandaag
			strncpy( data, weerDataString + 33, 2 ); //offset van 33 kom je bij het percentage zonneschijn
        	this->zonneschijn[0] = atoi( data );

        	//morgen
			strncpy( data, weerDataString + 69, 2 );
        	this->zonneschijn[1] = atoi( data );

        	//overmorgen
			strncpy( data, weerDataString + 105, 2 );
        	this->zonneschijn[2] = atoi( data );
        }


        //zoek neerslagkans
        weerDataString = zoekWoord( weerDataRecv, "<td>Neerslagkans (%)</td>" );

        //neerslagkans gevonden
        if( weerDataString )
        {
        	char data[2];

			//neerslag data vandaag
			strncpy( data, weerDataString + 33, 2 );
        	this->neerslag[0] = atoi( data );

        	//morgen
			strncpy( data, weerDataString + 69, 2 );
        	this->neerslag[1] = atoi( data );

        	//overmorgen
			strncpy( data, weerDataString + 105, 2 );
        	this->neerslag[2] = atoi( data );
        }


        //zoek minimum temperatuur
        weerDataString = zoekWoord( weerDataRecv, "<td>Minimumtemperatuur (&deg;C)</td>" );

        //gevonden
        if( weerDataString )
        {
        	char data[2];

        	//min temp data vandaag
			strncpy( data, weerDataString + 32, 1 );
        	this->minimumtemperatuur[0] = atoi( data )/10; //is in formaat 1/3 (1 tot 3 graden), we pakken alleen de 1. deling haalt tweede karakter weg.

        	//morgen
			strncpy( data, weerDataString + 69, 1 );
        	this->minimumtemperatuur[1] = atoi( data )/10;

        	//overmorgen
			strncpy( data, weerDataString + 106, 1 );
        	this->minimumtemperatuur[2] = atoi( data )/10;

        	//we zijn klaar! geen andere data is meer nodig, dus sluit de connectie
        	this->close();
        	return;
        }


        //lees de volgende 1024 bytes, deze functie wordt dan weer opnieuw aangeroepen
        this->recv(weerDataRecv, CONNECTION_BUFFER_SIZE);
    }

    else
    {
    	//fout is opgetreden of we hebben het eind van het document bereikt, sluit af.
    	this->close();
    }
}


void WeerData::connReadFinished( Connection* conn, int result )
{
}


void WeerData::connectFinished(Connection* conn, int result)
{
	//connectie is geeindigd, geef connectie weer vrij met de isConnecting boolean
	this->isConnecting = false;
}


