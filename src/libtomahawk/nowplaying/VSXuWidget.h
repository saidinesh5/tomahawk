#ifndef VSXuWidget_H
#define VSXuWidget_H

#include <QGLWidget>
#include <QTimer>
#include <QStringList>

#include <phonon/audiodataoutput.h>
#include <phonon/path.h>
#include <vsx_manager.h>

class VSXuWidget : public QGLWidget
{
  Q_OBJECT
private:
  vsx_manager_abs* m_manager;
  QTimer *m_timer; // A Timer to frequently update the display

  QStringList m_visuals;
  int m_width,m_height;
  bool m_isActive; // To Save the CPU when we aren't using VSXu.
  //QMap< Phonon::AudioDataOutput::Channel, QVector< qint16 > >     m_audioData;

  void injectSound(float soundData[]);

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
