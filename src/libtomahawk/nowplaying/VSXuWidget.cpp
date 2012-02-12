#include <QDebug>

#include "VSXuWidget.h"

#include "audio/audioengine.h"
#include "utils/logger.h"


VSXuWidget::VSXuWidget(QWidget *parent):
  QGLWidget(parent),
  m_isActive(true),
  m_fftMachine(SAMPLES)
{
  m_timer = new QTimer(this);
  connect (m_timer , SIGNAL(timeout()), this, SLOT(update()));

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
    m_manager->set_sound_wave(m_audioData);
    m_manager->set_sound_freq(m_freqData);

  }
  //m_manager->set_sound_wave(&sound_wave_test[0]);
  //m_manager->set_sound_freq(&sound_freq_test[0]);
  updateGL();
}

void VSXuWidget::initializeGL()
{
  m_manager = manager_factory();
  // init manager with the shared path and sound input type.
  // manual sound injection: manager->init( path.c_str() , "media_player");
  m_manager->init(0 , "media_player");
  
  m_manager->set_randomizer(false); //We Should be handling the randomizing and switching of visuals etc..
  
  std::vector<std::string> files = m_manager->get_visual_filenames();
  
  tDebug()<<files.size();
  for(int i = 0 ; i < files.size(); i++){
    m_visuals.push_back(QString::fromStdString(files[i]));
  }
  qDebug()<<m_visuals;
  
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0, 0, 0, 0);
  
  glViewport( 0, 0, width(), height());
  
  if (context()->format().hasOpenGL())
    tDebug()<<"You have a Valid OpenGL Context";
  if (context()->format().sampleBuffers())
    tDebug()<<"You have Sample Buffers";
  m_timer->start(20);
  //TODO  replace the 20 with stuff from http://zrusin.blogspot.in/2008/06/animated-interfaces.html
}


void VSXuWidget::paintGL()
{
  if (m_isActive){
    glViewport(0, 0, m_width, m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, m_width, 0, m_height); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (m_manager)
      m_manager->render();
  }
}


VSXuWidget::~VSXuWidget()
{}