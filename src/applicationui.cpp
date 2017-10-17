/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QSettings>
#include <bb/cascades/RenderFence>

using namespace bb::cascades;

const QString lastPebbleSelectedKey = "lastPebbleSelected";

ApplicationUI::ApplicationUI() :
        QObject()
{
    bluetoothHandler = new BluetoothHandler(this);
    connect(bluetoothHandler, SIGNAL(finished()), bluetoothHandler, SLOT(deleteLater()));

    //Registering access to this instance and bluetoothHandler object.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);
    qml->setContextProperty("_bluetoothHandler", bluetoothHandler);

    AbstractPane *root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);

    //RenderFence calls reached() when UI is fully loaded, don't forget to setRaised(true).
    RenderFence* renderFence = new RenderFence(this);
    connect(renderFence, SIGNAL(reached()), this, SLOT(onRenderFenceReached()));
    connect(renderFence, SIGNAL(reached()), renderFence, SLOT(deleteLater()));
    renderFence->setRaised(true);
}

QString ApplicationUI::getLastPebbleSelected() {
    //Read from persistent storage.
    QSettings settings;
    return settings.value(lastPebbleSelectedKey).toString();
}

void ApplicationUI::onRenderFenceReached() {
    bluetoothHandler->start();
}

void ApplicationUI::setLastPebbleSelected(QString selectedPebble) {
    //Save to persistent storage.
    QSettings settings;
    settings.setValue(lastPebbleSelectedKey, selectedPebble);
}
