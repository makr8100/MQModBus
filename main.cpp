/*
 * main.cpp - This file is part of AQModBus
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

#include <QtGui/QApplication>
#include "aqmodbus.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("MaKR");
    QCoreApplication::setOrganizationDomain("makrit.net");
    QCoreApplication::setApplicationName("AQModBus");
    QCoreApplication::setApplicationVersion(APP_VERSION);

    AQModBus w;
    w.show();

    return a.exec();
}
