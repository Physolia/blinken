/***************************************************************************
 *   Copyright (C) 2005 by Albert Astals Cid <tsdgeos@terra.es>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef ARTSPLAYER_H
#define ARTSPLAYER_H

#include <arts/kartsdispatcher.h>
#include <arts/kartsserver.h>
#include <arts/kplayobject.h>
#include <arts/kplayobjectfactory.h>

#include <qvaluelist.h>

#include "simongame.h"

class QTimer;

class artsPlayer : public QObject
{
Q_OBJECT
	public:
		artsPlayer();
		~artsPlayer();
		
		void play(simonGame::color c, bool stopCurrent = false);
		
	signals:
		void ended();
		
	private slots:
		void play();
		void checkEnded();
		
	private:
		QValueList<simonGame::color> m_nextSounds;
		
		QString m_greenPath, m_redPath, m_bluePath, m_yellowPath;
		
		QTimer *m_endChecker;
		
		KArtsDispatcher *m_dispatcher;
		KArtsServer *m_server;
		KDE::PlayObjectFactory *m_factory;
		KDE::PlayObject *m_playobj;
};

#endif