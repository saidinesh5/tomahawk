/*
    The Rendering Thread doing the main VSXu Rendering
    Copyright (C) 2012  Dinesh Manajipet <saidinesh5@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef VSXURENDERER_H
#define VSXURENDERER_H

#include <QStringList>
#include <QString>
#include <QThread>
#include <vsx_manager.h>

#include "audio/AudioEngine.h"

#define SAMPLES 512

class VisualizerWidget;
class VSXuRenderer: public QThread
{
  Q_OBJECT
  
    vsx_manager_abs *m_manager;
    VisualizerWidget *m_widget;
    bool m_isRunning, m_doResize, m_doAudioUpdate , m_isActive;
    int m_width,m_height;
    // A double buffer for the sound data.
    float m_soundData[2][SAMPLES];
    bool m_frontbuffer;

    //The Main Loop for VSXu Renderer
    void run();
    void drawSplashScreen();

private slots:
    void receiveAudioData( const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& );

public:
    VSXuRenderer(VisualizerWidget* parent);
    ~VSXuRenderer();
    void deactivate(){ m_isActive = false; }
    void activate(){ m_isActive = true; }
    void stop(){ m_isRunning = false;}

    void nextVisual(){ if(m_manager)m_manager->next_visual(); }
    void prevVisual(){ if(m_manager)m_manager->prev_visual(); }

    bool getRandomizerStatus();
    void setRandomizer(bool value){ if(m_manager)m_manager->set_randomizer(value); }

    float getFXLevel();
    void increaseFXLevel(){ if(m_manager)m_manager->inc_fx_level(); }
    void decreaseFXLevel(){ if(m_manager)m_manager->dec_fx_level(); }

    float getSpeed();
    void increaseSpeed(){ if(m_manager)m_manager->inc_speed();}
    void decreaseSpeed(){ if(m_manager)m_manager->dec_speed();}

    QStringList getVisuals();

    void resize(int w, int h);
    
};

#endif // VSXURENDERER_H
