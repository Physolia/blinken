/***************************************************************************
 *   Copyright (C) 2005 by Albert Astals Cid <tsdgeos@terra.es>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef SIMONGAME_H
#define SIMONGAME_H

#include <qvaluelist.h>

class QTimer;

class artsPlayer;

class simonGame : public QObject
{
Q_OBJECT
	public:
		simonGame();
		~simonGame();
		
		enum gamePhase { starting, choosingLevel, waiting3, waiting2, waiting1, learningTheSequence, typingTheSequence };
		enum color { none, red, green, blue, yellow, all };
		
		int level() const;
		gamePhase phase() const;
		
		void clicked(color c);
		void setPhase(gamePhase p);
		void start(int level);
	
	signals:
		void phaseChanged();
		void highlight(simonGame::color c, bool unhighlight);
		
	private slots:
		void nextSound();
		void soundEnded();
		void unhighlight();
		void waiting();
		
	private:
		color generateColor();
	
		gamePhase m_phase;
		int m_level;
		int m_sequenceLength;
		
		QTimer *m_waitTimer;
		
		artsPlayer *m_artsPlayer;
		QValueList<color> m_sequence;
		QValueList<color>::const_iterator m_nextColor;
};

#endif
