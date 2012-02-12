#ifndef VSXuWidget_H
#define VSXuWidget_H

#include <QGLWidget>
#include <QTimer>
#include <QStringList>

#include <phonon/audiodataoutput.h>
#include <phonon/path.h>
#include <vsx_manager.h>

#include "fftreal/fftreal.h"

#define SAMPLES 512

class VSXuWidget : public QGLWidget
{
  Q_OBJECT
private:
  vsx_manager_abs* m_manager;
  QTimer *m_timer; // A Timer to frequently update the display

  QStringList m_visuals;
  int m_width,m_height;
  bool m_isActive; // To Save the CPU when we aren't using VSXu.

  //Stuff for AudioData going into VSXuEngine
  FFTReal m_fftMachine;
  float m_audioData[SAMPLES];
  float m_freqData[SAMPLES];

protected:
  void initializeGL();
  void resizeGL(int w, int h){
    m_width = w;
    m_height = h;
  }
  void paintGL();
  
public:
  VSXuWidget(QWidget *parent = NULL);
  ~VSXuWidget();
  
public slots:
  void receiveAudioData( const QMap< Phonon::AudioDataOutput::Channel, QVector<qint16> >& data );
};

#endif // VSXuWidget_H
