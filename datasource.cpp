/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QtMath>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QQuickView *appViewer, QObject *parent) :
    QObject(parent),
    m_appViewer(appViewer),
    m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    generateData(0, 5, 1024);
	receiver_data = 0;
	receiver_data2 = 0;
}

void DataSource::update(QAbstractSeries *series)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(m_points);

		for(int i = 0; i < 1023; i++){
			m_points[i].setY(m_points[i + 1].ry())	;
		}
        //m_points[1023].setY((qreal) rand() / (qreal) RAND_MAX);
        m_points[1023].setY(receiver_data);
    }
}

void DataSource::update2(QAbstractSeries *series)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(m_points2);

		for(int i = 0; i < 1023; i++){
			m_points2[i].setY(m_points2[i + 1].ry())	;
		}
        //m_points[1023].setY((qreal) rand() / (qreal) RAND_MAX);
        m_points2[1023].setY(receiver_data2);
    }
}

void DataSource::update_red(QAbstractSeries *series)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(m_points_red);
    }
}

void DataSource::anylisy(char *p_char)
{
    if(p_char[0] == '0'){
        receiver_data = p_char[1] - 48	;
	}else{
        receiver_data2 = p_char[1] - 48	;
	}
}

void DataSource::generateData(int type, int rowCount, int colCount)
{
    // Remove previous data
    foreach (QVector<QPointF> row, m_data)
        row.clear();
    m_data.clear();

    // Append the new data depending on the type

    qDebug() << rowCount;

    for (int i(0); i < rowCount; i++) {
        QVector<QPointF> points;
        points.reserve(colCount);
        for (int j(0); j < colCount; j++) {
            qreal x(0);
            qreal y(0);
//            switch (type) {
//            case 0:
//                // data with sin + random component
//                //y = qSin(3.14159265358979 / 50 * j) + 0.5 + (qreal) rand() / (qreal) RAND_MAX;
//                y = 0;
//                x = j;
//                break;
//            case 1:
//                // linear data
//                x = j;
//                y = (qreal) i / 10;
//                break;
//            default:
//                // unknown, do nothing
//                break;
//            }
//            points.append(QPointF(j, 0));
            if(i <= 1){
                points.append(QPointF(j, 0));
            }else{
                points.append(QPointF(j, 2));
            }
        }
        m_data.append(points);
    }

    m_points = m_data.at(1);
    m_points2 = m_data.at(0);
    m_points_red = m_data.at(2);

}
