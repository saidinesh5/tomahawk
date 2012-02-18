#ifndef VSXuWidget_H
#define VSXuWidget_H

#include <QGLWidget>
#include <QTimer>
#include <QStringList>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QPaintEvent>

#include <phonon/audiodataoutput.h>
#include <phonon/path.h>

#include "fftreal/fftreal.h"
#include "nowplaying/vsxurenderer.h"

#define SAMPLES 512

class VSXuWidget : public QGLWidget
{
  Q_OBJECT
private:

  VSXuRenderer *m_vsxu;
  QStringList m_visuals;

  bool m_isActive;
  // To Save the CPU when we aren't using VSXu.

  //Stuff for AudioData going into VSXuEngine
  FFTReal m_fftMachine;
  float m_audioData[SAMPLES];
  float m_freqData[SAMPLES];

protected:/*
  void closeEvent(QCloseEvent *event);*/
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event){;}
  //void initializeGL(){};
  //void resizeGL(int w,int h);
  //void paintGL(){};
  
public:
  VSXuWidget(QWidget *parent = NULL);
  ~VSXuWidget();
  
public slots:
  void receiveAudioData( const QMap< Phonon::AudioDataOutput::Channel, QVector<qint16> >& data );
};

#endif // VSXuWidget_H
