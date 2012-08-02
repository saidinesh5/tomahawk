/*
    The Visualizer Page, acting as a placeholder for the VSXu Widget.
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


#ifndef VISUALIZERWIDGET_H
#define VISUALIZERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include "ViewPage.h"
#include "VSXuWidget.h"

class VisualizerWidget : public QWidget,public Tomahawk::ViewPage
{
    Q_OBJECT

public:
    VisualizerWidget( QWidget *parent = 0 );
    bool jumpToCurrentTrack() { return false; }
    QString description() const { return QString("Music Visualizer"); }
    QString title() const{ return QString("Vovoid VSXu"); }
    QPixmap pixmap() const { return QPixmap( RESPATH "images/visualizer.png" ); }
    Tomahawk::playlistinterface_ptr playlistInterface() const { return Tomahawk::playlistinterface_ptr(); }
    QWidget* widget(){ return this; }
    //TODO: Add the activate and deactivate methods, which can be called from  ViewManager.cpp 
    //when some other page is being activated, to save the CPU cycles.

private:
    VSXuWidget *m_VSXuWidget;

};
#endif // VISUALIZERWIDGET_H
