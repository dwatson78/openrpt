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

#include "patheditor.h"

#include <QColorDialog>
#include <QValidator>
#include <QVariant>

PathEditor::PathEditor(QWidget* parent, QPen initPen, Qt::WindowFlags fl, double left, double top, double width, double height)
    : QDialog(parent, fl)
{
  setupUi(this);

  _pen = initPen;
  _sbWidth->setValue(_pen.width());
  switch(_pen.style())
  {
    case Qt::DotLine:
      _rbDottedStyle->setChecked(true);
    break;
    case Qt::DashLine:
      _rbDashedStyle->setChecked(true);
    break;
    default:
      _rbSolidStyle->setChecked(true);
  }
  _left = left;
  _top = top;
  _width = width;
  _height = height;

  // signals and slots connections
  connect(_btnAccept, SIGNAL(clicked()), this, SLOT(accept()));
  connect(_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
  connect(_btnColor, SIGNAL(clicked()), this, SLOT(_btnColor_clicked()));

  _qleLeft->setValidator(new QDoubleValidator(0.0,100.0,3,_qleLeft));
  _qleTop->setValidator(new QDoubleValidator(0.0,100.0,3,_qleTop));
  _qleWidth->setValidator(new QDoubleValidator(-100.0,100.0,3,_qleWidth));
  _qleHeight->setValidator(new QDoubleValidator(-100.0,100.0,3,_qleHeight));

  if(_left != -1 && _top != -1 && _width != -1 && _height != -1)
  {
    _qleLeft->setText(QString::number(_left));
    _qleTop->setText(QString::number(_top));
    _qleWidth->setText(QString::number(_width));
    _qleHeight->setText(QString::number(_height));
    _qleWidth->setVisible(true);
  }
  else
  {
    _gbPos->setVisible(false);
  }

}

PathEditor::~PathEditor()
{
}

void PathEditor::languageChange()
{
  retranslateUi(this);
}

void PathEditor::_btnColor_clicked()
{
  QColor col = QColorDialog::getColor(_pen.color(), this);
  if(col.isValid()) {
    _pen.setColor(col);
  }
}

void PathEditor::accept()
{
  _pen.setWidth(_sbWidth->value());

  if(_rbDottedStyle->isChecked())
    _pen.setStyle(Qt::DotLine);
  else if (_rbDashedStyle->isChecked())
    _pen.setStyle(Qt::DashLine);
  else
    _pen.setStyle(Qt::SolidLine);

  double dt;
  bool ok;
  dt = _qleLeft->text().toDouble(&ok);
  if(ok) _left = dt * 100;
  dt = _qleTop->text().toDouble(&ok);
  if(ok) _top = dt * 100;
  dt = _qleWidth->text().toDouble(&ok);
  if(ok) _width = dt * 100;
  dt = _qleHeight->text().toDouble(&ok);
  if(ok) _height = dt * 100;

  QDialog::accept();
}

