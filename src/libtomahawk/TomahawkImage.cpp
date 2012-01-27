/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Dominik Schmidt <email>

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


#include "TomahawkImage.h"


#include <QDebug>
#include <QThread>

// PIXMAP REGISTRY START //
PixmapRegistry* PixmapRegistry::s_instance = 0;

PixmapRegistry::PixmapRegistry()
{
    Q_ASSERT(false);
    s_instance = this;
}

PixmapRegistry*
PixmapRegistry::instance()
{
    return s_instance;
}

void PixmapRegistry::cache(const QByteArray& data)
{
    Q_UNUSED(data);
}

void PixmapRegistry::uncache(const QByteArray& data)
{
    Q_UNUSED(data);
}
// PIXMAP REGISTRY END //

// PIXMAP REGISTRY GUI START //
PixmapRegistryGui::PixmapRegistryGui()
: PixmapRegistry()
{
}


const QPixmap PixmapRegistryGui::pixmap(const TomahawkImage& image)
{
    QByteArray ba = image.toByteArray();
    if(ba.isNull())
        return m_emptyPixmap;

    QPixmap pm = m_pixmaps.value(ba);

    return pm;
}

void PixmapRegistryGui::cache(const QByteArray& data)
{
    if ( QThread::currentThread() != thread() )
    {
        QMetaObject::invokeMethod( this, "cache", Qt::QueuedConnection, Q_ARG(QByteArray, data) );
        return;
    }

    QPixmap pixmap;
    pixmap.loadFromData( data );
    m_pixmaps.insert(data, pixmap);
}

void PixmapRegistryGui::uncache(const QByteArray& data)
{
    PixmapRegistry::uncache(data);
    m_pixmaps.remove(data);
}

// PIXMAP REGISTRY GUI END //




TomahawkImageData::TomahawkImageData(const QByteArray& data)
{
    m_data = data;
    PixmapRegistry::instance()->cache(data);
}

TomahawkImageData::TomahawkImageData(const TomahawkImageData &other)
    : QSharedData(other)
    , m_data(other.m_data)
{
}


TomahawkImageData::~TomahawkImageData()
{
    PixmapRegistry::instance()->uncache( m_data );
}


TomahawkImage::TomahawkImage()
{
    d = 0;
}

TomahawkImage::TomahawkImage( const QByteArray& data )
{
    d = new TomahawkImageData( data );
}

TomahawkImage::TomahawkImage( const TomahawkImage& other )
    : d(other.d)
{
}

const QByteArray TomahawkImage::toByteArray() const
{
    if( !d )
        return QByteArray();

    return d->m_data;
}

