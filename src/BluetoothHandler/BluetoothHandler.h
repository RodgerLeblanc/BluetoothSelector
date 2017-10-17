/*
 * BluetoothHandler.h
 *
 *  Created on: Oct 16, 2017
 *      Author: roger
 */

#ifndef BLUETOOTHHANDLER_H_
#define BLUETOOTHHANDLER_H_

#include <QtConnectivity/QBluetoothDeviceDiscoveryAgent>
#include <QtConnectivity/QBluetoothDeviceInfo>
#include <QtConnectivity/QBluetoothAddress>

using namespace QtMobility;

class BluetoothHandler : public QBluetoothDeviceDiscoveryAgent
{
    Q_OBJECT
public:
    BluetoothHandler(QObject* parent = NULL);

private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo&);

signals:
    void deviceDiscovered(QVariantMap);
};

#endif /* BLUETOOTHHANDLER_H_ */
