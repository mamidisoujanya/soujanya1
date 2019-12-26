#include "AL3_lib_include/lib/include/libAlmondHA.h"
#include <iostream>
#include <iterator>
#include <list>
#include <stdio.h>
#include <string>
using namespace std;

void f1(Event *a) {
  cout << "event is:" << a->event<< endl; 
}
void f2(Device *a) {
  int lni;
  char *lnv;
  lni = a->getLastNotificationIndex();
  lnv = a->getLastNotificationIndexValue();

  cout << "LastNotificationIndex:" << lni
       << "\nLastNotificationIndexValue:" << lnv << endl;
}
int main() {
  int deviceid, index, i, j, OZWNode, ZigBeeShortID, ValueCount, IndexID, Type;
  char *name, *location, *ZigBeeEUI64, *Value, *IndexDataType, *IndexName, *AssociationTimeStamp, *Name;
     
  list<Device>::iterator it;
  HADevices hd;
  Device dobj;
  DeviceList dl;
  hd.initializeFree2();
  dl.Populate();
  for (it = dl.devices.begin(); it != dl.devices.end(); ++it) {
    i = it->getID();
    name = it->getDeviceName();
    location = it->getDeviceLocation();
    OZWNode = it->getOZWNode();
    ZigBeeShortID = it->getShortID();
    ZigBeeEUI64 = it->getZigBeeEUI64();
    AssociationTimeStamp=it->getAssociationTimeStamp();
    ValueCount = it->getValueCount();

    cout << "\ndevicid:" << i << "\ndevice name:" << name
         << "\nlocation:" << location << "\nOZWNode:" << OZWNode
         << "\nZigBeeShortID:" << ZigBeeShortID
         << "\nZigBeeEUI64:" << ZigBeeEUI64 << endl
         << "\nAssociationTimeStamp:" << AssociationTimeStamp
         << "\nValueCount:" << ValueCount << endl;

    for (j = 0; j < ValueCount; j++) {
      Value = it->getValue(j);
      Type = it->getIndexType(j);
      Name = it->getValueName(j);
      cout << "Index\t" << j << "\tValue\t" << Value << "\tType\t" << Type
           << "\tName\t" << Name << endl;
    }
    cout << "================================================================";
  }
  int deviceID, indexID, lni;
  char indexvalue[40], *lnv;
  cout << "\nenter device id\n";
  cin >> deviceID;
  cout << "enter index id\n";
  cin >> indexID;
  cout << "enter index value\n";
  cin >> indexvalue;

  Device(deviceID).setValue(indexID, indexvalue);

  hd.genericCallback(f2);

  hd.eventCallback(f1);

  while (1) {
    sleep(1);
  }
}
