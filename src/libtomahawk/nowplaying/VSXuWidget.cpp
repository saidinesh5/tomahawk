#include "VSXuWidget.h"
#include <GL/glu.h>

#include "audio/audioengine.h"
#include "utils/logger.h"


VSXuWidget::VSXuWidget(QWidget *parent):
  QGLWidget(parent),
  m_isActive(true),
  m_fftMachine(SAMPLES)
{
  setAutoBufferSwap(false);
  m_vsxu = new VSXuRenderer(this);

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
        m_audioData[i] = data[Phonon::AudioDataOutput::LeftChannel][i];
    }/*
    if ( data.contains( Phonon::AudioDataOutput::RightChannel ) ){
      nSamples = data.value(Phonon::AudioDataOutput::RightChannel).size();
      if (nSamples > SAMPLES) nSamples = SAMPLES;
      
      for(int i = 0; i < nSamples; i++){
        m_audioData[i] += data[Phonon::AudioDataOutput::RightChannel][i];
        m_audioData[i] = m_audioData[i]/2;
      }
    }*/
    m_fftMachine.do_fft(m_freqData,m_audioData);
    m_vsxu->updateAudioData(m_audioData,m_freqData);
  }
}


/*
void VSXuWidget::closeEvent(QCloseEvent *event)
{
  closeEvent(event);
}
*/
void VSXuWidget::resizeEvent(QResizeEvent* event)
{
  m_vsxu->resizeViewport(event->size().width(),event->size().height());
}
/*
void VSXuWidget::resizeGL(int w, int h)
{
  m_vsxu->resizeViewport(w,h);
}

/*
void VSXuWidget::paintEvent(QPaintEvent *event)
{
}*/


VSXuWidget::~VSXuWidget()
{
  m_vsxu->stop();
  m_vsxu->wait();
  delete m_vsxu;
}