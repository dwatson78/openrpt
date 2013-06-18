/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2011 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#ifndef PATHEDITOR_H
#define PATHEDITOR_H

#include <QVariant>
#include <QDialog>
#include <QPen>
#include "ui_patheditor.h"

class PathEditor : public QDialog, public Ui::PathEditor
{
    Q_OBJECT

public:
    PathEditor(QWidget* parent, QPen initPen, Qt::WindowFlags fl = 0, double left = -1, double top = -1, double width = -1, double height = -1);
    ~PathEditor();

    QPen pen() { return _pen; }
    double left() { return _left; }
    double top() { return _top; }
    double width() { return _width; }
    double height() { return _height; }

public slots:

    void _btnColor_clicked();

protected slots:
    virtual void languageChange();
    virtual void accept();

private:
    QPen _pen;
    double _left;
    double _top;
    double _width;
    double _height;

};

#endif // PATHEDITOR_H
