/***************************************************************************
 *   Copyright (C) 2005 by Albert Astals Cid <tsdgeos@terra.es>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <qtimer.h>

#include <kapplication.h>

#include "artsplayer.h"
#include "simongame.h"

simonGame::simonGame() : m_phase(starting)
{
	m_artsPlayer = new artsPlayer;
	m_waitTimer = new QTimer(this);
	connect(m_waitTimer, SIGNAL(timeout()), this, SLOT(waiting()));
}

simonGame::~simonGame()
{
	delete m_artsPlayer;
}

simonGame::gamePhase simonGame::phase() const
{
	return m_phase;
}

void simonGame::clicked(color c)
{
	if (c == m_sequence.first())
	{
		m_sequence.pop_front();
		m_artsPlayer -> play(c);
		
		if (m_sequence.size() == 0)
		{
			m_sequenceLength++;
			setPhase(waiting3);
			m_waitTimer -> start(1000);
		}
	}
	else
	{
		emit highlight(all, true);
		setPhase(starting);
	}
}

void simonGame::setPhase(gamePhase p)
{
	m_phase = p;
	emit phaseChanged();
}

void simonGame::start(int level)
{
	m_level = level;
	m_sequenceLength = 1;
	
	setPhase(waiting3);
	m_waitTimer -> start(1000);
}

void simonGame::nextSound()
{
	if (m_nextSound != m_sequence.end())
	{
		color c;
		c = *m_nextSound;
		++m_nextSound;
		m_artsPlayer -> play(c);
		emit highlight(c, false);
	}
	else
	{
		emit highlight(none, false);
		m_artsPlayer->disconnect();
		setPhase(typingTheSequence);
	}
}

void simonGame::soundEnded()
{
	QTimer::singleShot(100, this, SLOT(nextSound()));
	QTimer::singleShot(50, this, SLOT(unhighlight()));
}

void simonGame::unhighlight()
{
	emit highlight(none, false);
}

void simonGame::waiting()
{
	if (m_phase == waiting1)
	{
		m_waitTimer -> stop();
		setPhase(simonGame::learningTheSequence);
		generateSequence();
	
		connect(m_artsPlayer, SIGNAL(ended()), this, SLOT(soundEnded()));
		m_nextSound = m_sequence.begin();
		soundEnded();
	}
	else if (m_phase == waiting3) setPhase(waiting2);
	else /* m_phase == waiting2 */ setPhase(waiting1);
}

void simonGame::generateSequence()
{
	m_sequence.clear();
	
	int r;
	// TODO do something with the level :-D
	for (int i = 0; i < m_sequenceLength; i++)
	{
		r = 1 + (int)(4.0 * kapp -> random() / (RAND_MAX + 1.0));
		switch(r)
		{
			case 1:
				m_sequence.append(red);
			break;
			
			case 2:
				m_sequence.append(green);
			break;
			
			case 3:
				m_sequence.append(blue);
			break;
			
			case 4:
				m_sequence.append(yellow);
			break;
		}
	}
}

#include "simongame.moc"