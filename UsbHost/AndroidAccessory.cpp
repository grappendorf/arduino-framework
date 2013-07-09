/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <UsbHost/Max3421e.h>
#include <UsbHost/UsbHost.h>
#include <UsbHost/AndroidAccessory.h>

#define USB_ACCESSORY_VENDOR_ID         0x18D1
#define USB_ACCESSORY_PRODUCT_ID        0x2D00

#define USB_ACCESSORY_ADB_PRODUCT_ID    0x2D01
#define ACCESSORY_STRING_MANUFACTURER   0
#define ACCESSORY_STRING_MODEL          1
#define ACCESSORY_STRING_DESCRIPTION    2
#define ACCESSORY_STRING_VERSION        3
#define ACCESSORY_STRING_URI            4
#define ACCESSORY_STRING_SERIAL         5

#define ACCESSORY_GET_PROTOCOL          51
#define ACCESSORY_SEND_STRING           52
#define ACCESSORY_START                 53


AndroidAccessory::AndroidAccessory(const char *manufacturer,
                                   const char *model,
                                   const char *description,
                                   const char *version,
                                   const char *uri,
                                   const char *serial) : manufacturer(manufacturer),
                                                         model(model),
                                                         description(description),
                                                         version(version),
                                                         uri(uri),
                                                         serial(serial),
                                                         connected(false)
{

}

boolean AndroidAccessory::begin(void) {
  powerOn();
  return true; // For forward compatibility with v2.x of the library
}

void AndroidAccessory::powerOn(void)
{
    max.powerOn();
    delay(200);
}

int AndroidAccessory::getProtocol(byte addr)
{
    uint16_t protocol = -1;
    usb.ctrlReq(addr, 0,
                USB_SETUP_DEVICE_TO_HOST |
                USB_SETUP_TYPE_VENDOR |
                USB_SETUP_RECIPIENT_DEVICE,
                ACCESSORY_GET_PROTOCOL, 0, 0, 0, 2, (char *)&protocol);
    return protocol;
}

void AndroidAccessory::sendString(byte addr, int index, const char *str)
{
    usb.ctrlReq(addr, 0,
                USB_SETUP_HOST_TO_DEVICE |
                USB_SETUP_TYPE_VENDOR |
                USB_SETUP_RECIPIENT_DEVICE,
                ACCESSORY_SEND_STRING, 0, 0, index,
                strlen(str) + 1, (char *)str);
}


bool AndroidAccessory::switchDevice(byte addr)
{
    int protocol = getProtocol(addr);

    if (protocol == 1) {
        Serial.print(F("device supports protcol 1\n"));
    } else {
        Serial.print(F("could not read device protocol version\n"));
        return false;
    }

    sendString(addr, ACCESSORY_STRING_MANUFACTURER, manufacturer);
    sendString(addr, ACCESSORY_STRING_MODEL, model);
    sendString(addr, ACCESSORY_STRING_DESCRIPTION, description);
    sendString(addr, ACCESSORY_STRING_VERSION, version);
    sendString(addr, ACCESSORY_STRING_URI, uri);
    sendString(addr, ACCESSORY_STRING_SERIAL, serial);

    usb.ctrlReq(addr, 0,
                USB_SETUP_HOST_TO_DEVICE |
                USB_SETUP_TYPE_VENDOR |
                USB_SETUP_RECIPIENT_DEVICE,
                ACCESSORY_START, 0, 0, 0, 0, NULL);

    while (usb.getUsbTaskState() != USB_DETACHED_SUBSTATE_WAIT_FOR_DEVICE) {
        max.Task();
        usb.Task();
    }

    return true;
}

// Finds the first bulk IN and bulk OUT endpoints
bool AndroidAccessory::findEndpoints(byte addr, EP_RECORD *inEp, EP_RECORD *outEp)
{
    int len;
    byte err;
    uint8_t *p;

    err = usb.getConfDescr(addr, 0, 4, 0, (char *)descBuff);
    if (err) {
        Serial.print(F("Can't get config descriptor length\n"));
        return false;
    }


    len = descBuff[2] | ((int)descBuff[3] << 8);
    if (len > (int) sizeof(descBuff)) {
        Serial.print(F("config descriptor too large\n"));
            /* might want to truncate here */
        return false;
    }

    err = usb.getConfDescr(addr, 0, len, 0, (char *)descBuff);
    if (err) {
        Serial.print(F("Can't get config descriptor\n"));
        return false;
    }

    p = descBuff;
    inEp->epAddr = 0;
    outEp->epAddr = 0;
    while (p < (descBuff + len)){
        uint8_t descLen = p[0];
        uint8_t descType = p[1];
        USB_ENDPOINT_DESCRIPTOR *epDesc;
        EP_RECORD *ep;

        switch (descType) {
        case USB_DESCRIPTOR_CONFIGURATION:
            Serial.print(F("config desc\n"));
            break;

        case USB_DESCRIPTOR_INTERFACE:
            Serial.print(F("interface desc\n"));
            break;

        case USB_DESCRIPTOR_ENDPOINT:
            epDesc = (USB_ENDPOINT_DESCRIPTOR *)p;
            if (!inEp->epAddr && (epDesc->bEndpointAddress & 0x80))
                ep = inEp;
            else if (!outEp->epAddr)
                ep = outEp;
            else
                ep = NULL;

            if (ep) {
                ep->epAddr = epDesc->bEndpointAddress & 0x7f;
                ep->Attr = epDesc->bmAttributes;
                ep->MaxPktSize = epDesc->wMaxPacketSize;
                ep->sndToggle = bmSNDTOG0;
                ep->rcvToggle = bmRCVTOG0;
            }
            break;

        default:
            Serial.print(F("unkown desc type "));
            Serial.println( descType, HEX);
            break;
        }

        p += descLen;
    }

    if (!(inEp->epAddr && outEp->epAddr))
        Serial.println(F("can't find accessory endpoints"));

    return inEp->epAddr && outEp->epAddr;
}

bool AndroidAccessory::configureAndroid(void)
{
    byte err;
    EP_RECORD inEp, outEp;

    if (!findEndpoints(1, &inEp, &outEp))
        return false;

    memset(&epRecord, 0x0, sizeof(epRecord));

    epRecord[inEp.epAddr] = inEp;
    if (outEp.epAddr != inEp.epAddr)
        epRecord[outEp.epAddr] = outEp;

    in = inEp.epAddr;
    out = outEp.epAddr;

    Serial.println(inEp.epAddr, HEX);
    Serial.println(outEp.epAddr, HEX);

    epRecord[0] = *(usb.getDevTableEntry(0,0));
    usb.setDevTableEntry(1, epRecord);

    err = usb.setConf( 1, 0, 1 );
    if (err) {
        Serial.print(F("Can't set config to 1\n"));
        return false;
    }

    usb.setUsbTaskState( USB_STATE_RUNNING );

    return true;
}

void AndroidAccessory::refresh(void) {
    max.Task();
    usb.Task();
}

bool AndroidAccessory::isConnected(void)
{
    USB_DEVICE_DESCRIPTOR *devDesc = (USB_DEVICE_DESCRIPTOR *) descBuff;
    byte err;

    refresh();

    if (!connected &&
        usb.getUsbTaskState() >= USB_STATE_CONFIGURING &&
        usb.getUsbTaskState() != USB_STATE_RUNNING) {
        Serial.print(F("\nDevice addressed... "));
        Serial.print(F("Requesting device descriptor.\n"));

        err = usb.getDevDescr(1, 0, 0x12, (char *) devDesc);
        if (err) {
            Serial.print(F("\nDevice descriptor cannot be retrieved. Trying again\n"));
            return false;
        }

        if (isAccessoryDevice(devDesc)) {
            Serial.print(F("found android acessory device\n"));

            connected = configureAndroid();
        } else {
            Serial.print(F("found possible device. swithcing to serial mode\n"));
            switchDevice(1);
        }
    } else if (usb.getUsbTaskState() == USB_DETACHED_SUBSTATE_WAIT_FOR_DEVICE) {
        if (connected)
            Serial.println(F("disconnect\n"));
        connected = false;
    }

    return connected;
}

bool AndroidAccessory::dataBufferIsEmpty() {
  return (numBytesInDataBuff == nextByteInDataBuffOffset);
}

void AndroidAccessory::refillDataBuffer() {
  int bytesRead = 0;

  numBytesInDataBuff = nextByteInDataBuffOffset = 0;
  
  // TODO: Add is connected check?

  bytesRead = read(dataBuff, sizeof(dataBuff));

  if (bytesRead >= 1) {
    numBytesInDataBuff = bytesRead;
  }
}

int AndroidAccessory::read() {

  if (dataBufferIsEmpty()) {
    refillDataBuffer();
  }

  return dataBufferIsEmpty() ? -1 : dataBuff[nextByteInDataBuffOffset++];
}

int AndroidAccessory::peek() {

  if (dataBufferIsEmpty()) {
    refillDataBuffer();
  }

  return dataBufferIsEmpty() ? -1 : dataBuff[nextByteInDataBuffOffset];
}

int AndroidAccessory::available() {

  // Strictly speaking this doesn't meet the "This is only for bytes
  // that have already arrived" definition from
  // <http://arduino.cc/en/Reference/StreamAvailable> but since the
  // data isn't handled by an ISR it's the only way to avoid hanging
  // waiting for `available()` to return true.
  if (dataBufferIsEmpty()) {
    refillDataBuffer();
  }

  return numBytesInDataBuff - nextByteInDataBuffOffset;
}

int AndroidAccessory::read(void *buff, int len, unsigned int nakLimit)
{
    return usb.newInTransfer(1, in, len, (char *)buff, nakLimit);
}

size_t AndroidAccessory::write(uint8_t *buff, size_t len)
{
    usb.outTransfer(1, out, len, (char *)buff);
    return len;
}

size_t AndroidAccessory::write(uint8_t c) {
  return write(&c, 1);
}

void AndroidAccessory::flush() {
  /*
    "Waits for the transmission of outgoing [...] data to complete."

    from <http://arduino.cc/en/Serial/Flush>

    We're treating this as a no-op at the moment.
  */
}
