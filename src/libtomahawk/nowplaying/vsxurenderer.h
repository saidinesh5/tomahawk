/*
    A Threaded Renderer for the computationally intensive VSXu.
    Copyright (C) 2012  Dinesh <dsai@chitika.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef VSXURENDERER_H
#define VSXURENDERER_H

#include <QSize>
#include <QThread>
#include <QStringList>

#include <vsx_manager.h>

#include "fftreal/fftreal.h"

class VSXuWidget;

class VSXuRenderer : public QThread
{
  Q_OBJECT
    //The class that provides us with the OpenGL Context we need
    VSXuWidget *m_widget;

    //The data we need for the VSXu
    vsx_manager_abs* m_manager;

    float *m_audioData;
    float *m_freqData;
    bool m_doResize, m_doRendering, m_doAudioDataUpdate;
    int m_width,m_height;
    int m_nFrames;

public:
    explicit VSXuRenderer(VSXuWidget *widget);
    ~VSXuRenderer();

    void resizeViewport(int w, int h);
    void updateAudioData( float *audioData, float *freqData );

    void run();
    void stop();

};

#endif // VSXURENDERER_H
