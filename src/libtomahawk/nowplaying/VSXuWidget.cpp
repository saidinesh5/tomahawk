#include "VSXuWidget.h"

#include "audio/audioengine.h"
#include "utils/logger.h"


VSXuWidget::VSXuWidget(QWidget *parent):
  QGLWidget(parent),
  m_isActive(true),
  m_renderer(this)

{
  setWindowTitle("Vovoid VSXu");
  setAutoBufferSwap(false);
  m_renderer.start();

  tDebug()<< "Initializing AudioDataOutput from AudioEngine to VSXu";
  connect ( AudioEngine::instance(),SIGNAL( audioDataReady( const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& ) ),
            this, SLOT( receiveAudioData( const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& ) ) );
  //TODO: Handle the track changes etc...
}

void VSXuWidget::receiveAudioData( const QMap< Phonon::AudioDataOutput::Channel, QVector< qint16 > >& data )
{
  if ( data.size() > 0 ){
    int nSamples;
    if ( data.contains( Phonon::AudioDataOutput::LeftChannel ) ){
      nSamples = data.value(Phonon::AudioDataOutput::LeftChannel).size();
      if (nSamples > SAMPLES) nSamples = SAMPLES;
      for(int i = 0; i < nSamples; i++)
        m_audioData[i] = (float)(data[Phonon::AudioDataOutput::LeftChannel][i]+data[Phonon::AudioDataOutput::RightChannel][i])/131070;
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

/*
void VSXuWidget::closeEvent(QCloseEvent *event)
{
  closeEvent(event);
}
*/

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

