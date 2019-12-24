#include "AL3_lib_include/lib/include/libAlmondHA.h"
#include <iostream>
#include <iterator>
#include <list>
#include <stdio.h>
#include <string>
using namespace std;

void f1(Event *a) {

  // cout<<"inside"<<endl;
  cout << "event is:" << a->event << endl;
}
void f2(Device *a) {
  // printf("voidf1\n");
  // cout<<"inside"<<endl;
  // cout<<"event is:"<<a->event<<endl;
}

int main() {
  int deviceid, index, i, j, OZWNode, ZigBeeShortID, ValueCount, IndexID, Type;
  char *name, *location, *ZigBeeEUI64, *Value, *IndexDataType, *IndexName,
      *Name;
  DevTech DeviceTechnology;
  list<Device>::iterator it;
  HADevices hd;
  Device dobj;
  DeviceList dl;
  dl.Populate();
  for (it = dl.devices.begin(); it != dl.devices.end(); ++it) {
    i = it->getID();
    name = it->getDeviceName();
    location = it->getDeviceLocation();
    OZWNode = it->getOZWNode();
    ZigBeeShortID = it->getShortID();
    ZigBeeEUI64 = it->getZigBeeEUI64();
    DeviceTechnology = it->getDeviceTechnology();
    ValueCount = it->getValueCount();

    cout << "\ndevicid:" << i << "\ndevice name:" << name
         << "\nlocation:" << location << "\nOZWNode:" << OZWNode
         << "\nZigBeeShortID:" << ZigBeeShortID
         << "\nZigBeeEUI64:" << ZigBeeEUI64 << endl
         << "\nDeviceTechnology:" << DeviceTechnology
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
  hd.initializeFree2();
  Device(deviceID).setValue(indexID, indexvalue);

  // struct Event e;
  // EventType g;
  // g=e.event;
  void (*fun)(Event *) = &f1;
  void (*fun2)(Device *) = &f2;
  // hd.broadcastEvent(g);
  hd.genericCallback(fun2);
  hd.eventCallback(fun);

  // lni=it->getLastNotificationIndex();
  // lnv=it->getLastNotificationIndexValue();
  // cout<<"LastNotificationIndex:"<<lni<<"\nLastNotificationIndexValue:"<<lnv<<endl;

  //******
  /*static void genericCallback(void (*callback)(Device *));
     static void eventCallback(void (*callback)(Event*));
     static void deviceCallback(int DevID, void (*callback)(Device *));*/
  // hd.genericCallback();
}
