/*
 * aqmodbus.cpp - This file is part of AQModBus
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

#include <QtCore/QSettings>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtGui/QMessageBox>
#include <QtGui/QScrollBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QResizeEvent>
#include <QtGui/QColorDialog>

#include "aqmodbus.h"
#include "ui_aqmodbus.h"
#include "libmodbus/modbus.h"
#include "QLedMatrix-0.6/qledmatrix.h"

AQModBus::AQModBus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AQModBus),
    m_mbParam(NULL)
{
    ui->setupUi(this);
    //this->setWindowState(Qt::WindowMaximized);

    ResizeUI();

    QString newCSS = ("QProgressBar::chunk{background-color: #85c018;}");
    ui->RegisterList->setColumnWidth(0, 32);
    ui->AnalogList->setColumnWidth(0, 32);

    QSettings settings("/sdcard/.aqmodbus.ini", QSettings::IniFormat);
    NetHost = settings.value("connection/ip").toByteArray();
    NetPort = settings.value("connection/port").toInt();
    SlaveID = settings.value("connection/slave").toInt();
    CoilAddr = settings.value("data/ca").toInt();
    CoilNum = settings.value("data/cn").toInt();
    InAddr = settings.value("data/ia").toInt();
    InNum = settings.value("data/in").toInt();
    RegAddr = settings.value("data/ra").toInt();
    RegNum = settings.value("data/rn").toInt();
    AnaAddr = settings.value("data/aa").toInt();
    AnaNum = settings.value("data/an").toInt();

    QString PortStr;
    QString SlaveStr;
    PortStr.append(QString("%1").arg(NetPort));
    SlaveStr.append(QString("%1").arg(SlaveID));
    QString StatusText = (NetHost + ":" + PortStr + "|" + SlaveStr);
    ui->statusBar->showMessage(StatusText);
    ui->CoilMatrix->setRowCount(CoilNum);
    ui->InputMatrix->setRowCount(InNum);
    ui->RegisterList->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    ui->RegisterList->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->AnalogList->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    ui->AnalogList->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);

    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(pollForDataOnBus()));
    t->start(500);
    ResizeUI();
}

AQModBus::~AQModBus()
{
    delete ui;
}

void AQModBus::connectNetAddress(void)
{
        if(m_mbParam)
        {
                modbus_close(m_mbParam);
                delete m_mbParam;
        }

        m_mbParam = new modbus_param_t;
        modbus_init_tcp(m_mbParam, NetHost.toAscii(), NetPort);

        if(modbus_connect(m_mbParam) == -1 )
        {
                QMessageBox::critical( this, tr( "Connection failed" ),
                        tr( "Could not connect to network! \n" ) );
        }
}

void AQModBus::pollForDataOnBus( void )
{
        if(m_mbParam) {
                modbus_poll(m_mbParam);
        }
        else {
            return;
        }
            // declare arrays for incoming data and set slave id
            uint8_t dest[1024];
            uint16_t * dest16 = (uint16_t *) dest;
            memset( dest, 0, 1024 );

            // set up modbus parameters for plc output
            int func = 1;
            int ret;
            int x;

            if (ui->tabWidget->currentIndex()==0)
            {
                // send data to plc
                ret = -1;
                ret = read_coil_status( m_mbParam, SlaveID, CoilAddr, (CoilNum * 8), dest );

                // update controls
                for(int y=0; y<CoilNum; y++)
                {
                    for (int x=0; x<=7; x++)
                    {
                        if (dest[(y*8+x)] == 1) {
                            ui->CoilMatrix->setColorAt(y, x, 0xFF85C018);
                        }
                        else {
                            ui->CoilMatrix->setColorAt(y, x, QLedMatrix::NoColor);
                        }
                    }
                }
            }

            // set up modbus parameters for plc input
            func = 2;

            // send data to plc
            if (ui->tabWidget->currentIndex()==1)
            {
                ret = -1;
                ret = read_input_status( m_mbParam, SlaveID, InAddr, (InNum * 8), dest );

                // update controls
                for(int y=0; y<InNum; y++)
                {
                    for (int x=0; x<=7; x++)
                    {
                        if (dest[(y*8+x)] == 1) {
                            ui->InputMatrix->setColorAt(y, x, 0xFF85C018);
                        }
                        else {
                            ui->InputMatrix->setColorAt(y, x, QLedMatrix::NoColor);
                        }
                    }
                }
            }

            if (ui->tabWidget->currentIndex()==2)
            {
                //set up parameters for plc registers
                func = 3;

                //send data to plc
                ret = -1;
                ret = read_holding_registers(m_mbParam, SlaveID, RegAddr, RegNum, dest16);

                //update controls
                x = 0;
                for(int i=0; i<RegNum; i++)
                {
                    if (dest16[i] != 0)
                    {
                        ui->RegisterList->setRowCount(x + 1);
                        QTableWidgetItem *addr = new QTableWidgetItem(QString("%1").arg(RegAddr + i));
                        QTableWidgetItem *value = new QTableWidgetItem(QString("%1").arg(dest16[i]));
                        ui->RegisterList->setItem(x, 0, addr);
                        ui->RegisterList->setItem(x, 1, value);
                        x++;
                    }
                }
                if (x == 0) ui->RegisterList->setRowCount(0);

                //set up parameters for analog input registers
                func = 4;

                //send data to plc
                ret = -1;
                ret = read_input_registers(m_mbParam, SlaveID, AnaAddr, AnaNum, dest16);

                //update controls
                x = 0;
                for(int i=0; i<AnaNum; i++)
                {
                    if (dest16[i] != 0)
                    {
                        ui->AnalogList->setRowCount(x + 1);
                        QTableWidgetItem *addr = new QTableWidgetItem(QString("%1").arg(AnaAddr + i));
                        QTableWidgetItem *value = new QTableWidgetItem(QString("%1").arg(dest16[i]));
                        ui->AnalogList->setItem(x, 0, addr);
                        ui->AnalogList->setItem(x, 1, value);
                        x++;
                    }
                }
                if (x == 0) ui->AnalogList->setRowCount(0);
            }
}

void AQModBus::on_settingsBtn_clicked()
{
    settingsDiag = new ModBusSettings(this);
    settingsDiag->show();
    connect(settingsDiag, SIGNAL(accepted()), this, SLOT(ConnectClicked()));
    connect(settingsDiag, SIGNAL(rejected()), settingsDiag, SLOT(close()));
}

void AQModBus::ConnectClicked()
{
    this->NetHost = settingsDiag->ip_addr();
    this->NetPort = settingsDiag->ip_port();
    this->SlaveID = settingsDiag->slave_id();
    this->CoilAddr = settingsDiag->dCA();
    this->CoilNum = settingsDiag->dCN();
    this->InAddr = settingsDiag->dIA();
    this->InNum = settingsDiag->dIN();
    this->RegAddr = settingsDiag->dRA();
    this->RegNum = settingsDiag->dRN();
    this->AnaAddr = settingsDiag->dAA();
    this->AnaNum = settingsDiag->dAN();
    settingsDiag->close();

    QString PortStr;
    QString SlaveStr;
    PortStr.append(QString("%1").arg(NetPort));
    SlaveStr.append(QString("%1").arg(SlaveID));
    QString StatusText = (NetHost + ":" + PortStr + "|" + SlaveStr);
    ui->statusBar->showMessage(StatusText);
    ui->CoilMatrix->setRowCount(CoilNum);
    ui->InputMatrix->setRowCount(InNum);

    QSettings settings("/sdcard/.aqmodbus.ini", QSettings::IniFormat);
    settings.setValue("connection/ip", NetHost);
    settings.setValue("connection/port", NetPort);
    settings.setValue("connection/slave", SlaveID);
    settings.setValue("data/ca", CoilAddr);
    settings.setValue("data/cn", CoilNum);
    settings.setValue("data/ia", InAddr);
    settings.setValue("data/in", InNum);
    settings.setValue("data/ra", RegAddr);
    settings.setValue("data/rn", RegNum);
    settings.setValue("data/aa", AnaAddr);
    settings.setValue("data/an", AnaNum);

    ResizeUI();
    connectNetAddress();
}

void AQModBus::on_connectBtn_clicked()
{
    connectNetAddress();
}

void AQModBus::on_closeBtn_clicked()
{
    this->close();
}

void AQModBus::on_btnWrite_clicked()
{
    int ret;
    switch (ui->cbWrite->currentIndex()) {
        case 0:
            ret = force_single_coil(m_mbParam, SlaveID, ui->WriteAddress->text().toInt(), ui->WriteValue->text().toInt());
        break;
        case 1:
            ret = preset_single_register(m_mbParam, SlaveID, ui->WriteAddress->text().toInt(), ui->WriteValue->text().toInt());
        break;
    }
}

void AQModBus::resizeEvent(QResizeEvent *event) {
    ResizeUI();
}

void AQModBus::ResizeUI() {
    if (this->height() == this->width())
    {
        UIgeometry = 1; //square defaults to landscape, possibly implement later (UIgeometry = 0)
    }
    else if (this->height() < this->width())
    {
        UIgeometry = 1; //landscape
    }
    else if (this->height() > this->width())
    {
        UIgeometry = 2; //portrait
    }
    else
    {
        QMessageBox::critical(this, "ZoMFg!!1!", "ubroookeit!!!11!!one!!!!"); //this should never happen
    }

    switch (UIgeometry) {
    case 0:
        //UI likely doesn't work on square, possibly implement later, for now use landscape method
    break;

    case 1:
        ui->tabWidget->setGeometry(0, 0, (this->width() - 160), this->height());
        ui->settingsBtn->setGeometry(ui->tabWidget->width(), 0, 160, (this->height() / 4));
        ui->connectBtn->setGeometry(ui->tabWidget->width(), (this->height() / 4), 160, (this->height() / 4));
        ui->closeBtn->setGeometry(ui->tabWidget->width(), (this->height() / 2), 160, (this->height() / 4));
    break;

    case 2:
        ui->tabWidget->setGeometry(0, 0, this->width(), (this->height() - 140));
        ui->settingsBtn->setGeometry(0, ui->tabWidget->height(), (this->width() / 3), 80);
        ui->connectBtn->setGeometry((this->width() / 3), ui->tabWidget->height(), (this->width() / 3), 80);
        ui->closeBtn->setGeometry((this->width() / 1.5), ui->tabWidget->height(), (this->width() / 3), 80);
    break;
    }

    ui->CoilMatrix->setGeometry(0, 0, ui->tabWidget->width(), (ui->tabWidget->height() - 80));
    ui->InputMatrix->setGeometry(0, 0, ui->tabWidget->width(), (ui->tabWidget->height() - 80));
    ui->RegisterList->setGeometry(0, 0, (ui->tabWidget->width() / 2), (ui->tabReg->height() - 80));
    ui->AnalogList->setGeometry(ui->RegisterList->width(), 0, (ui->tabWidget->width() / 2), (ui->tabReg->height() - 80));
}

void AQModBus::on_tabWidget_currentChanged(int index)
{
    ResizeUI();
}

void AQModBus::on_btnBGColor_clicked()
{

    QString NewCSS = "QWidget {background-color: green;}";
    this->setStyleSheet(NewCSS);
     //("QProgressBar::chunk{background-color: rgb(" + Red + ", 0, " + Blue + ");}");
}
