/*
    The QGLWidget based VSXuWidget class, ready to be embeddable in any QtGUI
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

#include "VSXuWidget.h"
#include "nowplaying/vsxurenderer.h"
#include "audio/audioengine.h"
#include "utils/logger.h"

VSXuWidget::VSXuWidget(QWidget *parent):
  QGLWidget(parent),
  m_renderer(this)
{
    setWindowTitle("Vovoid VSXu");
    setAutoBufferSwap(false);
    m_renderer.start();
    tDebug()<< "Initializing AudioDataOutput from AudioEngine to VSXu";
    connect ( AudioEngine::instance(),SIGNAL( audioDataReady( const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& ) ),
              this, SLOT( receiveAudioData( const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& ) ) );

}

void VSXuWidget::resizeEvent(QResizeEvent *event)
{
    QSize s = event->size();
    m_renderer.resize(s.width(),s.height());
}

VSXuWidget::~VSXuWidget()
{
    m_renderer.stop();
    m_renderer.wait();
}

void VSXuWidget::receiveAudioData( const QMap< Phonon::AudioDataOutput::Channel, QVector< qint16 > >& data )
{
  if ( data.size() > 0 ){
    int nSamples;
    if ( data.contains( Phonon::AudioDataOutput::LeftChannel ) ){
      nSamples = data.value(Phonon::AudioDataOutput::LeftChannel).size();
      if (nSamples > SAMPLES) nSamples = SAMPLES;
      for(int i = 0; i < nSamples; i++)
        soundData[i] = (float)(data[Phonon::AudioDataOutput::LeftChannel][i]+data[Phonon::AudioDataOutput::RightChannel][i])/131070;
    }/*
    if ( data.contains( Phonon::AudioDataOutput::RightChannel ) ){
      nSamples = data.value(Phonon::AudioDataOutput::RightChannel).size();
      if (nSamples > SAMPLES) nSamples = SAMPLES;
      for(int i = 0; i < nSamples; i++){
        m_audioData[i] += data[Phonon::AudioDataOutput::RightChannel][i];
        m_audioData[i] = m_audioData[i]/2;
      }
    }*/
  }
}
