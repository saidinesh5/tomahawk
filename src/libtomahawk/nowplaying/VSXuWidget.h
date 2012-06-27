#ifndef VSXuWidget_H
#define VSXuWidget_H

#include <QGLWidget>
#include <QTimer>
#include <QStringList>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QGLContext>

#include <phonon/audiodataoutput.h>
#include <phonon/path.h>

#include "nowplaying/vsxurenderer.h"
#define SAMPLES 512

class VSXuWidget : public QGLWidget
{
  Q_OBJECT
private:

  VSXuRenderer m_renderer;
  QStringList m_visuals;

  bool m_isActive;
  // To Save the CPU when we aren't using VSXu.

  //Stuff for AudioData going into VSXuEngine
  float m_audioData[SAMPLES];

protected:/*
  void closeEvent(QCloseEvent *event);*/
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event){;}

public:
  VSXuWidget(QWidget *parent = NULL);
  ~VSXuWidget();

public slots:
  void receiveAudioData( const QMap< Phonon::AudioDataOutput::Channel, QVector<qint16> >& data );
};

#endif // VSXuWidget_H
