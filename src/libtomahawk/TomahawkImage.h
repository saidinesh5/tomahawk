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


#ifndef TOMAHAWKIMAGE_H
#define TOMAHAWKIMAGE_H

#include <QSharedDataPointer>
#include <QSharedData>
#include <QString>
#include <QPixmap>
#include <QHash>


#include "dllmacro.h"

class QByteArray;
class TomahawkImageData;


class DLLEXPORT TomahawkImage
{
public:
    TomahawkImage();
    TomahawkImage( const QByteArray& data );
    TomahawkImage( const TomahawkImage& other );

    const QByteArray toByteArray() const;

private:
    QSharedDataPointer<TomahawkImageData> d;
};

class DLLEXPORT PixmapRegistry
{
public:
    PixmapRegistry();
    virtual ~PixmapRegistry() { };
    static PixmapRegistry* instance();
    virtual void cache( const QByteArray& data );
    virtual void uncache( const QByteArray& data );

private:
    static PixmapRegistry* s_instance;
};



class DLLEXPORT PixmapRegistryGui : public PixmapRegistry
{
public:
    PixmapRegistryGui();
    const QPixmap pixmap( const TomahawkImage& image );
    virtual void cache( const QByteArray& data );
    virtual void uncache( const QByteArray& data );

    static PixmapRegistryGui* instanceGui()
    {
        return dynamic_cast< PixmapRegistryGui* >( PixmapRegistry::instance() );;
    }

private:
    QHash< QByteArray, QPixmap > m_pixmaps;
};

class DLLEXPORT TomahawkImageData : public QSharedData
{

public:
    TomahawkImageData( const QByteArray& data );
    TomahawkImageData(const TomahawkImageData &other);
    ~TomahawkImageData();

    QByteArray m_data;
};


#endif // TOMAHAWKIMAGE_H
