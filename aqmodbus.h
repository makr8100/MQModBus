/*
 * aqmodbus.h - This file is part of AQModBus
 *
 * Copyright © 2011 Mark Gullings http://www.makrit.net
 *
 * Which is nearly a complete ripoff of QModBus © 2009 - Tobias Doerffel- http://qmodbus.sourceforge.net
 * It incorporates libmodbus © 2001-2008 - Stéphane Raimbault - http://www.libmodbus.org
 * And incorporates QLedMatrix © 2009 Pierre-Etienne Messier - http://pemessier.hexpresso.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef AQMODBUS_H
#define AQMODBUS_H

#include <QMainWindow>
#include <QDialog>
#include "libmodbus/modbus.h"
#include "QLedMatrix-0.6/qledmatrix.h"

namespace Ui {
    class AQModBus;
    class ModBusSettings;
}

class ModBusSettings;

class AQModBus : public QMainWindow
{
    Q_OBJECT

public:
    AQModBus(QWidget *parent = 0);
    ~AQModBus();
    QString NetHost;
    int NetPort;
    int SlaveID;
    int CoilAddr;
    int CoilNum;
    int InAddr;
    int InNum;
    int RegAddr;
    int RegNum;
    int AnaAddr;
    int AnaNum;
    int UIgeometry;

private slots:
    void connectNetAddress(void);
    void pollForDataOnBus(void);
    void on_settingsBtn_clicked();
    void ConnectClicked();
    void on_closeBtn_clicked();
    void on_connectBtn_clicked();
    void on_btnWrite_clicked();
    void resizeEvent(QResizeEvent*);
    void ResizeUI();
    void on_tabWidget_currentChanged(int index);
    void on_btnBGColor_clicked();

private:
    Ui::AQModBus *ui;
    modbus_param_t * m_mbParam;
    ModBusSettings* settingsDiag;
};

class ModBusSettings : public QDialog
{
    Q_OBJECT

public:
    ModBusSettings(QWidget *parent = 0);
    ~ModBusSettings();
    QString ip_addr() const;
    int ip_port() const;
    int slave_id() const;
    int dCA() const;
    int dCN() const;
    int dIA() const;
    int dIN() const;
    int dRA() const;
    int dRN() const;
    int dAA() const;
    int dAN() const;

private:
    Ui::ModBusSettings *ui;
    void resizeEvent(QResizeEvent*);
    void ResizeUI();
};

#endif // AQMODBUS_H
