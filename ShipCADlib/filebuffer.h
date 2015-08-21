/*##############################################################################################
 *    ShipCAD
 *    Copyright 2015, by Greg Green <ggreen@bit-builder.com>
 *    Original Copyright header below
 *
 *    This code is distributed as part of the FREE!ship project. FREE!ship is an               *
 *    open source surface-modelling program based on subdivision surfaces and intended for     *
 *    designing ships.                                                                         *
 *                                                                                             *
 *    Copyright © 2005, by Martijn van Engeland                                                *
 *    e-mail                  : Info@FREEship.org                                              *
 *    FREE!ship project page  : https://sourceforge.net/projects/freeship                      *
 *    FREE!ship homepage      : www.FREEship.org                                               *
 *                                                                                             *
 *    This program is free software; you can redistribute it and/or modify it under            *
 *    the terms of the GNU General Public License as published by the                          *
 *    Free Software Foundation; either version 2 of the License, or (at your option)           *
 *    any later version.                                                                       *
 *                                                                                             *
 *    This program is distributed in the hope that it will be useful, but WITHOUT ANY          *
 *    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A          *
 *    PARTICULAR PURPOSE. See the GNU General Public License for more details.                 *
 *                                                                                             *
 *    You should have received a copy of the GNU General Public License along with             *
 *    this program; if not, write to the Free Software Foundation, Inc.,                       *
 *    59 Temple Place, Suite 330, Boston, MA 02111-1307 USA                                    *
 *                                                                                             *
 *#############################################################################################*/

#ifndef FILEBUFFER_H_
#define FILEBUFFER_H_

#include <vector>
#include <QFile>
#include <QObject>
#include <QVector3D>
#include <QColor>
#include <QString>

#include "version.h"
#include "plane.h"

namespace ShipCAD {

//////////////////////////////////////////////////////////////////////////////////////

/*! \brief in-memory buffer of data for a binary file (FREE!Ship format)
 */
class FileBuffer : public QObject
{
    Q_OBJECT
public:

    explicit FileBuffer();
    ~FileBuffer() {}

    size_t size() {return _data.size();}

    // version
    version_t getVersion() {return _file_version;}
    void setVersion(version_t v);
	
    // save/restore/reset
    void loadFromFile(const QString& filename);
    void saveToFile(const QString& filename);
    void reset();

    // load/add

    void load(bool& val);
    void add(bool val);

    void load(float& val);
    void add(float val);

    void load(int& val);
    void add(int val);

    void load(size_t& val);
    void add(size_t val);

    void load(version_t& val);
    void add(version_t val);

    void load(QVector3D& val);
    void add(const QVector3D& val);

    void load(QColor& val);
    void add(const QColor& val);

    void load(QString& val);
    void add(const QString& val);

    void load(Plane& val);
    void add(const Plane& val);

private:

    size_t _pos;           // current position in the data vector
    version_t _file_version;
    std::vector<unsigned char> _data;   // the data
};

//////////////////////////////////////////////////////////////////////////////////////

};				/* end namespace */

#endif

