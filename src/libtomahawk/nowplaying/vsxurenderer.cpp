/*
    Copyright (C) 2012  Dinesh <saidinesh5@gmail.com>

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


#include "vsxurenderer.h"
#include "VSXuWidget.h"
#include "utils/logger.h"

VSXuRenderer::VSXuRenderer(VSXuWidget* widget): 
  QThread(),
  m_widget(widget),
  m_doResize(false),
  m_doRendering(true),
  m_doAudioDataUpdate(false),
  m_nFrames(0)
{
  m_widget->makeCurrent();
  m_manager = manager_factory();
  m_manager->init(0,"media_player");
  //m_manager->dec_fx_level();
  m_widget->doneCurrent();
  m_width = m_widget->width();
  m_height = m_widget->height();
  start();
}

void VSXuRenderer::stop()
{
  m_doRendering = false;
}

void VSXuRenderer::resizeViewport(int w, int h)
{
  m_width = w;
  m_height = h;
  m_doResize = true;
}

void VSXuRenderer::updateAudioData(float *audioData, float *freqData)
{
  m_audioData = audioData;
  m_freqData = freqData;
  //tDebug()<<"Doing Audio Update";
  m_doAudioDataUpdate = true;
}


void VSXuRenderer::run()
{
  m_widget->makeCurrent();
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0, 0, 0, 0);
  glViewport( 0, 0, m_width, m_height);
  while(m_doRendering){
    if(m_doResize){
      glViewport(0, 0, m_width, m_height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, m_width, 0, m_height); // set origin to bottom left corner
      glMatrixMode(GL_MODELVIEW);
      m_doResize = false;
    }
    if(m_doAudioDataUpdate){
      m_manager->set_sound_wave(m_audioData);
      m_manager->set_sound_freq(m_freqData);
      m_doAudioDataUpdate = false;
    }
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(m_manager)
      m_manager->render();

    m_widget->swapBuffers();
    msleep(15);
    //TODO: Find a way to set the value 15 dynamically, based on the performance
  }
  m_widget->doneCurrent();

}

VSXuRenderer::~VSXuRenderer()
{
  if(m_manager)
    delete m_manager;
}

