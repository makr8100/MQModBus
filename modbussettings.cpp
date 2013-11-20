/*
 * modbussettings.cpp - This file is part of AQModBus
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

#include <QSettings>
#include "ui_modbussettings.h"
#include "aqmodbus.h"

ModBusSettings::ModBusSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModBusSettings)
{
    ui->setupUi(this);

    QSettings settings("/sdcard/.aqmodbus.ini", QSettings::IniFormat);
    QString NetHost = settings.value("connection/ip").toByteArray();
    int NetPort = settings.value("connection/port").toInt();
    int SlaveID = settings.value("connection/slave").toInt();
    int CoilAddr = settings.value("data/ca").toInt();
    int CoilNum = settings.value("data/cn").toInt();
    int InAddr = settings.value("data/ia").toInt();
    int InNum = settings.value("data/in").toInt();
    int RegAddr = settings.value("data/ra").toInt();
    int RegNum = settings.value("data/rn").toInt();
    int AnaAddr = settings.value("data/aa").toInt();
    int AnaNum = settings.value("data/an").toInt();

    QString PortStr;
    QString SlaveStr;
    QString sCA;
    QString sCN;
    QString sIA;
    QString sIN;
    QString sRA;
    QString sRN;
    QString sAA;
    QString sAN;

    PortStr.append(QString("%1").arg(NetPort));
    SlaveStr.append(QString("%1").arg(SlaveID));
    sCA.append(QString("%1").arg(CoilAddr));
    sCN.append(QString("%1").arg(CoilNum));
    sIA.append(QString("%1").arg(InAddr));
    sIN.append(QString("%1").arg(InNum));
    sRA.append(QString("%1").arg(RegAddr));
    sRN.append(QString("%1").arg(RegNum));
    sAA.append(QString("%1").arg(AnaAddr));
    sAN.append(QString("%1").arg(AnaNum));

    ui->IPaddr->setText(NetHost);
    ui->IPport->setText(PortStr);
    ui->slaveID->setText(SlaveStr);
    ui->tCoilAddr->setText(sCA);
    ui->tCoilNum->setText(sCN);
    ui->tInAddr->setText(sIA);
    ui->tInNum->setText(sIN);
    ui->tRegAddr->setText(sRA);
    ui->tRegNum->setText(sRN);
    ui->tAnaAddr->setText(sAA);
    ui->tAnaNum->setText(sAN);
}

void ModBusSettings::resizeEvent(QResizeEvent *event) {
    ResizeUI();
}

void ModBusSettings::ResizeUI() {
    ui->tabWidget->setGeometry(0, 0, this->width(), this->height());

    ui->lbIIPaddr->setGeometry(0, 0, (this->width() * .6), 20);
    ui->lblIPport->setGeometry((this->width() * .6), 0, (this->width() * .2), 20);
    ui->lblSlaveID->setGeometry((this->width() * .8), 0, (this->width() * .2), 20);

    ui->IPaddr->setGeometry(0, 20, (this->width() * .6), 30);
    ui->IPport->setGeometry((this->width() * .6), 20, (this->width() * .2), 30);
    ui->slaveID->setGeometry((this->width() * .8), 20, (this->width() * .2), 30);

    ui->Connect->setGeometry((this->width() * .01), 60, (this->width() * .45), 50);
    ui->Cancel->setGeometry((this->width() * .54), 60, (this->width() * .45), 50);

    ui->lbStart->setGeometry((this->width() * .6), 120, (this->width() * .2), 20);
    ui->lbNumber->setGeometry((this->width() * .8), 120, (this->width() * .2), 20);

    ui->lbCoil->setGeometry(0, 140, (this->width() * .6), 30);
    ui->tCoilAddr->setGeometry((this->width() * .6), 140, (this->width() * .2), 30);
    ui->tCoilNum->setGeometry((this->width() * .8), 140, (this->width() * .2), 30);

    ui->lbIn->setGeometry(0, 170, (this->width() * .6), 30);
    ui->tInAddr->setGeometry((this->width() * .6), 170, (this->width() * .2), 30);
    ui->tInNum->setGeometry((this->width() * .8), 170, (this->width() * .2), 30);

    ui->lbReg->setGeometry(0, 200, (this->width() * .6), 30);
    ui->tRegAddr->setGeometry((this->width() * .6), 200, (this->width() * .2), 30);
    ui->tRegNum->setGeometry((this->width() * .8), 200, (this->width() * .2), 30);

    ui->lbAnaIn->setGeometry(0, 230, (this->width() * .6), 30);
    ui->tAnaAddr->setGeometry((this->width() * .6), 230, (this->width() * .2), 30);
    ui->tAnaNum->setGeometry((this->width() * .8), 230, (this->width() * .2), 30);

    ui->tbAbout->setGeometry(0, 0, this->width(), this->height());
}

ModBusSettings::~ModBusSettings()
{
    delete ui;
}

QString ModBusSettings::ip_addr() const {
    return this->ui->IPaddr->text();
}

int ModBusSettings::ip_port() const {
    return this->ui->IPport->text().toInt();
}

int ModBusSettings::slave_id() const {
    return this->ui->slaveID->text().toInt();
}

int ModBusSettings::dCA() const {
    return this->ui->tCoilAddr->text().toInt();
}

int ModBusSettings::dCN() const {
    if (ui->tCoilNum->text().toInt() < 16){
        return this->ui->tCoilNum->text().toInt();
    }
    else {
        return 16;
    }
}

int ModBusSettings::dIA() const {
    return this->ui->tInAddr->text().toInt();
}

int ModBusSettings::dIN() const {
    if (ui->tInNum->text().toInt() < 16)
    {
        return this->ui->tInNum->text().toInt();
    }
    else {
        return 16;
    }
}

int ModBusSettings::dRA() const {
    return this->ui->tRegAddr->text().toInt();
}

int ModBusSettings::dRN() const {
    if (ui->tRegNum->text().toInt() > 32)
    {
        return this->ui->tRegNum->text().toInt();
    }
    else {
        return 32;
    }
}

int ModBusSettings::dAA() const {
    return this->ui->tAnaAddr->text().toInt();
}

int ModBusSettings::dAN() const {
    if (ui->tAnaNum->text().toInt() < 32)
    {
        return this->ui->tAnaNum->text().toInt();
    }
    else {
        return 32;
    }
}
