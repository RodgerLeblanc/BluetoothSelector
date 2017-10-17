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

import bb.cascades 1.4

Page {
    attachedObjects: [
        ComponentDefinition { id: dropDownEntry; Option {} }
    ]
    
    onCreationCompleted: {
        _bluetoothHandler.deviceDiscovered.connect(onDeviceDiscovered)
    }
    
    function onDeviceDiscovered(device) {
        console.log("device:" + JSON.stringify(device))
        
        if (device.name.indexOf("Pebble") == 0) {
            var dropDownOption = dropDownEntry.createObject(bluetoothDropDown)
            
            dropDownOption.text = device.name
            dropDownOption.value = device.address
            dropDownOption.selected = device.address == bluetoothDropDown.lastPebbleSelected
            
            bluetoothDropDown.add(dropDownOption)
        }
    }
    
    Container {
        layout: DockLayout {}
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        Container {
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            leftPadding: ui.du(3)
            rightPadding: leftPadding
            DropDown {
                id: bluetoothDropDown
                
                property string lastPebbleSelected: _app.getLastPebbleSelected()
                
                title: qsTr("Choose a Pebble") + Retranslate.onLocaleOrLanguageChanged
                
                onSelectedValueChanged: {
                    _app.setLastPebbleSelected(selectedValue)
                }
            }
        }
    }
}
