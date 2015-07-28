/*###############################################################################################
 *    ShipCAD																					*
 *    Copyright 2015, by Greg Green <ggreen@bit-builder.com>									*
 *    Original Copyright header below															*
 *																								*
 *    This code is distributed as part of the FREE!ship project. FREE!ship is an                *
 *    open source surface-modelling program based on subdivision surfaces and intended for      *
 *    designing ships.                                                                          *
 *                                                                                              *
 *    Copyright © 2005, by Martijn van Engeland                                                 *
 *    e-mail                  : Info@FREEship.org                                               *
 *    FREE!ship project page  : https://sourceforge.net/projects/freeship                       *
 *    FREE!ship homepage      : www.FREEship.org                                                *
 *                                                                                              *
 *    This program is free software; you can redistribute it and/or modify it under             *
 *    the terms of the GNU General Public License as published by the                           *
 *    Free Software Foundation; either version 2 of the License, or (at your option)            *
 *    any later version.                                                                        *
 *                                                                                              *
 *    This program is distributed in the hope that it will be useful, but WITHOUT ANY           *
 *    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A           *
 *    PARTICULAR PURPOSE. See the GNU General Public License for more details.                  *
 *                                                                                              *
 *    You should have received a copy of the GNU General Public License along with              *
 *    this program; if not, write to the Free Software Foundation, Inc.,                        *
 *    59 Temple Place, Suite 330, Boston, MA 02111-1307 USA                                     *
 *                                                                                              *
 *##############################################################################################*/

#include <QString>
#include <QtTest>
#include <cmath>
#include "subdivpoint.h"
#include "subdivface.h"
#include "subdivedge.h"
#include "subdivsurface.h"

using namespace ShipCADGeometry;
using namespace std;

class SubdivfaceTest : public QObject
{
    Q_OBJECT

public:
    SubdivfaceTest();
    ~SubdivfaceTest();
private:
    SubdivisionSurface* _owner;

private Q_SLOTS:
    void testCaseConstruct();
    void testCaseAddPoints();
};

SubdivfaceTest::SubdivfaceTest()
{
    _owner = new SubdivisionSurface();
}

SubdivfaceTest::~SubdivfaceTest()
{
    delete _owner;
}

void SubdivfaceTest::testCaseConstruct()
{
    SubdivisionFace *face = new SubdivisionFace(_owner);
    QVERIFY(face->numberOfPoints() == 0);
    QVERIFY(face->getArea() == 0.0);
    QVERIFY(face->getFaceCenter()[0] == 0.0 &&
            face->getFaceCenter()[1] == 0.0 &&
            face->getFaceCenter()[2] == 0.0);
    QVERIFY(face->getFaceNormal()[0] == 0.0 &&
            face->getFaceNormal()[1] == 0.0 &&
            face->getFaceNormal()[2] == 0.0);
}

void SubdivfaceTest::testCaseAddPoints()
{
    SubdivisionFace *face = new SubdivisionFace(_owner);
    SubdivisionPoint *pt1 = SubdivisionPoint::construct(_owner);
    pt1->setCoordinate(QVector3D(-1,0,0));
    SubdivisionPoint *pt2 = SubdivisionPoint::construct(_owner);
    pt2->setCoordinate(QVector3D(0,2,0));
    SubdivisionPoint *pt3 = SubdivisionPoint::construct(_owner);
    pt3->setCoordinate(QVector3D(1,0,0));
    SubdivisionPoint *pt4 = SubdivisionPoint::construct(_owner);
    pt4->setCoordinate(QVector3D(0,0,1));
    face->addPoint(pt1);
    face->addPoint(pt2);
    face->addPoint(pt3);
    QVERIFY2(face->numberOfPoints() == 3, "number of points");
    QVERIFY2(face->hasPoint(pt1) && face->hasPoint(pt2) && face->hasPoint(pt3), "has point");
    QVERIFY2(!face->hasPoint(pt4), "not have point");
    QVERIFY2(face->getPoint(0) == pt1, "get pt1");
    QVERIFY2(face->getPoint(1) == pt2, "get pt2");
    QVERIFY2(face->getPoint(2) == pt3, "get pt3");
    QVERIFY2(face->getArea() == 2.0, "area");
    QVector3D fc = face->getFaceCenter();
    QVERIFY2(fc[0] == 0 && abs(fc[1] - 0.6666667) <= 0.000001 && fc[2] == 0, "face center");
    QVector3D fn = face->getFaceNormal();
    QVERIFY2(fn[0] == 0 && fn[1] == 0 && fn[2] == -1, "face normal");
}

QTEST_APPLESS_MAIN(SubdivfaceTest)

#include "tst_subdivfacetest.moc"
