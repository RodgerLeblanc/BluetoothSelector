/*
 * BluetoothHandler.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: roger
 */

#include <src/BluetoothHandler/BluetoothHandler.h>

using namespace QtMobility;

/*
 *
 * This class is only a wrapper around QBluetoothDeviceDiscoveryAgent that adds
 * another signal that can be easily understood by QML.
 *
 */


BluetoothHandler::BluetoothHandler(QObject* parent) :
        QBluetoothDeviceDiscoveryAgent(parent)
{
    connect(this, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)), this, SLOT(deviceDiscovered(const QBluetoothDeviceInfo&)));
}

void BluetoothHandler::deviceDiscovered(const QBluetoothDeviceInfo& bluetoothInfo) {
    QVariantMap deviceInfo;
    deviceInfo.insert("name", bluetoothInfo.name());
    deviceInfo.insert("address", bluetoothInfo.address().toString());

    emit this->deviceDiscovered(deviceInfo);
}
