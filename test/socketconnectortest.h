/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef SOCKETCONNECTORINTEGRATIONTEST_H
#define SOCKETCONNECTORINTEGRATIONTEST_H

#include <qt4/QtCore/QObject>
#include "android_usb_camera_test_base.h"

#include "qtInterfaces/socketinterface.h"
#include "framesdataextractor.h"
class MockSocket;
class MockFramesDataExtractor;
class SocketConnector;

class SocketConnectorTest : public QObject
{
Q_OBJECT
  private slots:
    void init();
    void shouldConnectToLocalhost();
    void shouldReadDataOnSocketSignalAndDoNothingOnNoData();
    void shouldReadDataOnSocketSignalAndPassDataToFramesExtractor();
    void cleanup();
  private:
    MockSocket *mocksocket;
    MockFramesDataExtractor *mockframesdataextractor;
    SocketConnector *socketConnector;
  };


  class VoidSocket : public QAbstractSocket {
    public:
      VoidSocket() : QAbstractSocket(UnknownSocketType, NULL) {};
  };

class MockSocket : public SocketInterface {
  public:
    MockSocket() : SocketInterface(new VoidSocket(), NULL) {};
    MOCK_METHOD2(connectToHost, void(const QString &, int) );
    MOCK_METHOD0(readAll, QByteArray());
    void emitReadyRead() { emit readyRead() ;}
};

class MockFramesDataExtractor : public FramesDataExtractor {
  public:
    MockFramesDataExtractor() : FramesDataExtractor(NULL) {};
    MOCK_METHOD1(gotFramesData, void(QByteArray));
};

#endif // SOCKETCONNECTORINTEGRATIONTEST_H
