/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2012,      Teo Mrnjavac <teo@kde.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FLEXIBLEHEADER_H
#define FLEXIBLEHEADER_H

#include <QTimer>

#include "widgets/BasicHeader.h"
#include "DllMacro.h"
#include "Artist.h"

class QPaintEvent;
class FlexibleView;
class QRadioButton;
class QSearchField;

class DLLEXPORT FlexibleHeader : public BasicHeader
{
    Q_OBJECT

public:
    FlexibleHeader( FlexibleView* parent );
    ~FlexibleHeader();

public slots:
    void setFilter( const QString& filter );

signals:
    void filterTextChanged( const QString& filter );

protected:
    void changeEvent( QEvent* e );

private slots:
    void onFilterEdited();
    void applyFilter();

private:
    FlexibleView* m_parent;

    QString m_filter;
    QTimer m_filterTimer;

    QRadioButton* m_radioCloud;
    QRadioButton* m_radioDetailed;
    QRadioButton* m_radioNormal;

    QSearchField* m_filterField;
};

#endif
